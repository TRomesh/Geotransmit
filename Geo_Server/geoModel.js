const mongoose = require("mongoose");
const Schema = mongoose.Schema;

const GeoSchema = new Schema({
  package: String,
  longitude: { type: Number, required: true },
  lattitude: { type: Number, required: true },
  timestamp: { type: Date, default: Date.now }
});

GeoSchema.index({ longitude: 1, lattitude: 1 }, { unique: true });

module.exports = mongoose.model("Geo", GeoSchema);
