import { Template } from 'meteor/templating';
import { ReactiveVar } from 'meteor/reactive-var';

import './main.html';

Images = new Mongo.Collection("images");
console.log("I am the client. SERVE ME");

//Template.images.helpers({images:img_data});


// iron:router
Router.configure({
	layoutTemplate: 'ApplicationLayout'
});

Router.route('/', function () {
 	this.render('welcome',{
		to:"main"
  	});
});

Router.route('/images', function(){
  	this.render('navbar', {
		to:"navbar"
	});
	this.render('images', {
		to:"main"
	});
});


Session.set("imageLimit", 8);

lastScrollTop = 0;
$(window).scroll(function(event) {
	// test if near bottom of window
	if ($(window).scrollTop() + $(window).height() > $(document).height() - 100) {
		// console.log(new Date());
		// test if going down
		var scrollTop = $(this).scrollTop();
		if (scrollTop > lastScrollTop) {
			Session.set("imageLimit", Session.get("imageLimit") + 4);
		}
		
		lastScrollTop = scrollTop;		
	}
});

Accounts.ui.config({
	passwordSignupFields: "USERNAME_AND_EMAIL"
});

Template.images.helpers({
	images:function(){
		if (Session.get("userFilter")) { 	//user sets a filter
			return Images.find({createdBy:Session.get("userFilter")}, {sort:{createdOn: -1, rating:-1}});
		} else {
			return Images.find({}, {sort:{createdOn: -1, rating:-1}, limit:Session.get("imageLimit")});
		}
	},

	filtering_images:function() {
		if (Session.get("userFilter")) {
			return true;
		} else {
			return false;
		}
	},

	getFilterUser:function() {
		if (Session.get("userFilter")) {
			var user = Meteor.users.findOne({_id:Session.get("userFilter")});
			return user.username;
		} else {
			return false;
		}
	},	

	getUser:function(user_id){
		var user = Meteor.users.findOne({_id:user_id});
		if (user) {
			return user.username;
		} else {
			return "anon";
		}
	}
});


Template.body.helpers({username: function(){
	if(Meteor.user()){
		return Meteor.user().username;
		//return Meteor.user().emails[0].address;
	} else {
		return "anonymous user";
	}
}
});

Template.images.events({
  'click .js-image':function(event){
	alert("Hello!!");
	console.log(event);
	//$(event.target).css("width", "50px");
  },
  'click .js-del-image':function(event){
	var image_id = this._id;
	console.log(image_id);
	$("#"+image_id).hide('slow', function()
	{
		Images.remove({"_id":image_id});
	})
  },
  'click .js-rate-image':function(event){
	var rating = $(event.currentTarget).data("userrating");
  	console.log(rating);
	var image_id = this.id;
	console.log(image_id);

	Images.update({_id:image_id}, {$set: {rating:rating}});
  },

  'click .js-show-image-form':function(event){
 	$("#image_add").modal('show');
  },

  'click .js-set-image-filter':function(event){
	Session.set("userFilter", this.createdBy);
  },

  'click .js-unset-image-filter':function(event){
	Session.set("userFilter", undefined);
  }
});

Template.image_add.events({
  'submit .js-add-image':function(event) {
	var img_src, img_alt;
	img_src = event.target.img_src.value;
	img_alt = event.target.img_alt.value;
	console.log("src: "+img_src+" alt: "+img_alt);

	if (Meteor.user()) {
	  Images.insert({
	  	  img_src:img_src,
		  img_alt:img_alt,
		  createdOn:new Date(),
	  	  createdBy:Meteor.user()._id
	  });
	}

	$("#image_add_form").modal('show');
	return false;
  }
});
