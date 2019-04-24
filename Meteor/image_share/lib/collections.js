Images = new Mongo.Collection("images");

// set up security on Images collection
Images.allow({
	insert:function(userId, doc) {
		console.log("testing security on image insert");
		return true;
	}
})