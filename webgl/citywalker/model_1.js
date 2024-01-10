import * as THREE from 'three';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera( 45, window.innerWidth / window.innerHeight, 0.1, 1000000 );

const renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );

const axesHelper = new THREE.AxesHelper( 10 );
scene.add( axesHelper );

camera.position.z = 100;


const loader = new GLTFLoader();
//loader.load( 'static/models/postwar_city.glb', function ( gltf ) {
loader.load( 'static/models/BarramundiFish.glb', function ( gltf ) {

	//scene.add( gltf.scene );
	scene.add(gltf.scene)
	console.info("The model was loaded successfully");
	console.log(gltf.scene);

}, undefined, function ( error ) {

	console.error( error );

} );

const light = new THREE.AmbientLight( 0x404040 ); // soft white light
scene.add( light );

renderer.render(scene, camera);