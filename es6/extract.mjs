const createObject = () => {
	return {
		Header: () => 'creating a header',
		Footer: () => 'creating a footer',
		Misc: 'other stuff goes here',
	}
}

const { Header, Footer } = createObject();
//console.log("Header: ", Header(), ", Footer: ", Footer())

export { Header, Footer }

export const TwoPi = 3.14159 * 2;

export default "hello, world";