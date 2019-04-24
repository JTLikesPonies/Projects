import { Meteor } from 'meteor/meteor';
Images = new Mongo.Collection("images");

Meteor.startup(function() {
	console.log("I am the server, FEAR ME");
	
	if (Images.find().count() == 0) {

		for (var i=1;i<4;i++) {
		Images.insert(
			{
			img_src:"ua"+i+".jpg",
			img_alt:"'Image via Umbrella Academy'"
			}
		);
		}
		
		console.log("From server/main.js, Images uploaded: "+Images.find().count());
	
	}
});
