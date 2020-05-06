#ifndef CITYSCAPE_SPATIALLAYER_H
#define CITYSCAPE_SPATIALLAYER_H

#include "graph.h"
#include "point.h"
#include "segment.h"
#include "spatial_index.h"

namespace cityscape {
namespace spatial {
template <typename P>
class Layer : public cityscape::graph::Graph {
 public:
  //! Constructor with a unique spatial layer id, tag and initialize idx
  //! \param[in] id Index of the spatial layer
  //! \param[in] tag Tag to categorize spatial layer (default is empty)
  Layer(cityscape::id_t id, const std::string& tag = std::string())
      : Graph(id, tag),
        point_index_(std::make_shared<SpatialIndex<std::shared_ptr<P>>>()),
        segment_index_(
            std::make_shared<SpatialIndex<std::shared_ptr<Segment<P>>>>()){};

  //! Add node
  //! \param[in] node Pointer to node object
  bool add_node(const std::shared_ptr<P>& point);

  //! Create edge
  //! \param[in] src Source node name
  //! \param[in] dest Destination node name
  //! \param[in] directed Edge is directed or undirected
  //! \param[in] tag Tag to categorize edge (default is empty)
  bool create_edge(const std::string& src, const std::string& dest,
                   bool directed, const std::string& tag = std::string());

  //! Return an edge pointer
  //! \param[in] src Source node id
  //! \param[in] dest Destination node id
  //! \retval edge Edge pointer
  std::shared_ptr<Segment<P>> segment(cityscape::id_t src,
                                      cityscape::id_t dest);
  //! Get point index (Rtree)
  std::shared_ptr<SpatialIndex<std::shared_ptr<P>>> point_index() const {
    return point_index_;
  }
  //! Get segment index (Rtree)
  std::shared_ptr<SpatialIndex<std::shared_ptr<Segment<P>>>> segment_index()
      const {
    return segment_index_;
  }

 private:
  //! Points
  tsl::robin_map<cityscape::id_t, std::shared_ptr<P>> points_;
  // Segments
  std::map<std::tuple<cityscape::id_t, cityscape::id_t>,
           std::shared_ptr<Segment<P>>>
      segments_;
  // Segments
  tsl::robin_map<cityscape::id_t, std::shared_ptr<Segment<P>>> segment_ids_;

  // Spatial Index
  std::shared_ptr<SpatialIndex<std::shared_ptr<P>>> point_index_;
  std::shared_ptr<SpatialIndex<std::shared_ptr<Segment<P>>>> segment_index_;
};

#include "layer.tcc"

}  // namespace spatial
}  // namespace cityscape

#endif  // CITYSCAPE_SPATIALLAYER_H
