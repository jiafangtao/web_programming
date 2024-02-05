import * as THREE from 'three';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls";

// feature toggles
const FeatureToggle = {
	showCube: false,
	useAxesHelper: true,
	useOrbitControl: false,
	showGltfModel: true,
}

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera( 
	75, 
	window.innerWidth / window.innerHeight, 
	0.1, 
	100 );

	camera.position.z = 1;


const renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );

const material = new THREE.MeshBasicMaterial( { color: 0x00ee33 } );

if (FeatureToggle.showCube) {
	const geometry = new THREE.BoxGeometry( 0.1, 0.1, 0.1 );
	const cube = new THREE.Mesh( geometry, material );
	scene.add( cube );
}


if (FeatureToggle.useAxesHelper) {
	const axesHelper = new THREE.AxesHelper( 5 );
	scene.add( axesHelper );
}

let controls = undefined;
if (FeatureToggle.useOrbitControl) {
	controls = new OrbitControls(camera, renderer.domElement);
	controls.target.set(0, 0, 0);
	controls.update();
}

const loader = new GLTFLoader();
if (FeatureToggle.showGltfModel) {
	loader.load( 'static/models/BarramundiFish.glb', function ( gltf ) {


		let model = gltf.scene;
		// try
		//model.scale.set(10, 10, 10);


		console.info("The model was loaded successfully");
		console.log(gltf.scene);
	
		model.traverse(function (object) {
			if (object.type === 'Mesh') {
				// 批量更改所有Mesh的材质
				/*object.material = new THREE.MeshLambertMaterial({
					map: object.material.map, //获取原来材质的颜色贴图属性值
					color: object.material.color, //读取原来材质的颜色
				})*/
	
				object.material = material;
			}

			if (object.frustumCulled) {
				console.info("object is frustumCulled, ", object);
				object.frustumCulled = false;
			}
		})

		scene.add(model);
	
		if (FeatureToggle.showGltfModel && FeatureToggle.useOrbitControl) {
			controlsBox(model, controls);
		}
	
	}, undefined, function ( error ) {
		console.error( error );
	} );	
}

const light = new THREE.AmbientLight( 0x808080 ); // soft white light
scene.add( light );

const hemLight = new THREE.HemisphereLight(0xffffff, 0xffffff);
            hemLight.position.set(0, 20, 0);
scene.add(hemLight);


renderer.render(scene, camera);

// 将模型的中心点设置到canvas坐标系的中心点，保证模型显示是居中的
function controlsBox(model, controls) {
	let box = new THREE.Box3().setFromObject(model); // 获取模型的包围盒
	console.log(box);
	let mdlen = box.max.x - box.min.x;
	let mdwid = box.max.z - box.min.z;
	let mdhei = box.max.y - box.min.y;
	let xPoiition = box.min.x + mdlen / 2;
	let yPoiition = box.min.y + mdhei / 2;
	let zPoiition = box.min.z + mdwid / 2;
	let diagonal = Math.sqrt(Math.pow(Math.sqrt(Math.pow(mdlen, 2) + Math.pow(mdwid, 2)), 2) + Math.pow(mdhei, 2));
	// 假设我们需要的进入视角为45度
	// 设置相机位置，向上偏移，确定可以包裹整个模型
	controls.object.position.set(box.max.x + diagonal / 2, (diagonal * 2) / Math.tan(Math.PI / 180 * 45) + Math.abs(box.max.y), box.max.z + diagonal / 2);
	// 设置相机的视角方向，看向模型的中心点
	controls.target.set(xPoiition, yPoiition, zPoiition);
	controls.update();
}

