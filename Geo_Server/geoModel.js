const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const GeoSchema = new Schema({
    package:String,
    longitude: { type: Number, unique: true },
    lattitude: { type: Number, unique: true },
    timestamp:{ type: Date, default: Date.now },
});

module.exports = mongoose.model('Geo', GeoSchema);