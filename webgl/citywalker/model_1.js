import * as THREE from 'three';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera( 90, window.innerWidth / window.innerHeight, 0.1, 10 );

const renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );

const axesHelper = new THREE.AxesHelper( .1 );
scene.add( axesHelper );

camera.position.z = .1;


const loader = new GLTFLoader();
//loader.load( 'static/models/postwar_city.glb', function ( gltf ) {
loader.load( 'static/models/BarramundiFish.glb', function ( gltf ) {

	//scene.add( gltf.scene );
	let model = gltf.scene;

	scene.add(model);
	console.info("The model was loaded successfully");
	
	console.log("Scene - ", model);
	console.log("Scenes - ", gltf.scenes);

	model.scale.set(10, 10, 10);

}, undefined, function ( error ) {

	console.error( error );

} );

const light = new THREE.AmbientLight( 0x808080 ); // soft white light
scene.add( light );

const hemiLight = new THREE.HemisphereLight(0x0000ff, 0x00ff00, 0.6);
hemiLight.position.set(0, 100, 0);
scene.add(hemiLight);

renderer.render(scene, camera);