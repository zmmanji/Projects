// Exercise 2: Set It Up
	// write a class component
	// make it a div with a class name of Likes
	// write a span and a button element inside
	// export default the component!

// Exercise 3: Prop It Up
// Likes should take in number of likes as a prop and display it.

// Exercise 4: State It
// Create a button that toggles between two states: "Liked" and "Not liked (yet)"
	 // add a constructor with initial state
	 // add a button to the rendered JSX with an onClick attribute
	 // add a method to handle the click/ change the state
	 // hook up the button text to the state
// BONUS: Create a likes counter
	 // take in a prop for the number of likes
	 // increase or decrease the likes based on whether button click is like/ unlike
	 // hint: take the total likes as a prop, and convert it to state


import React from 'react';
class Likes extends React.Component{
	state={
	likes: this.props.likes,
	liked: this.props.liked
	}
	handleclick=()=>{
		this.setState({
		liked: !this.state.liked,
		likes: this.state.liked? this.state.likes+1: this.state.likes-1
		
		})

	}
	render(){
	console.log('props: '+ this.props.likes)
	console.log('state: ' +this.state.likes)
		return(
			<div>
			<span>
			<button onClick={this.handleclick}>
			Like
			</button>
			<div>
			</div>
			</span>
			</div>
		);

	}
}

export default Likes