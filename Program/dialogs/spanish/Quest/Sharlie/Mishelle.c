// Брат Шарля, Мишель де Монпе, он же Дичозо, он же воплощение Кукулькана, он же главный злодей
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (pchar.questTemp.Sharlie == "takeknife")
		{
			dialog.text = "¡Bienvenido, Charles el Viajero! He oído todo sobre cómo derrotaste a esos piratas en la costa oriental de Martinica. Ahora estoy absolutamente seguro de que no me equivoqué contigo, hermano.";
			link.l1 = "Hijos de perra me tendieron una trampa. Pero nos subestimaron. Mi navegante, mi tripulación y yo salimos victoriosos. Aunque debo admitir, querido hermano, al principio... las cosas pintaban mal.";
			link.l1.go = "trial"; // промежуточная стадия
			break;
		}
		if (pchar.questTemp.Sharlie == "gambitstage")
		{
			bool bFMQM = CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM != "fail" && pchar.questTemp.FMQM != "end";
			bool bFMQN = CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN != "fail" && pchar.questTemp.FMQN != "end";
			bool bFMQT = CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT != "fail" && pchar.questTemp.FMQT != "end";
			bool bFMQP = CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP != "fail" && pchar.questTemp.FMQP != "end";
			bool bFMQG = CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && pchar.questTemp.FMQG != "end";
			bool bFMQL = CheckAttribute(pchar, "questTemp.FMQL") && pchar.questTemp.FMQL != "fail" && pchar.questTemp.FMQL != "end";
			if (bFMQM || bFMQN || bFMQT || bFMQP || bFMQG || bFMQL)
			{
				if (sti(pchar.rank) < 12)
				{
					dialog.text = "¡Saludos, hermano! Aprecio tu sincero fervor por sacarme de aquí, pero aún no estás listo para el siguiente paso. Mi plan requiere de un capitán experimentado. Sigue explorando el Caribe, gana premios y aprende. Cuando estés listo, continuaremos.";
					link.l1 = "Bueno, lo que digas, hermano. Tú eres el que está aquí sentado, no yo.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Es bueno verte, hermano. No olvides tus compromisos con los demás. Tan pronto como estés libre, te estaré esperando, ¡tengo ideas para nuestro próximo paso!";
					link.l1 = "Entendido, hermano. Me tomaré un tiempo para mis compromisos, pero volveré pronto.";
					link.l1.go = "exit";
				}
				break;
			}
			if (sti(pchar.rank) < 12)
			{
				Log_info("¡Se requiere el nivel 12!");
				dialog.text = "¡Charles el Navegante! ¡He oído sobre tus aventuras! Estás casi listo para la siguiente etapa de mi plan. Regresa tan pronto como hayas ganado un poco más de experiencia.";
				if (sti(pchar.rank) < 7)
				{
					dialog.text = "¡Saludos, hermano! Aprecio tu sincero empeño por sacarme de aquí, pero aún no estás listo para el siguiente paso. Mi plan requiere un capitán experimentado. Sigue explorando el Caribe, gana premios y aprende. Cuando estés listo, continuaremos.";
				}
				else
				{
					if (sti(pchar.rank) < 10)
					{
						dialog.text = "¡Qué bueno verte, hermano! ¡He oído que estás progresando! Pero aún no estás listo para el siguiente paso de mi plan. Sigue haciendo lo que has estado haciendo y vuelve a mí cuando estés listo.";
					}
				}
				link.l1 = "Bueno, lo que digas, hermano. Tú estás aquí encerrado, no yo.";
				link.l1.go = "exit";
				if (sti(pchar.rank) > 8)
				{
					link.l2 = "No lo creo, hermano. Quizás ya te hayas acostumbrado a esta jaula, pero no pienso quedarme aquí mucho tiempo, nuestro padre no puede esperar para siempre. Suéltalo ya.";
					link.l2.go = "gambitA";
				}
				break;
			}
			else
			{
				dialog.text = "Buenas tardes, Charles. Verte alegra mi corazón: definitivamente estás cambiando para mejor.";
				link.l1 = "¿De veras? ¿Y cómo lo imaginas?";
				link.l1.go = "gambit"; // переход на Гамбит
				break;
			}
		}
		if (!CheckAttribute(npchar, "quest.givelink_saga") && CheckAttribute(pchar, "questTemp.HWIC.Detector")) // признак, что Гамбит пройден или провален
		{
			dialog.text = "Puedo verlo, ¡tienes noticias para mí, Charles! Bueno, ¿de qué se trata? ¿Con suerte nada sombrío?";
			link.l1 = "Seguí el consejo que me diste la última vez...";
			link.l1.go = "saga"; // переход на Сагу
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("FortFrance");
			break;
		}
		if (CheckAttribute(pchar, "questTemp.HWIC.Fail1") && CheckAttribute(pchar, "questTemp.HWIC.Fail2") && CheckAttribute(pchar, "questTemp.HWIC.Fail3")) // признак, что Гамбит провален по всем трем вариантам
		{
			dialog.text = "Finalmente estás aquí... ¿Qué novedades hay, querido hermano?";
			link.l1 = "Seguí el consejo que me diste la última vez...";
			link.l1.go = "gambit_fale";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("FortFrance");
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "mishelle") // Сага готова к старту
		{
			dialog.text = "¡Encantado de verte, Charles! ¿Has visto al Chevalier de Poincy? ¿Cómo fue tu reunión?";
			link.l1 = "Sí, querido hermano. Nos hemos encontrado. Y tengo dos noticias para ti, una buena y otra mala. Empezaré con la buena. He saldado tu deuda con De Poincy. La mala noticia es que no te liberará hasta que cumpla tu promesa de arreglar las cosas con algún hereje...";
			link.l1.go = "saga_5";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("FortFrance");
			break;
		}
		// Addon 2016-1 Jason пиратская линейка
		if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && !CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью
		{
			dialog.text = "¿Cómo te fue en La Vega, hermano?";
			link.l1 = "Realmente, no hay nada de qué presumir. Tyrex es un personaje pintoresco, pero sus maneras de hacer negocios simplemente no son para mí.";
			link.l1.go = "saga_17e";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("FortFrance");
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью, но дальше 4 квеста
		{
			dialog.text = "¿Cómo te fue en La Vega, hermano? He oído rumores y para ser completamente honesto, no me siento feliz con ellos... Charlie Prince.";
			link.l1 = "Creo que sé de qué iban esos rumores. Pero todo eso es cosa del pasado. Ya no trabajo con Tyrex, este trabajo se volvió demasiado sucio para mi gusto.";
			link.l1.go = "saga_17f";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("FortFrance");
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete") // пиратская линейка пройдена полностью
		{
			dialog.text = "Bueno, saludos... Corsario Charlie Prince. Dime, Charles, ¿cómo caíste tan bajo? No puedo creer esto. ¡Mi hermano, que ponía cara de asco cuando una vez mencioné saquear un galeón mercante español, ahora es uno de los piratas más buscados y peligrosos de esta región! Incluso yo, sentado aquí en esta letrina, me sonrojo cada vez que tu infamia llega a mis oídos. He maldecido el día en que te envié a La Vega. ¡Qué vergüenza! ¡Un noble francés se ha unido a los piratas y se ha convertido en el peor de todos ellos en tan poco tiempo! ¿Y ahora qué, hermano? ¿Buscas una vacante en el trabajo de barón pirata?";
			link.l1 = "No. He terminado con la piratería de una vez por todas.";
			link.l1.go = "saga_17g";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("FortFrance");
			break;
		}

		dialog.text = "¿Qué más, Charles? Creo que hemos discutido todo. El tiempo es dinero, querido hermano, ¡apresúrate!";
		link.l1 = "Sí, sí, allá voy...";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("Fortfrance");
		break;

	case "Mishelle_prisoner":
		DelLandQuestMark(npchar);
		DelLandQuestMark(characterFromId("Maltie_officer"));
		QuestPointerDelLoc("FortFrance_Dungeon", "quest", "quest1");
		SetCurrentTime(13, 30);
		dialog.text = "¡Charles!.. ¡Encantado de verte, hermano! Entiendo, por supuesto, que será difícil para ti creerlo, pero estoy feliz como un demonio de que estés aquí...";
		link.l1 = "¡Ja! ¡Míralo! ¡Está feliz! Así que mientras tú estabas en tu alto caballo con tu 'Orden', Charles era la vergüenza de la familia, un mísero artista, viviendo del dinero de las cortesanas, y un 'caballero' de la corte, ¿eh? ¡Pero ahora que estás encerrado tras las rejas por tus propios camaradas, estás 'feliz como unas castañuelas' de ver a tu hermano inútil!";
		link.l1.go = "Mishelle_prisoner_1";
		break;

	case "Mishelle_prisoner_1":
		dialog.text = "Charles, tú...";
		link.l1 = "¡No he terminado aún! ¿Por qué no reportaste nada sobre ti a Francia?! ¿Te han privado del derecho a la correspondencia?! ¡Nuestro padre está completamente enfermo de preocupación por ti! ¡Y me pidió que averiguara al menos algo sobre tu destino!..";
		link.l1.go = "Mishelle_prisoner_1a";
		break;

	case "Mishelle_prisoner_1a":
		dialog.text = "Charles, ¿en qué palabras le contaría a nuestro padre lo que me sucedió? ¿Qué le escribiría? No, hermano, por muy difícil que sea, es mejor que nuestro padre no sepa nada aún. Y sería inútil escribirte a ti, siempre estás en diferentes direcciones en París... ¿Cómo me encontraste?..";
		link.l1 = "A la súplica de nuestro padre fui a Malta. Allí recibí alguna información de tu amigo el caballero de La Brignais. Me escribió sobre tus problemas y que probablemente estás en algún lugar de Martinica. Luego volví a Francia y visité a nuestro padre. Y después de todo eso, vine a este agujero infernal en el calor sofocante donde los mosquitos literalmente te mastican hasta la muerte...";
		link.l1.go = "Mishelle_prisoner_1b";
		break;

	case "Mishelle_prisoner_1b":
		dialog.text = "¿Le contaste a nuestro padre acerca de todo esto?";
		link.l1 = "No. Y el caballero de La Brignais no respondió a sus cartas, temiendo las tristes consecuencias... Nuestro padre aún no sabe nada de tu destino. Decidí encontrarte y llegar al fondo del asunto. Solo para que sepas, ¡vine a Martinica no por ti, sino por nuestro pobre padre!";
		link.l1.go = "Mishelle_prisoner_2";
		break;

	case "Mishelle_prisoner_2":
		dialog.text = "¿De verdad? Charles, ¿desde cuándo te importa tu familia? Seamos honestos, hermano, todos en París saben quién es tu padre. Puede que lleves el apellido de De Maure, pero no quieres que el nombre de De Monper sea deshonrado.\nPorque en ese caso no podrías usar tu linaje para contarle a todos historias ficticias sobre tus heroicas hazañas, ¿verdad? Las puertas de las mejores casas de París estarán cerradas para ti, y no te dejarán acercarte a menos de una milla del Louvre.\n¿De verdad crees que tus cortesanas y amantes, cuyos maridos haces cornudos mientras ellos luchan en el campo de batalla por nuestra patria, estarán felices de engañar a sus señores y amos con el hermano de un criminal del estado como yo?.\nSupongo que has llegado aquí directamente desde el lecho de alguna chica casada, ¿me equivoco? Charles, ¿qué pasa con tu cara? ¿Te he tocado un nervio?";
		link.l1 = "Tú... ¡Tú!..";
		link.l1.go = "Mishelle_prisoner_3";
		break;

	case "Mishelle_prisoner_3":
		dialog.text = "Está bien, hermano. Hemos intercambiado pullas, es suficiente. Estoy de acuerdo en que no soy perfecto. Pero tú tampoco eres un ángel. Charles, realmente no es el momento para discutir. Ambos tenemos el mismo objetivo de salvar el honor y la dignidad de la familia Monper... no importa cuáles sean nuestros motivos. Hermano, por una vez en nuestras vidas, reemplacemos la animosidad por la paz. ¿Trato hecho?";
		link.l1 = "Probémoslo... Pero, ¿puedes explicarme de qué te acusan?";
		link.l1.go = "Mishelle_prisoner_4";
		break;

	case "Mishelle_prisoner_4":
		dialog.text = "Oficialmente suena como si se tratara del gasto del dinero de la Sociedad. En realidad, es mucho más profundo.";
		link.l1 = "¿Así que te has apropiado del dinero de tu organización? Bueno-bueno...";
		link.l1.go = "Mishelle_prisoner_5";
		break;

	case "Mishelle_prisoner_5":
		dialog.text = "Te dije que esos eran los cargos oficiales. No tomé ni un solo Luis de oro. Así fue como sucedió... verás, no puedo explicarte todo en detalle mientras esté tras las rejas. No tengo el derecho moral de divulgar los secretos de nuestra Sociedad.";
		link.l1 = "Por favor, trata de explicar, querido hermano. Tengo derecho a saber, ¿no crees?";
		link.l1.go = "Mishelle_prisoner_6";
		break;

	case "Mishelle_prisoner_6":
		dialog.text = "Bien. Había recibido dinero para una operación muy peligrosa y delicada que se suponía cambiaría el equilibrio político en el Caribe. Estaba actuando bajo órdenes directas de Philippe de Poincy, él es el Gobernador General de las Colonias Francesas. Pero la operación fracasó a pesar de todos mis esfuerzos.\nDe Poincy tuvo un ataque de ira debido al hecho de que todos sus planes arriesgados se vinieron abajo. Personalmente firmó la orden de mi arresto y se aseguró de que se ejecutara. Luego vino aquí y declaró que me acusaría de peculado y traición contra la Orden, si mis familiares o yo no devolvíamos el dinero gastado en la operación.";
		link.l1 = "Vaya situación. ¿Dónde está este dinero que, según entiendo, nuestra familia tiene que pagar por tus desatinos?";
		link.l1.go = "Mishelle_prisoner_7";
		break;

	case "Mishelle_prisoner_7":
		dialog.text = "Se gastó en preparar la operación. Sobornos, organización de expediciones, compra de todo tipo de mercancías y equipo. Tuve gastos bastante grandes. Tal como dije, no tomé ni una moneda.";
		link.l1 = "¿Y cuál es la suma que se está exigiendo?";
		link.l1.go = "Mishelle_prisoner_8";
		break;

	case "Mishelle_prisoner_8":
		dialog.text = "Un millón.";
		link.l1 = "¡Merde! Estás bromeando, ¿verdad?";
		link.l1.go = "Mishelle_prisoner_9";
		break;

	case "Mishelle_prisoner_9":
		dialog.text = "¿Acaso parezco alguien con humor para bromas? No, querido hermano, esta es la amarga verdad. Vamos a necesitar entregar a De Poincy un millón de pesos.";
		link.l1 = "¡Pero maldita sea! ¡Nuestra familia no tiene ni de cerca ese tipo de dinero! ¡No podríamos juntar tanto en veinte años!";
		link.l1.go = "Mishelle_prisoner_10";
		break;

	case "Mishelle_prisoner_10":
		dialog.text = "Si no estuviera tras las rejas y restringido por mis obligaciones con la Sociedad, lo haría en seis meses a un año, un año y medio como máximo. Charles, este es el Nuevo Mundo. Todo es diferente aquí. Un hombre motivado y ambicioso puede hacerse una fortuna aquí sin dedicarle toda su vida como en Europa.";
		link.l1 = "¿Un millón en medio año? ¿Estás loco? Si estás tan seguro, ¿por qué no le cuentas eso a tu De Poincy? Que te libere. Da lo mejor de ti...";
		link.l1.go = "Mishelle_prisoner_11";
		break;

	case "Mishelle_prisoner_11":
		dialog.text = "¡Oh, no digas tonterías, Charles! No hay manera de que Poincy me libere de esta celda. Si fuera tan fácil, no pediría tu ayuda.";
		link.l1 = "¡¿Así que soy yo quien tiene que conseguir el dinero para tu libertad?!";
		link.l1.go = "Mishelle_prisoner_12";
		break;

	case "Mishelle_prisoner_12":
		dialog.text = "No solo mi libertad, ¿o lo has olvidado? ¿Deberíamos volver a nuestra conversación sobre los palacios, los bailes y el sexo con cortesanas nobles? Sí, Charles, eres tú quien tiene que hacerlo. Si, por supuesto, te gustaría seguir llevando tu vida meretricia en París como antes. Te gustaría eso, ¿verdad, hermano?";
		link.l1 = "¡Pero maldita sea, ¿de dónde diablos se supone que lo voy a conseguir?! ¿Conoces algún bosque viejo por aquí donde crezcan Luis de oros en lugar de hojas?";
		link.l1.go = "Mishelle_prisoner_13";
		break;

	case "Mishelle_prisoner_13":
		dialog.text = "Todo el Nuevo Mundo representa un bosque de árboles de dinero, pero la gente es demasiado perezosa para levantar sus estúpidas cabezas y extender las manos hacia las ramas. No te preocupes, Charles, lo harás muy bien. Te conozco desde nuestra infancia y nunca perdería mi tiempo persuadiendo a nuestro padre para que te enviara aquí si pensara que eres estúpido o perezoso.\nA pesar de tus defectos que he mencionado antes, eres valiente, ambicioso, inteligente, tienes una lengua afilada y sabes manejar un estoque, lo cual es una habilidad extremadamente importante aquí...";
		link.l1 = "Muchas gracias. ¿De verdad mi querido hermano se ha dignado a alabarme? Y yo pensé que no era más que un artista lamentable, un cortesano...";
		link.l1.go = "Mishelle_prisoner_14";
		break;

	case "Mishelle_prisoner_14":
		dialog.text = "Ya basta, Charles. ¿Tenemos un acuerdo o no?";
		link.l1 = "Lo siento, hermano. Se me escapó. Es que no estoy acostumbrado a oír esas palabras de ti. Es como si una cortesana de la calle predicara sobre salvar un alma.";
		link.l1.go = "Mishelle_prisoner_15";
		break;

	case "Mishelle_prisoner_15":
		dialog.text = "Procedamos, hermano. Como dije, tienes todo lo necesario para tener éxito aquí. No solo eso, no estás solo. Te ayudaré con consejos sobre qué hacer y cómo hacerlo de la manera correcta. Escúchame y saldremos victoriosos. Créeme, no encontrarás a alguien que reemplace mi experiencia. ¿Estás listo para dejar de hablar basura y finalmente llegar al grano?";
		link.l1 = "Sí, parece que me quedaré aquí por un tiempo... Está bien. Soy todo oídos, Michel.";
		link.l1.go = "Mishelle_prisoner_16";
		break;

	case "Mishelle_prisoner_16":
		dialog.text = "Sí, hermano, vas a quedarte aquí por un tiempo. Es bueno que puedas verlo claramente. Así que si alguna cortesana está esperando tu regreso en París, te sugiero que te olvides de ella. Pero no te sientas mal por eso, las chicas locales tienen sus propios encantos.\nAunque, les gustan los hombres de verdad, fuertes e insistentes, incluso rudos. Así que si vas a acostarte con alguna chica de la colonia, no cuentes con poesía, discusiones sobre pinturas o paseos bajo la luna. No lo aprobarán.";
		link.l1 = "Está bien, hermano. ¿Te ha golpeado un rayo de charlatanería? Vamos al grano. Estoy dispuesto a escuchar tus consejos, pero no tus insidias maliciosas.";
		link.l1.go = "Mishelle_prisoner_17";
		break;

	case "Mishelle_prisoner_17":
		dialog.text = "Espléndido. Para que tengas algún tipo de éxito, necesitas poseer un barco. El Caribe es un archipiélago. Lo sabes, ¿verdad? La vida está entrelazada con el mar. Un hombre con su propio barco tiene un horizonte infinito de potencial de ganancia.";
		link.l1 = "¡Pero no soy marinero!";
		link.l1.go = "Mishelle_prisoner_18";
		break;

	case "Mishelle_prisoner_18":
		dialog.text = "Entonces, es hora de convertirte en uno. No tienes otra opción de todos modos. No pensaste en convertirte en empleado de la oficina del puerto o registrarte en la guarnición, ¿verdad? ¿No? Entonces, serás un capitán.";
		link.l1 = "¡Qué giro de los acontecimientos en mi carrera! ¿Y dónde encontraré un barco?";
		link.l1.go = "Mishelle_prisoner_19";
		break;

	case "Mishelle_prisoner_19":
		dialog.text = "Hay una excelente barca esperando en nuestro astillero. No es grande, pero es un barco muy cómodo, perfecto para dar los primeros pasos en la arena de un marinero. Esta barca fue construida especialmente para mí. He dejado un depósito de cinco mil pesos por la embarcación con la ayuda de mis amigos. Dirígete al constructor de barcos y dile que Michel de Monper te envía. Él entenderá para qué estás allí.";
		link.l1 = "¿El barco solo cuesta cinco mil? Eso es un poco raro...";
		link.l1.go = "Mishelle_prisoner_20";
		break;

	case "Mishelle_prisoner_20":
		dialog.text = "Hermano, ¿me estás escuchando? Cinco mil es solo para el depósito. El precio del falucho es de unos veinte mil pesos. Así que tendrás que ganar el resto del dinero tú mismo. Además de eso, necesitarás dinero para contratar una tripulación y un navegante.";
		link.l1 = "¡Estupendo! ¿Y cómo lo conseguiré?";
		link.l1.go = "Mishelle_prisoner_21";
		break;

	case "Mishelle_prisoner_21":
		dialog.text = "No es de extrañar. Gánatelo. ¿Cómo si no? Aquí el dinero se encuentra detrás de cada arbusto, solo tienes que saber dónde buscar y no temer a la adversidad. Pasea por los diferentes establecimientos por aquí. Habla con la gente. Seguro que consigues algún tipo de trabajo. Pero ten cuidado, hay muchos más estafadores que personas honestas. Si no eres un hombre honesto, podrías intentar robar algo valioso de las casas.";
		link.l1 = "Pero somos nobles, ¿verdad?";
		link.l1.go = "Mishelle_prisoner_22";
		break;

	case "Mishelle_prisoner_22":
		dialog.text = "Los títulos no valen nada aquí. Trabaja, pelea, roba como todos los demás. Después de comprar un barco, contrata una tripulación. No podrás dirigir el barco tú solo al principio, así que necesitarás un navegante. Puedes hablar de todo esto con el dueño de la taberna, él te ayudará. Y asegúrate de no perderte, por supuesto. Cuando zarpes al mar, pon rumbo directo a Guadalupe...";
		link.l1 = "¿Qué es eso? ¿Un pueblo?";
		link.l1.go = "Mishelle_prisoner_23";
		break;

	case "Mishelle_prisoner_23":
		dialog.text = "Es una isla a casi dos días de aquí. Intenta conseguir un mapa del archipiélago lo antes posible y apréndelo como el 'Padre Nuestro', para que no parezcas un idiota ante todos los que pueden diferenciar entre un pueblo y una isla. Tendrás que navegar mucho alrededor del archipiélago, así que prepárate con anticipación.";
		link.l1 = "Mm. Está bien. Entonces, ¿qué hago en esta, eh... Guadalupe?";
		link.l1.go = "Mishelle_prisoner_24";
		break;

	case "Mishelle_prisoner_24":
		dialog.text = "Busca a un hombre allí llamado 'Fadey'. Tiene su propia casa no muy lejos del muelle. Dile que me conoces y pídele que pague su deuda. Perdió una buena mano contra mí en una partida de cartas. El dinero que recibas te ayudará a levantarte. Úsalo para poner las cosas en marcha.";
		link.l1 = "¿Qué quieres decir con poner las cosas en marcha?";
		link.l1.go = "Mishelle_prisoner_25";
		break;

	case "Mishelle_prisoner_25":
		dialog.text = "Quiero decir que uses este dinero para ganar aún más dinero, y así sucesivamente. Por ejemplo, comerciando. Volveremos a esta conversación más tarde. Ahora debes ocuparte del barco, navegar a Guadalupe, encontrar a ese gordo moscovita y sacarle la deuda.\nNo literalmente, por supuesto, Fadey es un hombre muy respetado en Guadalupe y amigo del mismo gobernador. Así que no tiene sentido pelearse. Al contrario, intenta hacerte amigo de él. Vuelve a mí tan pronto como tengas el dinero. ¿Entendido, hermano?";
		link.l1 = "Entendido. Oh, por qué... ¿Qué hice para merecer este castigo...?";
		link.l1.go = "Mishelle_prisoner_26";
		break;

	case "Mishelle_prisoner_26":
		dialog.text = "No te aflijas, Charles. Acéptalo como un mal inevitable o... como algo bueno. Más adelante, agradecerás al destino que tu vida haya tomado este giro. Tú, hermano, finalmente tienes la oportunidad de hacer algo para demostrar que eres un hombre de verdad. Incluso podrías convertirte en un ser humano decente...";
		link.l1 = "¿Otra vez con sermones?";
		link.l1.go = "Mishelle_prisoner_27";
		link.l2 = "Hermano, no tengo tiempo para esto. Quiero saltarme la parte aburrida y zarpar en alta mar de inmediato. Cuanto antes tenga un barco, antes saldrás de este agujero. ¿O prefieres quedarte aquí más tiempo?";
		link.l2.go = "Mishelle_prisoner_29"; // Addon 2016-1 Jason пиратская линейка 1
		break;

	case "Mishelle_prisoner_27":
		dialog.text = "No, no. No lo tomes a mal... Está bien, Charles, no pierdas tiempo. Sabes lo que tienes que hacer. Te esperaré regresando de Guadalupe como capitán de tu propio barco con el dinero de Fadey. Buena suerte, hermano. Cuento contigo.";
		link.l1 = "Trataré de no defraudarte. Está bien, Michel. ¡Hasta la próxima!";
		link.l1.go = "Mishelle_prisoner_28";
		break;

	case "Mishelle_prisoner_28":
		DialogExit();
		pchar.questTemp.Sharlie = "ship"; // флаг на старт мини-квестов для сбора денег
		// LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
		LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true); // таверна закр
		if (!bHardcoreGame)
			LocatorReloadEnterDisable("Fortfrance_town", "reload7_back", true); // ЦЕРКОВЬ закр
		LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", true);		// ростовщик закр
		LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", true);		// бордель закр
		LocatorReloadEnterDisable("Fortfrance_town", "reload91", true);			// бордель закр
		LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", true);		// тюрьма закр
		bDisableFastReload = false;												// open быстрый переход
		SaveCurrentQuestDateParam("questTemp.Sharlie_ship");					// запомним дату
		NextDiag.CurrentNode = "First time";
		AddQuestRecord("Sharlie", "5");
		// Sharlie_CreateGigoloMan();//мини-квесты на бордель и на джунгли
		AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
		AddLandQuestMark(characterFromId("FortFrance_PortMan"), "questmarkmain");
		if (CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
		{
			AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
			QuestPointerToLoc("Fortfrance_town", "reload", "reload3_back");
		}
		QuestPointerToLoc("Fortfrance_town", "reload", "reload6_back");
		/*pchar.quest.CreateGigoloMan.win_condition.l1 = "Hour";
		pchar.quest.CreateGigoloMan.win_condition.l1.start.hour = 17.00;
		pchar.quest.CreateGigoloMan.win_condition.l1.finish.hour = 18.00;
		pchar.quest.CreateGigoloMan.function = "Sharlie_CreateGigoloMan";*/
		/* pchar.quest.SharlieremoveLocks.win_condition.l1 = "HardHour";
		pchar.quest.SharlieremoveLocks.win_condition.l1.hour = 23;
		pchar.quest.SharlieremoveLocks.win_condition.l2 = "location";
		pchar.quest.SharlieremoveLocks.win_condition.l2.location = "FortFrance_Town";
		pchar.quest.SharlieremoveLocks.function = "Sharlie_removeLocks"; */
		// устанавливаем прерывание на джунгли
		pchar.quest.Jungle_jew.win_condition.l1 = "location";
		pchar.quest.Jungle_jew.win_condition.l1.location = "Martinique_jungle_01";
		pchar.quest.Jungle_jew.function = "Junglejew_CreateIndians";

		ref location = &Locations[FindLocation(pchar.location)];
		location.first_meeting = true;
		npchar.greeting = "mishelle_3";
		// на гида
		if (GetCharacterIndex("Guide") != -1)
		{
			pchar.quest.Guide_next.win_condition.l1 = "location";
			pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Guide_next.win_condition = "Guide_next";
		}
		break;

	case "Mishelle_prisoner_29": // Addon 2016-1 Jason пиратская линейка 1
		dialog.text = "¡Heh! Esta 'parte aburrida' podría salvarte la vida algún día... Lo que sea. Hay una forma fácil de conseguir el dinero ahora mismo.\nVe a la iglesia y habla con el Abad Benoit. Él es un viejo amigo de nuestro padre. Cuéntale sobre la situación, cae de rodillas y suplica que te preste suficientes monedas para comprar un barco.";
		link.l1 = "¡Mucho mejor ahora! Dirigiéndome al abad.";
		link.l1.go = "Mishelle_prisoner_31";
		link.l2 = "(COMENZAR TUTORIAL) ¿Quieres que comience aumentando tus deudas a niveles aún más altos? ¿Crees que soy un idiota, hermano? Puedo ver que no puedes ayudarme en absoluto con esto. Todo esto recae sobre mí, entonces.";
		link.l2.go = "Mishelle_prisoner_30";
		break;

	case "Mishelle_prisoner_30":
		dialog.text = "¡Vaya! Parece que no me equivoqué contigo, hermano. Espero con ansias tu regreso de Guadalupe, como capitán de tu propio barco con el dinero de Fadey. ¡Buena suerte!";
		link.l1 = "Nos vemos. Que te diviertas aquí.";
		link.l1.go = "Mishelle_prisoner_28";
		break;

	case "Mishelle_prisoner_31":
		DialogExit();
		AddLandQuestMark(characterFromId("Benua"), "questmarkmain");
		pchar.questTemp.Sharlie = "ship_fast"; // ускоренный старт
		pchar.questTemp.Sharlie.FastStart = "true";
		LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false); // откроем верфь
		SaveCurrentQuestDateParam("questTemp.Sharlie_ship");				 // запомним дату
		NextDiag.CurrentNode = "First time";
		AddQuestRecord("Sharlie", "5-1");
		location = &Locations[FindLocation(pchar.location)];
		location.first_meeting = true;
		npchar.greeting = "mishelle_3";
		// на гида
		if (GetCharacterIndex("Guide") != -1)
		{
			pchar.quest.Guide_next.win_condition.l1 = "location";
			pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Guide_next.win_condition = "Guide_next";
		}
		// DeleteAttribute(pchar, "GenQuest.CannotWait");
		Sharlie_removeLocks("");
		sld = characterFromId("Benua");
		sld.dialog.currentnode = "First time";
		break;

	case "trial":
		DelLandQuestMark(npchar);
		dialog.text = "¿Estás tratando de decir que eso fue aterrador? No te pongas tenso, hermano. Está todo absolutamente bien. Yo tampoco me sentí mucho como un héroe en mi primera batalla naval. Tonterías. En un mes o dos, tales encuentros te parecerán de lo más comunes... ¿Has visitado a Fadey?";
		link.l1 = "Así es... Pero con este tipo de éxito... ¿Por qué me molesté siquiera?";
		link.l1.go = "trial_1";
		break;

	case "trial_1":
		dialog.text = "Mm. ¿A qué te refieres?";
		link.l1 = "Porque está en apuros. Recientemente fue robado y tiene sus propios problemas de dinero. En cambio, me ofreció una daga de su colección. Dijo que tiene valor, y que su valor es mayor que la suma de toda la deuda. Así que la tomé...";
		link.l1.go = "trial_2";
		break;

	case "trial_2":
		dialog.text = "¿Está en apuros? ¿Robado? ¿Problemas de dinero? ¡Ja-ja-ja! ¡Me has hecho reír, querido hermano! Ese maldito moscovita te vio de inmediato, y te reconoció como un novato y... ¡ah, ese bribón! Muéstrame la daga que te dio el viejo a cambio de su deuda.";
		if (CheckCharacterItem(pchar, "knife_01"))
		{
			link.l1 = "Aquí tienes...";
			link.l1.go = "trial_3";
			PlaySound("interface\important_item.wav");
		}
		else
		{
			link.l1 = "No la tengo conmigo. A simple vista es solo una daga común. Fadey me dijo que está encantada por un chamán indio, y se llama la Garra del Jefe.";
			link.l1.go = "trial_4";
		}
		break;

	case "trial_3":
		PlaySound("interface\important_item.wav");
		dialog.text = "Mm. Bueno, veamos... Dios juzgará a ese oso rechoncho. Es una chatarra, Charles. Podrías comprarla en cualquier tienda. Te engañó, aprovechándose de tu falta de experiencia... Aquí tienes, toma de vuelta este pedazo de acero. Guárdala como recuerdo. Puedes colgarla sobre tu cama en tu camarote.";
		link.l1 = "¡Cabrón! Oh, a quién le importa... ¡Volveré a verlo en Guadalupe y le daré una buena sacudida a este grasiento insolente!";
		link.l1.go = "trial_5";
		break;

	case "trial_4":
		dialog.text = "¿Encantada por un chamán? ¿Garra del jefe? Sí... todo claro. Dios juzgará a ese oso rechoncho. Es una chatarra, Charles. Podrías comprarla en cualquier tienda. Te hizo una jugada astuta, aprovechándose de tu falta de experiencia... Intentó contarme algún tipo de cuentos de hadas y lo puse de nuevo en su lugar. Así que puedes colgar esta garra en tu camarote sobre tu cama como un recuerdo... Si no la has tirado a la papelera todavía.";
		link.l1 = "¡Cabrón! Oh, ¿a quién le importa...? Volveré a verlo en Guadalupe y le daré una sacudida a este grasiento caluroso.";
		link.l1.go = "trial_5";
		break;

	case "trial_5":
		dialog.text = "Calma, querido hermano, relájate. No hay necesidad de eso a menos que quieras pasar un par de meses en una celda de la prisión de Basse-Terre. ¿Has olvidado lo que te he dicho? Ese oso inflado es un amigo de Claude Francois de Lyon, el gobernador de Guadalupe. Tan pronto como salga de este lugar, iré a hablar con él... de corazón a corazón. No va a ir a ninguna parte.";
		link.l1 = "Está bien. Será mejor que trates con él... ¿Crees que me quedaré sin los fondos iniciales prometidos?";
		link.l1.go = "trial_6";
		break;

	case "trial_6":
		dialog.text = "Parece que sí, Charles. Pero mantén la cabeza en alto. Quien tiene un barco y cabeza sobre los hombros no puede equivocarse en el Caribe. Y tú tienes ambos, ¿verdad?";
		link.l1 = "¿Qué estás insinuando? He metido la pata con este puñal, entonces ¿qué debería...?";
		link.l1.go = "trial_7";
		break;

	case "trial_7":
		dialog.text = "¡Cálmate, querido hermano! ¿Por qué estás tan nervioso de repente? Mantén la calma, vivirás más tiempo. No estoy insinuando nada. ¡Ni siquiera tuve esos pensamientos!";
		link.l1 = "Lo siento, Michel. Es solo que estoy un poco... ¡bueno, trata de entenderme también!";
		link.l1.go = "trial_8";
		break;

	case "trial_8":
		dialog.text = "Entiendo. ¡Y realmente quiero ayudarte! Así que escucha con atención. Debes ganar algo de experiencia y al menos ahorrar un poco de dinero antes de asumir asuntos más serios. Lanzarse a aventuras sin la preparación necesaria es puro suicidio. No quiero que este lugar te aplaste tan pronto.";
		link.l1 = "Muy inspirador. ¿Sobre qué tipo de aventuras estás disertando, Michel? He perdido el hilo de tus divagaciones por alguna razón.";
		link.l1.go = "trial_9";
		break;

	case "trial_9":
		dialog.text = "Hermano, permíteme recordarte que yo, o más específicamente, nosotros, le debemos a de Poincy un millón de pesos. ¿Realmente crees que puedes ganarlos honestamente? Claro, puedes comerciar tanto, es posible si la fortuna te sonríe, pero comerciar en el Caribe tampoco es una actividad pacífica.\nLas aventuras te encontrarán incluso si no quieres participar, la cuestión es, ¿estarás listo para ellas cuando llegue el momento? Es mejor atacar primero. Si vis pacem, para bellum, Charles...";
		link.l1 = "¿Otra vez con las palabras elegantes? Habla francés, te lo ruego...";
		link.l1.go = "trial_10";
		break;

	case "trial_10":
		dialog.text = "Es latín, querido hermano. Dije, 'Si vis pacem, para bellum'. Toma esta frase como una mentalidad de liderazgo hacia la acción. Puedes escribirla en tu bitácora y releerla cada mañana después de la oración. Hay mucho que tienes que aprender y mucho que aún te queda por comprender...";
		link.l1 = "Está bien, eso es suficiente. Me he cansado de tus documentos científicos. Vamos al grano.";
		link.l1.go = "trial_11";
		break;

	case "trial_11":
		dialog.text = "Soy específico, simplemente no sigues todavía. Bien. Primero, necesitas familiarizarte con el archipiélago y acostumbrarte a tu nueva vida como capitán de un barco. Tendrás que trabajar duro para asegurar tu bienestar y un salario para tu tripulación. Hay muchas maneras de ganar dinero.\nTomar cargas y pasajeros a bordo son las más simples. Los comerciantes en las tiendas pueden ofrecerte contratos de carga, y los pasajeros te abordarán en las calles ellos mismos. También deberías considerar revisar las oficinas del puerto, tener cualquier barco rápido te permitirá ganar buen dinero en un trabajo de mensajero.\nLos maestros de puerto te proporcionarán contratos de carga muy rentables una vez que consigas un barco más grande. Habla con la gente, no presumas de tu linaje, sé amable y las cosas irán bien. Visita a los gobernadores de las colonias, a menudo ofrecen trabajo bien pagado.\nPuedes intentar comerciar, pero en ese caso deberías contratar a un buen intendente. Ten cuidado en el mar, evita los escuadrones militares españoles y los barcos de guerra. Si encuentras a un solo comerciante español o un convoy desprotegido, puedes intentar capturarlos.";
		link.l1 = "¿Qué?! Michel, ¿he perdido el oído? ¿Estás sugiriendo que me convierta en pirata? ¿Tú, el orgullo de la Sociedad, un siervo de Dios y la Trinidad, me propones semejante vida?";
		link.l1.go = "trial_12";
		break;

	case "trial_12":
		dialog.text = "Oh, Charles... Te aconsejo que te deshagas de tu fastidio de una vez por todas, aquí no se aprecia. Y sobre la Orden... no seas ingenuo, hermano. Tal vez en Europa el Louvre y el Escorial estén en paz de alguna manera, pero aquí hay guerra. Cualquier asaltante español no dudará en saquear tu barco y colgarte a ti y a tu tripulación para que se sequen en una percha.\nPor lo tanto, nadie te culpará por saquear un barco mercante de una nación hostil, te lo aseguro. Y con una carta de corso incluso obtendrás el apoyo oficial de las autoridades...";
		link.l1 = "Empiezo a entender los principios de tu vida. Así como entiendo los métodos con los que aparentemente serías capaz de 'ganar' un millón en medio año.";
		link.l1.go = "trial_13";
		break;

	case "trial_13":
		dialog.text = "Y tendrás que usar estos métodos, Charles. Después de todo, esto es apoyado por las autoridades actuantes abiertamente o a puerta cerrada. Incluso si te mantienes en el comercio, un día te verás obligado a luchar contra piratas o asaltantes españoles, porque para ellos eres el botín.\nTu mejor interés es olvidar tus puntos de vista anteriores sobre la vida. Créeme, hermano, puedes hacer un gran número de cosas no solo sin perder la cara, sino también ganar el favor de las autoridades y el amor del pueblo.";
		link.l1 = "Jamás dejas de sorprenderme, Michel. Ahora me dices que me convierta en pirata. ¿Qué sigue?";
		link.l1.go = "trial_14";
		break;

	case "trial_14":
		dialog.text = "No dramatices demasiado esto, Charles. Es realmente simple: cazar o ser cazado. Esa es toda la filosofía. Yo prefiero la primera y me gustaría que siguieras mi ejemplo. Y no te estoy diciendo que te conviertas en pirata, sino que te involucres en acciones militares contra una nación hostil solo cuando haya una buena razón para ello.";
		link.l1 = "¿Un beneficio, dices?";
		link.l1.go = "trial_15";
		break;

	// Rebbebion, небольшое изменение диалога
	case "trial_15":
		dialog.text = "Ves, entiendes, hermano. Pero basta de palabras. Es hora de ponerte a prueba. Ven a verme sólo cuando te sientas listo. Gana algo de dinero decente, consigue un mejor barco, conoce el archipiélago y mejora tus habilidades.\nPero ten cuidado, si pasas los próximos meses en tabernas y burdeles, y no aprendes nada útil en el proceso... ni siquiera regreses entonces. ¿Estamos claros, Charles?";
		link.l1 = "No te preocupes. No vine aquí para recrearme... ¿Qué viene después de eso?";
		link.l1.go = "trial_16";
		break;

	case "trial_16":
		dialog.text = "Más tarde te diré qué hacer después de eso. Ya he elaborado un plan. Tienes un futuro brillante por delante, Charles, si sigues con precisión mis consejos y recomendaciones.";
		link.l1 = "Preferiría mi modesto pasado a un futuro tan brillante y grandioso...";
		link.l1.go = "trial_17";
		break;

	case "trial_17":
		dialog.text = "Confía en mí, hermano, te reirás de tu pasado sin valor y agradecerás al destino por salvarte de él. Sé optimista y positivo. Te encantará esta vida. Ya verás.\nAh, una cosa más: visita a nuestro amigo común Fadey y pídele que te consiga un trabajo. El oso tiene buenas conexiones, estoy seguro de que encontrará algo para ti. No te demores o podrías perder una oportunidad. Y por favor, no me falles.";
		link.l1 = "Enseñanzas moral otra vez... Señor, ¿cuándo terminará todo esto? Está bien, Michel... ¿Puedo seguir mi camino?";
		link.l1.go = "trial_18";
		break;

	case "trial_18":
		dialog.text = "Espera. Unos cuantos consejos tácticos más. Si te encuentras en conflicto con alguna nación y te vuelves un forajido, visita la iglesia y habla con el Abad Benoit. Dile que te he enviado yo. Él tiene conexiones tanto en la sociedad Papista como en la Calvinista y me ha ayudado mucho con estos asuntos más de una vez. Pero ten en cuenta que no es ni fácil ni barato, así que intenta evitar hacer enemigos. \n¡Espera, una cosa más! Somos nobles, pero es insensato tener aversión a trabajar con nuestras propias manos, especialmente aquí. Puedes elaborar muchos objetos útiles, siempre que tengas las herramientas y componentes necesarios... Dime, hermano, ¿cómo cargas cualquiera de tus pistolas?";
		link.l1 = "Hm. Como de costumbre, una bala y una pizca de pólvora. ";
		link.l1.go = "trial_19";
		break;

	case "trial_19":
		dialog.text = "¡Ja! No esperaba escuchar nada diferente.";
		link.l1 = "¿Conoces otro camino, querido hermano?";
		link.l1.go = "trial_20";
		break;

	case "trial_20":
		dialog.text = "Por supuesto. Pero hay pocos que lo hacen debido a la ignorancia y la simple pereza. Al gastar un par de horas de tu tiempo, podrías hacer cartuchos de papel con pólvora y balas. Usarlos reduce a la mitad el tiempo de recarga del arma. ¿Impresionado?";
		link.l1 = "Hum. Supongo que sí. Es interesante.";
		link.l1.go = "trial_21";
		break;

	case "trial_21":
		pchar.alchemy.known = 1;
		AddQuestRecordInfo("Recipe", "cartridge");
		SetAlchemyRecipeKnown("cartridge");
		dialog.text = "Toma estas instrucciones de fabricación para conchas de papel, estúdialas en tu tiempo libre, y no seas demasiado perezoso para aplicar tu nuevo conocimiento\Espera, hermano. No te olvides de pasar a ver a nuestro querido gobernador.";
		link.l1 = "¿Hay alguna ocasión?";
		link.l1.go = "trial_22";
		break;

	// Rebbebion, намёк на "Травлю крысы"
	case "trial_22":
		dialog.text = "Siempre es bueno mantener contacto con los gobernadores, especialmente si tienen a tus familiares encarcelados en sus islas.";
		link.l1 = "Dime sobre él.";
		link.l1.go = "trial_23";
		break;

	case "trial_23":
		dialog.text = "No todos pueden aferrarse al trono de Martinica. Los intereses de la Orden, la Corona, los piratas... y un noble no debería olvidar sus propios intereses. Si Parquet no fuera tan laxo y tentado por el pecado, incluso podría hacer que Poincy lo tomara en serio.";
		link.l1 = "¿Y de qué utilidad podría ser yo para él?";
		link.l1.go = "trial_24";
		break;

	case "trial_24":
		dialog.text = "Los funcionarios siempre tienen trabajo para capitanes libres. Aunque pagan con moderación, y solo cuando se trata de intereses públicos, no personales. En cualquier caso, no hay mejor manera en el Caribe de elevar el honor y mejorar las relaciones nacionales que trabajando para los gobernadores. Aprovecha el momento, especialmente ahora que Parquet enfrenta algunos problemas. ¿Qué tipo de problemas?";
		link.l1 = "¿Qué tipo de problema?";
		link.l1.go = "trial_25";
		break;

	case "trial_25":
		dialog.text = "Lo siento, hermano. Los intereses de la Orden están involucrados. Solo diré que no somos los únicos que necesitan maneras rápidas de hacerse ricos.";
		link.l1 = "Estás siendo críptico otra vez... Bueno, pasaré cuando tenga tiempo.";
		link.l1.go = "trial_26";
		break;

	case "trial_26":
		dialog.text = "Ahora ve. ¡Buena suerte, hermano!";
		link.l1 = "Gracias... Hasta luego, Michel.";
		link.l1.go = "trial_27";
		break;

	case "trial_27":
		TakeNItems(pchar, "bullet", 5);
		TakeNItems(pchar, "gunpowder", 5);
		DialogExit();
		NextDiag.TempNode = "First time";
		pchar.questTemp.Sharlie = "trial";
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		pchar.questTemp.Trial = "begin";								 // старт промежуточной линейки
		SetFunctionTimerCondition("Sharlie_TrialOver", 0, 0, 24, false); // таймер
		AddMapQuestMarkCity("Baster", false);
		AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
		AddQuestRecord("Sharlie", "19");
		// открываем все острова
		for (i = 0; i < MAX_ISLANDS; i++)
		{
			if (!CheckAttribute(&Islands[i], "hidden"))
				Island_SetReloadEnableGlobal(Islands[i].id, true);
		}
		DeleteAttribute(pchar, "questTemp.Sharlie.Lock");				 // снимаем блокировку
		LocatorReloadEnterDisable("FortFrance_store", "reload2", false); // откроем склад магазина
		sld = characterFromId("Benua");
		sld.quest.help = "true";
		npchar.greeting = "mishelle_3";
		i = FindIsland("Martinique");
		Islands[i].EffectRadius = 5000;
		// Addon-2016 Jason, французские миниквесты (ФМК)
		pchar.quest.Sharlie_FMQ.win_condition.l1 = "Rank";
		pchar.quest.Sharlie_FMQ.win_condition.l1.value = 4;
		pchar.quest.Sharlie_FMQ.win_condition.l1.operation = ">=";
		pchar.quest.Sharlie_FMQ.function = "FMQ_SetConditions";
		// Sinistra - миниквест "Делюк"
		PChar.quest.Del_Alonso.win_condition.l1 = "location";
		PChar.quest.Del_Alonso.win_condition.l1.location = "FortFrance_town";
		PChar.quest.Del_Alonso.win_condition = "Del_Alonso";
		// при достижении уровня даём флаг на квест "Голландский Гамбит"
		pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1 = "Rank";
		pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1.value = 9;
		pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1.operation = ">=";
		pchar.quest.Sharlie_GambitStage_level_9.function = "Sharlie_GambitStage_level_9";
		pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1 = "Rank";
		pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1.value = 12;
		pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1.operation = ">=";
		pchar.quest.Sharlie_GambitStage_level_12.function = "Sharlie_GambitStage_level_12";
		// маркер на контрабандиста по квесту "Деньги на деревьях"
		AddLandQuestMark(characterFromId("FortFrance_Smuggler"), "questmarkmain");
		PChar.quest.MOT_UbratMarku.win_condition.l1 = "MapEnter";
		PChar.quest.MOT_UbratMarku.win_condition = "MOT_UbratMarku";
		// Sinistra - Старт квеста "Травля крысы"
		pchar.questTemp.TK_TravlyaKrys = true;
		AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
		SetTimerCondition("TK_Timer", 0, 0, 30, false);
		// маркер на торговца БасТера по квесту "Бесчестный конкурент"
		AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;

	case "gambitA":
		dialog.text = "Pues que sea a tu manera entonces. Creo en ti, hermano. Cuando te miro ahora, sé que estás cambiando para mejor.";
		link.l1 = "No me digas. ¿Cómo así?";
		link.l1.go = "gambit";
		break;

	case "gambit":
		dialog.text = "Lo veo, querido hermano. Puedo ver tu andar y la expresión en tu rostro. Finalmente la máscara de un joven engreído, que literalmente me volvía loco, se ha derretido de ti. Tu nueva vida claramente te ha beneficiado hasta ahora.";
		if (sti(pchar.money) >= 1000000)
		{
			link.l1 = "No puedo entender, hermano, si tus palabras son alabanzas o insultos. Pero te diré la verdad: no me interesa lo que pienses de mí desde allá. He reunido el millón necesario para pagar tu deuda, así que pronto estarás libre. ¿Dónde puedo encontrar a de Poincy?";
			link.l1.go = "gambit_1_1";
		}
		else
		{
			link.l1 = "No puedo entender, hermano, qué hacer con tus palabras, si son alabanzas o insultos. Pero te diré la verdad: no me interesa lo que pienses de mí desde allí. Tengo un mar, no un montón, de asuntos que atender y no tengo tiempo para enredarme en una disputa contigo aquí y picar palabras. ¿Tienes algo relevante que decir? Si no, entonces seguiré mi camino...";
			link.l1.go = "gambit_1";
		}
		DelLandQuestMark(npchar);
		// уберем маркеры, если ФМК не стали проходить
		DelMapQuestMarkCity("Baster");
		DelMapQuestMarkCity("Fortfrance");
		DelMapQuestMarkCity("Charles");
		DelMapQuestMarkCity("Tortuga");
		DelMapQuestMarkCity("Portpax");

		if (CharacterIsAlive("FMQG_pass_1"))
		{
			sld = CharacterFromID("FMQG_pass_1");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
		}
		if (CharacterIsAlive("FMQM_carpenter"))
		{
			sld = CharacterFromID("FMQM_carpenter");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
		}
		if (CharacterIsAlive("FMQN_seafox_1"))
		{
			sld = CharacterFromID("FMQN_seafox_1");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
		}
		if (CharacterIsAlive("FMQT_girl"))
		{
			sld = CharacterFromID("FMQT_girl");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
		}
		if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin")
		{
			DeleteAttribute(pchar, "questTemp.FMQP");
			sld = CharacterFromID("PortPax_waitress");
			DelLandQuestMark(sld);
		}
		if (CharacterIsAlive("FMQG_cureer"))
		{
			sld = CharacterFromID("FMQG_cureer");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
		}
		if (CharacterIsAlive("Guide_y"))
		{
			sld = CharacterFromID("Guide_y");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
		}
		break;

	case "gambit_1_1":
		dialog.text = "¿Has logrado juntar un millón? ¡Buen trabajo, Charles, simplemente impecable! Pero Philippe de Poincy, desafortunadamente, ya no está en su residencia, ha partido por asuntos de la Sociedad en una expedición secreta. Así que tendrás que esperar un poco antes de visitarlo.";
		link.l1 = "¡Al diablo contigo y tus asuntos secretos! Pensé que habría terminado con todo esto y volvería a casa, y ahora...";
		link.l1.go = "gambit_1_2";
		break;

	case "gambit_1_2":
		dialog.text = "Y ahora te has abierto a la oportunidad de ganar mucho más dinero y no solo eso. Hermano, el hecho de que hayas reunido la cantidad solicitada por el viejo zorro es increíble, pero no estaría tan confiado y tan tranquilo... De Poincy es todo un anguila resbaladiza, y ha mostrado mucho interés en tu modesta persona, y...";
		link.l1 = "¿Y ahora temes que un millón no será suficiente para él? ¿O es que has dejado algo fuera la última vez?";
		link.l1.go = "gambit_1_3";
		break;

	case "gambit_1_3":
		dialog.text = "No temo a nada, pero debo advertirte que Poincy no es un hombre simple. Mientras él está ausente, tienes la oportunidad de construirte cierta reputación, para que puedas hablar con él como un igual, no como un señor y un servidor. Por lo tanto, insistentemente te llamo a seguir mi plan, que te expondré ahora mismo.";
		link.l1 = "Está bien. No sirve de nada llorar sobre la leche derramada. Me quedaré en este infierno un poco más. De Poincy no va a estar navegando por ahí para siempre. Ponme al tanto de tu plan.";
		link.l1.go = "gambit_2";
		break;

	case "gambit_1":
		dialog.text = "¡Oh! Una respuesta encomiable. Me alegra, Charles, que te hayas convertido en un hombre. Sin embargo, no seas tan severo con tu hermano. Concedido, tengo algo que decirte. He estado esperando nuestro reencuentro, y ya he desarrollado un plan para lo que harás a continuación.";
		link.l1 = "Bien. Entonces, infórmame.";
		link.l1.go = "gambit_2";
		break;

	case "gambit_2":
		dialog.text = "Mira. Claro, el dinero juega un papel importante en el Caribe, como en cualquier otro lugar, pero el dinero no puede resolverlo todo. Un hombre exitoso no solo debe tener una bolsa pesada, sino también conexiones extensas y variadas, y no con gente de baja calaña, sino con personas que significan algo en este mundo.\nNo importa de qué nacionalidad o estamento sean. Las conexiones abren puertas que no se pueden abrir solo con dinero. La combinación de 'dinero más conexiones' le da al hombre la cosa más valiosa del mundo: el poder.\nDeberías considerar establecer tales conexiones y no podrás hacerlo realizando trabajos de carga, comerciando, con piratería menor o incluso ganando el favor de los gobernadores.";
		link.l1 = "¿Qué propones?";
		link.l1.go = "gambit_3";
		break;

	case "gambit_3":
		dialog.text = "No hay tantas organizaciones poderosas en el Caribe. Una de ellas es la Compañía Holandesa de las Indias Occidentales. Puedes unirte a ellos. Su sede está en Willemstad, en Curazao. La Compañía a menudo contrata a capitanes independientes y ofrece contratos especiales a largo plazo a los más útiles de ellos. \nSi tienes suerte, podrías hacer una carrera decente allí. He oído que están experimentando serios problemas ahora: algún corsario inglés se ha alzado en armas contra la Compañía y está hundiendo constantemente sus barcos. No pueden hacer nada contra él, es un oficial de la armada, lo que lo hace demasiado duro para ellos.\nDicen que está de alguna manera conectado con la inteligencia militar británica y son personas muy serias. Así que, tal vez, tomar el lado de este capitán podría ser incluso más rentable para ti, pero el problema es que no conozco su nombre, solo sé que Antigua es su base operativa.\nPuedes navegar allí y preguntar. También he oído hablar de alguna organización extraña que también participa en este conflicto anglo-holandés, pero no sé de qué lado están. Todo lo que sé es que los rastros conducen a Barbados, a Bridgetown...";
		link.l1 = "¿Así que propones que me aliste al servicio de los holandeses o busque un capitán sospechoso o una 'organización' aún más sospechosa?";
		link.l1.go = "gambit_4";
		break;

	case "gambit_4":
		dialog.text = "La decisión es tuya. En cualquier caso, no tendrás otra manera de integrarte rápidamente con las personas que deciden el destino de otros en el Caribe y poseen un poder significativo. Espero que no se te haya metido en la cabeza que dos o tres favores para el gobernador te llevarán directamente a la armada real.";
		link.l1 = "Sabes, querido hermano. En realidad, no esperaba una carrera militar en la marina francesa. Dios me libre de terminar como tú, atrapado en una celda por alguna tarea que no logré llevar a cabo... Está bien, entendí. Creo que encontraré el Cuartel General de la Compañía Holandesa sin mucha dificultad, pero no tengo ni idea de cómo buscar el resto de las partes.";
		link.l1.go = "gambit_5";
		break;

	case "gambit_5":
		dialog.text = "En cuanto al corsario inglés, puedes preguntar en St. John's, Antigua. Alguien definitivamente podrá decirte. Diles que buscas trabajo con la flota inglesa. En cuanto a 'la tercera fuerza', puedes hablar con la gente en Bridgetown sobre eso. Seguramente alguien allí tiene que estar conectado con esta organización.";
		link.l1 = "¿Su trabajo será al menos compensado? La Compañía, este corsario... ¿O todo será por el bien de las 'conexiones'?";
		link.l1.go = "gambit_6";
		break;

	case "gambit_6":
		dialog.text = "Charles, me estás sorprendiendo. La Compañía Holandesa de las Indias Occidentales maneja sumas que un rey envidiaría. El corsario del que te hablé ha saqueado tantos barcos holandeses que ya debe estar rebosante de riqueza. Y la gente de la 'organización' no solo tiene mucho dinero. Tienen un montón de dinero.\nTrabajar para ellos siempre te garantizará un buen pedazo del pastel. Gente como ellos siempre juegan en grande. Y si eres listo, siempre puedes jugar tu propio juego y ganar aún más.";
		link.l1 = "Está bien. Lo pensaré y decidiré cuál es mi mejor opción. ¿Tienes alguna otra instrucción?";
		link.l1.go = "gambit_7";
		break;

	case "gambit_7":
		dialog.text = "Sí. Deberías aprender a usar las herramientas de navegación. Eh, muchos navegantes solo pueden orientarse por la brújula y las estrellas y no pueden estimar las coordenadas. Y esto es crítico.\nEntonces. Usa un boussole para estimar la latitud. Es una herramienta bastante rara y no la encontrarás en las tiendas, pero puedes fabricarla tú mismo usando dos artículos comunes: una brújula y un astrolabio. Aquí, toma las instrucciones.\nEstimando la longitud es un poco más complicado. Necesitarás un cronómetro clasificado. Puedes hacer uno a partir de un cronómetro de barco común ajustándolo con un reloj de arena. El problema es que tal herramienta funciona eficientemente solo durante un mes antes de volverse demasiado inexacta debido a errores.\nUn cronómetro siempre requiere ser reajustado. Los relojes de arena se pueden comprar en la oficina de la Compañía Holandesa de las Indias Occidentales. Yo también compré cronómetros allí. Aquí, toma estas instrucciones.";
		link.l1 = "Gracias. Me pondré a estudiar de inmediato.";
		link.l1.go = "gambit_8";
		break;

	case "gambit_8":
		AddQuestRecordInfo("Recipe", "bussol");
		SetAlchemyRecipeKnown("bussol");
		AddQuestRecordInfo("Recipe", "clock2");
		SetAlchemyRecipeKnown("clock2");
		dialog.text = "Intenta adquirir todas estas herramientas lo antes posible. Todos los capitanes experimentados y respetados operan con latitud y longitud. Se te considerará un novato en la navegación hasta que sepas qué significan esos números.\nBueno, vuelve para alardear tan pronto como tengas éxito en los asuntos que hemos discutido recientemente. ¡Buena suerte, Charles!";
		link.l1 = "Gracias, querido hermano. ¡Siento que seguro será de gran utilidad!";
		link.l1.go = "gambit_9";
		break;

	case "gambit_9":
		DialogExit();
		NextDiag.CurrentNode = "First time";
		pchar.questTemp.Sharlie = "gambit";	   // флаг на Голландский Гамбит
		pchar.questTemp.HWIC.CanTake = "true"; // Голландский Гамбит доступен для взятия
		AddQuestRecord("Sharlie", "20");
		npchar.greeting = "mishelle_3";
		AddMapQuestMarkCity("Bridgetown", false);
		AddMapQuestMarkCity("Villemstad", false);
		AddMapQuestMarkCity("SentJons", false);
		AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
		AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
		// Rebbebion, убираем марки
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("Fortfrance");
		break;

	case "gambit_fale":
		dialog.text = "¿Y de qué tienes que presumir?";
		link.l1 = "Nada por ahora. He encontrado las tres organizaciones y he intentado trabajar con ellas, pero como un cigarro, todo se desvaneció en humo literalmente en la primera etapa. Es como si el destino estuviera amañado en mi contra...";
		link.l1.go = "gambit_fale_1";
		break;

	case "gambit_fale_1":
		dialog.text = "Entonces, los rumores son ciertos... Querido hermano, el destino no está en tu contra. Se llama cerebro obtuso y manos torcidas. Me has decepcionado. Vuelve a Francia, no hay nada más que hacer aquí.";
		link.l1 = "Pero cómo...";
		link.l1.go = "gambit_fale_2";
		break;

	case "gambit_fale_2":
		dialog.text = "Ya no es asunto tuyo. Me encargaré yo mismo. Tengo a otras personas más capaces para ayudarme a resolver mi problema. Temía que confiar en ti me retuviera aquí hasta el fin de mis días. En fin. Lárgate de aquí, vuelve con tus cortesanas.";
		link.l1 = "Está bien, vete al infierno...";
		link.l1.go = "gambit_fale_3";
		break;

	case "gambit_fale_3":
		DialogExit();
		NextDiag.CurrentNode = "gambit_fale_4";
		npchar.lifeday = 30;
		break;

	case "gambit_fale_4":
		dialog.text = "No tengo nada de qué hablar contigo. Vete.";
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "gambit_fale_4";
		break;

	case "saga":
		switch (pchar.questTemp.HWIC.Detector)
		{
		case "holl_win":
			sTemp = "Entré al servicio de la Compañía Holandesa de las Indias Occidentales y me convertí en agente de tareas especiales y amigo íntimo del viceadministrador de la Compañía, Lucas Rodenburg. Conseguí llevar a cabo varias misiones serias, en particular, liquidé al corsario inglés real. Además, ahora tengo mi propia casa personal en Antigua y mis bolsillos están llenos de dinero..";
			break;

		case "holl_fail":
			sTemp = "He entrado al servicio de la Compañía Holandesa de las Indias Occidentales, sin embargo los asuntos han ido modestamente, he fallado en una tarea importante, y fui obligado a una baja deshonrosa sin nada.";
			break;

		case "eng_win":
			sTemp = "He encontrado al verdadero corsario inglés, Richard Fleetwood, y he llevado a cabo varias tareas importantes en nombre de la armada inglesa, en particular, liquidé el 'barco fantasma' pirata y acabé con el mismísimo Lucas Rodenburg, viceadministrador de la Compañía. Además, ahora tengo mi propia casa en Antigua y mis bolsillos están llenos de dinero.";
			break;

		case "eng_win_half":
			sTemp = "He encontrado al verdadero corsario inglés, Richard Fleetwood, y he llevado a cabo varias tareas importantes en nombre de la armada inglesa, en particular, he liquidado al 'barco fantasma' pirata. Por supuesto, Fleetwood partió hacia Inglaterra y mi servicio con él ha terminado, pero aún así...";
			break;

		case "eng_fail":
			sTemp = "He entrado en servicio con el corsario inglés de Antigua, sin embargo los asuntos han ido modestamente. He fallado en una tarea importante, y me he visto obligado a una baja deshonrosa sin nada.";
			break;

		case "self_win":
			sTemp = "He descubierto la 'organización secreta' de Barbados, he empezado a jugar mi propio juego y he conseguido bastantes cosas: Acabé con ese corsario inglés, Richard Fleetwood, metí entre rejas a Lucas Rodenburg, el viceadministrador de la Compañía, me hice íntimo amigo del gobernador Matthias Beck y del director de la Compañía, Peter Stuyvesant. Además, ahora tengo mi propia casa personal en Antigua y mis bolsillos están llenos de dinero.";
			break;

		case "self_fail":
			sTemp = "He descubierto la 'organización secreta' en Barbados, empecé a rodar algún juego por mi cuenta, sin embargo todo se fue al traste a la hora de la verdad...";
			break;
		}
		dialog.text = "¿Y? Vamos, querido hermano, no lo alargues. ¿Cuál es la buena nueva? Algunos rumores han llegado a mí sobre tu ardiente laboriosidad, pero quería escucharlo todo de ti.";
		link.l1 = sTemp;
		link.l1.go = "saga_1";
		break;

	case "saga_1":
		if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "eng_win" || pchar.questTemp.HWIC.Detector == "self_win")
		{
			dialog.text = "¡Excelente! ¡Gran trabajo, Charles! ¡No dudé de ti ni por un minuto! Llegarás lejos, querido hermano... Ocupándote así y estableciendo relaciones con gente tan importante, claro, no esperaba eso. ¡Felicidades!";
		}
		else
		{
			dialog.text = "No te enfades, Charles. Si no resultó, no hay nada que puedas hacer al respecto. Usaremos otros medios para lograr los resultados que necesitamos.";
		}
		link.l1 = "¿Qué hacemos ahora, Michel? ¿Es hora de visitar al Caballero de Poincy? Me siento bastante preparado para una conversación con él.";
		link.l1.go = "saga_2";
		break;

	case "saga_2":
		dialog.text = "¿Ya has logrado reunir la suma requerida de un millón de pesos?";
		if (sti(pchar.money) >= 1000000)
		{
			link.l1 = "Sí, actualmente poseo la suma requerida.";
			link.l1.go = "saga_3_1";
		}
		else
		{
			link.l1 = "No, aún no tengo esa cantidad de dinero.";
			link.l1.go = "saga_3_2";
		}
		break;

	case "saga_3_1":
		dialog.text = "¡Excelente! Entonces no estaré sentado en este casamata por mucho más tiempo... Ve a Capsterville, está en San Cristóbal, y pide una audiencia con de Poincy. Debería estar en el palacio del gobernador donde reside. Más allá de eso, juzga según la situación y recuerda: Poincy es astuto, muy astuto... Tengo un mal presentimiento de que todo este asunto no va a ser tan fácil. ¡Ve, hermano, y ten cuidado!";
		link.l1 = "Tendré en cuenta tus precauciones, Michel. No te preocupes, tampoco nací ayer. Voy al viejo zorro. ¡Hasta luego!";
		link.l1.go = "saga_4";
		break;

	case "saga_3_2":
		dialog.text = "Entonces no tiene sentido hablar con de Poincy. Ni siquiera te dejará entrar. Reúne el dinero, hermano mío, ya tienes bastante experiencia, así que no será mucho problema. Navega a Capsterville en San Cristóbal tan pronto como lo tengas.\nEl Caballero debe estar en su palacio del gobernador. Pide una audiencia y te dejarán entrar. Luego compruébalo por ti mismo y ten cuidado: Poincy es astuto, muy astuto... Algo me dice que esta historia no terminará así como así.";
		link.l1 = "Tendré en cuenta tus precauciones, Michel. No te preocupes, tampoco nací ayer. Tan pronto como reúna el dinero, iré directo al viejo zorro. ¡Hasta luego!";
		link.l1.go = "saga_4";
		break;

	case "saga_4":
		DialogExit();
		AddMapQuestMarkCity("Charles", false);
		AddLandQuestMark(characterFromId("Puancie"), "questmarkmain");
		npchar.quest.givelink_saga = "true";
		NextDiag.TempNode = "First time";
		pchar.questTemp.Sharlie = "saga"; // флаг на Пиратскую Сагу
		break;

	case "saga_5":
		dialog.text = "¡Nom d'une pipe! Eso es exactamente lo que temía. ¡Poincy te ha estado siguiendo los pasos durante mucho tiempo, Charles! ¡Por eso ha mostrado tanto interés en ti! Te has forjado toda una reputación en el Caribe y por eso ha decidido usarte para cumplir encargos que se fueron al garete...";
		link.l1 = "Tengo la sensación, Michel, de que estabas bien al tanto y simplemente no querías informarme antes. Todo está saliendo demasiado bien... Primero el dinero, ahora tu trabajo... Eso no sucede por casualidad.";
		link.l1.go = "saga_6";
		break;

	case "saga_6":
		dialog.text = "Charles, no busques un mensaje secreto donde no lo hay. Si tan solo le hubieras dado a Poincy el dinero el primer día que llegaste aquí... Bueno, quiero decir, supongamos que lo tenías. El Caballero no te habría pedido nada más. Pero ahora que ha mostrado interés en ti y ha visto con qué facilidad te has instalado aquí y lo que has podido lograr, ha decidido explotar tus talentos.";
		link.l1 = "Correcto... porque tus talentos ya no le satisfacen, ¿verdad? ¡Merde! Muy bien. Veo que estoy en un callejón sin salida aquí. ¿Quién es este hereje? ¿Cómo puedo encontrarlo?";
		link.l1.go = "saga_7";
		break;

	case "saga_7":
		dialog.text = "¡No hay necesidad de buscarlo! Nunca deja Tortuga y se mantiene bajo la protección del bastión que construyó y las hordas de hugonotes leales, que sirven como soldados en su guarnición. Por lo tanto, cada soldado le es leal. Poincy se refería a François Levasseur, el gobernador de Tortuga.\nLos españoles aún no pueden sacarlo de allí y de Poincy creía seriamente que yo podría hacerlo solo sin ningún apoyo de la marina, solo porque iniciar una guerra civil sería un error político debido a la cercana ubicación de la guarnición de Santo Domingo.\nEl viejo miserable está demasiado preocupado por su carrera limpia y una pensión venidera para arriesgarlo todo de esa manera. No obstante, Levasseur ha ido demasiado lejos y representa un peligro para la corona.\nDe Poincy, quien nombró a Levasseur a su posición actual él mismo, considera a este temible hugonote un enemigo personal y está ansioso por reemplazarlo con el Caballero de Malta de Fontenay, mi superior inmediato bajo cuyo mando he llegado aquí desde Malta.";
		link.l1 = "¡Glorioso! Primero, hacer un millón, luego asesinar al gobernador de Tortuga. ¿Cuál será mi próxima misión? ¿Organizar una conspiración en el Escorial? ¡Mierda! No me sorprende que hayas estropeado eso. Liquidar al gobernador no es como robar a los mercaderes españoles. Espero que tuvieras algún plan cuando juraste sacar las castañas del fuego.";
		link.l1.go = "saga_8";
		break;

	case "saga_8":
		dialog.text = "Para ser completamente honesto, no tenía ningún plan ya que iba a dejar el servicio de todos modos y regresar a nuestra mansión familiar en caso de éxito de mi arriesgada empresa. Personalmente, no me importa un comino los problemas de de Poincy.\nSeguramente, él se volvería mucho más flexible tan pronto como hubiera visto el oro indio... Bueno, actualmente tiene todas las cartas de triunfo contra nosotros. Supongo que me quedaré aquí mientras Levasseur sea el gobernador de Tortuga.";
		link.l1 = "¿Y por qué no habrían de cargar los malteses liderados por de Fontenay, con la vista puesta en el asiento del gobernador, sobre Tortuga ellos mismos?";
		link.l1.go = "saga_9";
		break;

	case "saga_9":
		dialog.text = "Imagina eso. La orden declara la guerra a Louis. ¡No seas absurdo! Un escándalo así no es una opción. Solo un individuo privado puede capturar Tortuga. Un pirata, o un aventurero católico como tú.\nDespués de eso, puede rendir la isla al control del nuevo gobernador que de Poincy enviará. Un acto así se verá grandioso desde el punto de vista de los grandes políticos.";
		link.l1 = "¿Entonces hay algún sentido en negociar con piratas?";
		link.l1.go = "saga_10";
		break;

	case "saga_10":
		dialog.text = "El problema es que Levasseur tiene autoridad entre muchos piratas de la Hermandad y más allá. Les permite esconderse detrás de las baterías de Tortuga y vender lo que han saqueado libremente por una parte del botín.\nSolía compartir con de Poincy, pero ya no está compartiendo. Los barcos piratas protegerán Tortuga y su guarnición, lo que hace que asaltar el fuerte sea aún más difícil.";
		link.l1 = "¿Crees que este asunto es una causa perdida?";
		link.l1.go = "saga_11";
		break;

	case "saga_11":
		dialog.text = "Siempre hay una solución, hermanito. Simplemente no siempre es visible en la superficie. No todos los piratas simpatizan con los hugonotes de Tortuga. Conozco al menos a dos piratas autoritarios que consideran a Levasseur un traidor y escoria. Estoy hablando de Steven Dodson, también conocido como Shark, y del legendario barón de la Bahía de los Mosquitos, Jan Svenson.\nNo sé dónde encontrar al Shark, he oído rumores de que algo ha pasado y tuvo que abandonar su base en Isla Tesoro. Pero siempre puedes encontrar a Svenson en Blueweld. Es una figura significativa allí.";
		link.l1 = "¿Crees que este... Svenson me ayudará?";
		link.l1.go = "saga_12";
		break;

	case "saga_12":
		dialog.text = "Lo hará si le ayudas. Las cosas no le van muy bien en este momento y el hombre podría usar gente leal y talentosa. Primero tendrás que demostrarle tu utilidad antes de tener una conversación seria. Encontrarás la manera de hacerlo cuando llegues allí. Me resulta difícil dar consejos desde aquí.\n¿Supongo que has decidido seguir adelante, Charles, ya que sigues haciendo preguntas?";
		link.l1 = "Verás, Michel, acabo de entregar una pila de mi propia plata a de Poincy. ¡La reuní con sangre, sudor y lágrimas! No estoy seguro de que hubieras arriesgado siquiera un solo louis d'or por mí si estuvieras en mi lugar.";
		link.l1.go = "saga_13";
		break;

	case "saga_13":
		dialog.text = "Charles...";
		link.l1 = "¡No me interrumpas! Sería una estupidez volver con las manos vacías a padre. El problema aún no está resuelto, estás tras las rejas y bajo amenaza de ser condenado por traición a la Sociedad. Poincy no dudaría en mancillar el nombre de Monper, si no llevo a cabo su 'solicitud'. Eso estaba escrito en su rostro. Así que partiré a Blueweld para encontrar una manera de acercarme a Svenson. Mientras tanto, piensa en qué más has 'olvidado' contarme. Por ejemplo, es la primera vez que oigo de ti sobre algún oro indio que tenías que llevar a de Poincy.";
		link.l1.go = "saga_14";
		break;

	case "saga_14":
		dialog.text = "Hay cosas que es mejor que permanezcan ocultas. Tienes razón, no te conté todo lo que sé. Quizás, algún día te cuente más, pero no antes de que te encargues de Levasseur, sería un conocimiento inútil por ahora.\nNo tengo duda de que tu conmovedor cuidado por mí es causado solo por el deseo de salvar el honor de nuestra familia. Al salvarme, te estás salvando a ti mismo en primer lugar y en segundo lugar la posibilidad de visitar las mejores casas en París. ¿Me equivoco?";
		link.l1 = "Me temo que ya no es así, hermano. Tenías razón. Estos últimos meses que pasé en el Caribe han cambiado cada fibra de mí y toda mi perspectiva. Y estoy seguro de que es para mejor. Ya no necesito realmente esos salones parisinos y un día podré seguir adelante sin el nombre de Monpe. De Mor no es peor...";
		link.l1.go = "saga_15";
		break;

	case "saga_15":
		dialog.text = "...";
		link.l1 = "Y ahora lo único que realmente me duele es el hecho de que tu vergüenza dejará una marca en nuestro viejo padre. Él no conoce el verdadero statu quo ni lo que realmente ocurre aquí. Además, como correctamente dijiste, el patrimonio debe ser restaurado de su estado ominoso. Y el millón pagado por tu libertad ha aligerado significativamente mi tesorería, por lo que claramente requerirá ser rellenada.";
		link.l1.go = "saga_16";
		break;

	case "saga_16":
		dialog.text = "Has comprendido excelentemente todas las lecciones de la vida, Charles. Estoy verdaderamente feliz por ti. Y me alegra que hayas seguido adelante y aceptado la petición de de Poincy en lugar de zarpar de regreso a Francia. Espero que todo salga bien para ti y que puedas llevar a cabo lo que yo no pude hacer.";
		link.l1 = "Me temo que no me queda otra opción. Como desde mi primer día en el Caribe. Nos vemos luego, Michel. Creo que nuestro próximo encuentro incluirá la orden para tu liberación.";
		link.l1.go = "saga_17a";

		break;

	// Addon 2016-1 Jason Пиратская линейка
	case "saga_17a":
		dialog.text = "¡Espera un momento! Antes de ir a Jan Svenson, asegúrate de visitar a Marcus Tyrex. Él es el Guardián del Código. Gobierna La Vega en La Española. Tiene una autoridad ilimitada entre los piratas y los españoles le temen a muerte.";
		link.l1 = "¿Podría ayudarme con nuestro asunto?";
		link.l1.go = "saga_17b";
		break;

	case "saga_17b":
		dialog.text = "Dudo que sí. No puedo decir realmente de qué lado está, lo más probable es que esté solo por sí mismo. Necesitarás al Shark y a Svenson de todos modos, pero en este momento, Tyrex es el pirata más poderoso por aquí. Lo eligieron como Guardián del Código por una razón. No deberías ignorar a una figura tan importante. Podría ser útil conocer mejor a los piratas antes de encontrarte con Svenson. Incluso podrías hacerte un nombre entre ellos...";
		link.l1 = "Y una vez más, estamos de vuelta con la jerga pirata. No hay manera de que me libre de esto, ¿verdad? Muy bien. Le haré una visita.";
		link.l1.go = "saga_17c";
		break;

	case "saga_17c":
		dialog.text = "Ser pirata y hacer negocios con ellos es un juego completamente diferente, hermano. Espero que veas la diferencia. Ve a La Vega y pídele trabajo a Tyrex. Si no os lleváis bien, que le den y vuelve a mí.";
		link.l1 = "Muy bien, Michel. ¡Nos vemos!..";
		link.l1.go = "saga_17d";
		break;

	case "saga_17d":
		DialogExit();
		AddQuestRecord("Sharlie", "22");
		npchar.greeting = "mishelle_3";
		pchar.questTemp.Mtraxx = "to_lavega";
		pchar.questTemp.Saga = "pirate_line";
		AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
		AddMapQuestMarkCity("LaVega", false);
		break;

	case "saga_17e":
		dialog.text = "Al menos lo has intentado. Tuviste la oportunidad de 'familiarizarte' con un infame barón pirata. No importa. Ve a Jan Svenson, él está en Blueweld. Intenta convertirlo en tu aliado o nuestro trato con Levasseur se convertirá en un derramamiento de sangre.";
		link.l1 = "Bien. Estoy en camino.";
		link.l1.go = "saga_17";
		pchar.questTemp.Mtraxx = "fail_end";
		break;

	case "saga_17f":
		dialog.text = "Me alegra que te hayas detenido, hermano. Una vez te dije que es un juego totalmente diferente ser pirata y hacer negocios con ellos. Y has perdido el rumbo. Espero que no cometas el mismo error con Shark y Svenson. Haz el trabajo pero mantén tu distancia de ellos. Después de todo, eres un noble francés, así que estate por encima de ellos. Ahora ve a Jan Svenson, él está en Blueweld. Trata de hacerlo tu aliado o nuestro trato con Levasseur se convertirá en un derramamiento de sangre.";
		link.l1 = "Está bien. Estoy en camino.";
		link.l1.go = "saga_17";
		pchar.questTemp.Mtraxx = "fail_end";
		break;

	case "saga_17g":
		dialog.text = "Me alegra mucho oírlo, si estás diciendo la verdad. Pero, ¿puedo realmente confiar en la palabra de un pirata que quema ciudades, incluso si son españolas, y asesina a civiles, incluidas mujeres?";
		// belamour legendary edition -->
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice"))
		{
			if (pchar.questTemp.Mtraxx.Retribution.Choice == "good")
			{
				link.l1 = "Detente... Lamento mucho lo que hice durante mi tiempo con Tyrex. He visto el infierno con mis propios ojos, hermano... No, ¡está hecho! He terminado con la piratería y de ninguna manera volveré a poner un pie en La Vega. Haré todo lo necesario para restaurar mi buen nombre.";
				link.l1.go = "saga_17gx";
			}
			if (pchar.questTemp.Mtraxx.Retribution.Choice == "bad")
			{
				link.l1 = "Créelo o no. Tú estás tras las rejas, no yo.";
				link.l1.go = "saga_17gxa";
			}
		}
		else // заглушка
		{
			link.l1 = "Detente... Realmente me arrepiento de las abominaciones que he hecho mientras trabajaba con Tyrex. ¡Vi el infierno con mis propios ojos, hermano! .. ¡No, mi pasado pirata ha terminado! Ya no estoy en La Vega. Tomaré todas las medidas para restaurar mi buen nombre.";
			link.l1.go = "saga_17gx";
		}
		break;

	case "saga_17gxa":
		dialog.text = "Oh, hermano... No enfades a Dios... Espero que esto no vuelva a suceder con Svenson y Shark. Haz las cosas, pero mantente al margen y recuerda qué clase de personas son. No es adecuado para un noble francés convertirse en como ellos. Sé superior. Ahora ve a Jan Swenson en Blueweld y trata de encontrar una manera de acercarte al viejo corsario. Sin él, no será posible resolver el problema con Levasseur con poca efusión de sangre.";
		link.l1 = "Está bien. No me demoraré.";
		link.l1.go = "saga_17";
		pchar.questTemp.Mtraxx = "full_complete_end";
		break;

	case "saga_17gx":
		dialog.text = "Tendrás que esforzarte mucho, hermano. ¿Recuerdas lo que te dije una vez? Que es un juego totalmente diferente ser pirata y hacer negocios con ellos. Tú... Olvídalo, espero que no cometas el mismo error con Shark y Svenson. Haz el trabajo pero mantén tu distancia de ellos. Después de todo, eres un noble francés, así que mantente por encima de ellos. Ahora ve a Jan Svenson, está en Blueweld. Intenta hacerlo tu aliado o nuestro trato con Levasseur se convertirá en un derramamiento de sangre.";
		link.l1 = "Está bien. Estoy en camino.";
		link.l1.go = "saga_17";
		pchar.questTemp.Mtraxx = "full_complete_end";
		break;

	case "saga_17":
		DialogExit();
		AddQuestRecord("Sharlie", "22_1");
		pchar.questTemp.Saga = "blueveld";
		LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
		npchar.greeting = "mishelle_3";
		if (CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince"))
		{
			DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince");
			SetFunctionTimerCondition("DelCharleePrince", 1, 0, 0, false);
		}
		AddMapQuestMarkCity("SantaCatalina", false);
		AddLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"), "questmarkmain");
		AddLandQuestMark(characterFromId("JS_girl"), "questmarkmain");
		break;

	case "Base_fight":
		dialog.text = "¡Ahora no es el momento adecuado para conversar, hermano! ¡El enemigo está en nuestro refugio!";
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Base_fight";
		break;

	case "Base_afterfight":
		sTemp = "";
		// belamour legendary edition фикс проверки мундира с мушкетом
		if (IsUniformEquip())
			sTemp = "Veo que te has convertido en capitán de la marina... No lo vi venir para ser honesto. ¡Te felicito de verdad!";
		dialog.text = "¡Llegas justo a tiempo, querido hermano! ¡Estoy tan feliz de verte! Estos malditos castellanos ya han tomado completamente Saint-Pierre. ¡Pensé que estábamos perdidos seguro!" + sTemp + "";
		link.l1 = "No estamos fuera de peligro, la ciudad está despejada pero los canallas están atrincherados en el fuerte y hay un enorme escuadrón liderado por un acorazado. Pero te traigo noticias bastante encantadoras: ¡Michel, eres libre!";
		link.l1.go = "Base_afterfight_1";
		break;

	case "Base_afterfight_1":
		dialog.text = "¡No puedo creer lo que oigo! ¿Puede ser verdad? ¡¿Libertad?!";
		link.l1 = "Levasseur está muerto, Tortuga ahora está dirigida por tu ex comandante, y el viejo zorro Poincy ha retirado todos sus cargos contra ti. De ahora en adelante, nada amenaza nuestro buen nombre.";
		link.l1.go = "Base_afterfight_2";
		break;

	case "Base_afterfight_2":
		dialog.text = "Dudé hasta el último minuto... Me has sorprendido, Charles, y has tenido éxito donde yo sufrí un fiasco angustioso.";
		link.l1 = "Audaces fortuna juvat, hermano... Como puedes ver, ahora también sé latín. ¿Dónde está la llave de tu celda?";
		link.l1.go = "Base_afterfight_3";
		break;

	case "Base_afterfight_3":
		dialog.text = "La llave de mi casamata debería estar en el escritorio del oficial de servicio. Búscala allí. Tal vez se haya caído al suelo y se haya deslizado a algún lugar...";
		link.l1 = "¡Iré a encontrarlos y regresaré!";
		link.l1.go = "Base_afterfight_4";
		break;

	case "Base_afterfight_4":
		DialogExit();
		pchar.questTemp.Sharlie.DefendSP.SeekKey = true;
		LAi_CharacterDisableDialog(npchar);
		break;

	case "Base_afterfight_6":
		dialog.text = "¡Libertad al fin! ¡Oh, cuánto tiempo he esperado!";
		link.l1 = "No puedes siquiera imaginar cuánto he esperado este momento... Michel, ¿tenemos gente capaz de luchar?";
		link.l1.go = "Base_afterfight_7";
		break;

	case "Base_afterfight_7":
		dialog.text = "¿Qué tienes en mente, Charles?";
		link.l1 = "La amenaza que presentan los españoles aún no se ha evaporado. ¡Quiero sacarlos del fuerte y luego unir fuerzas para atacar la escuadra tanto por tierra como por mar! ¡Usando los cañones del bastión podré enfrentarme al acorazado!";
		link.l1.go = "Base_afterfight_8";
		break;

	case "Base_afterfight_8":
		dialog.text = "Tenemos personal. Una gran cantidad de caballeros ha partido para proteger el palacio del gobernador. Seguro que podremos encontrar a alguien en la ciudad... Reuniré a toda la gente que pueda encontrar. ¡Nos vemos más allá de las puertas de la ciudad!";
		link.l1 = "...";
		link.l1.go = "Base_afterfight_9";
		break;

	case "Base_afterfight_9":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_SetImmortal(npchar, false);
		LAi_SetCheckMinHP(npchar, 10, true, ""); // скрытое бессмертие
		LAi_SetHP(npchar, 500, 500);
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 30.0);
		pchar.quest.DefendSP_base2.win_condition.l1 = "location";
		pchar.quest.DefendSP_base2.win_condition.l1.location = "FortFrance_Town";
		pchar.quest.DefendSP_base2.function = "DefendSP_CloseTown";
		AddQuestRecord("Sharlie", "36");
		break;

	case "Fort_attack":
		dialog.text = "Aquí está hermano, nuestro ejército. Toda la gente que pude encontrar. No son muchos en términos de números, ¡pero lucharemos por nuestra Patria! ¡Echaremos a estos malditos intrusos del fuerte! El elemento sorpresa nos ayudará, no esperan nuestro ataque. ¡Adelante!";
		link.l1 = "¡Dulce et decorum est pro patria mori! ¡Adelante!";
		link.l1.go = "Fort_attack_1";
		break;

	case "Fort_attack_1":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		for (i = 1; i <= 7; i++)
		{
			sld = CharacterFromID("DefendSP_frafort_" + i);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		}
		chrDisableReloadToLocation = false; // открыть локацию
		LocatorReloadEnterDisable("FortFrance_Exittown", "reload2_back", false);
		LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", true);
		LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", true);
		pchar.quest.DefendSP_fort2.win_condition.l1 = "location";
		pchar.quest.DefendSP_fort2.win_condition.l1.location = "FortFrance_fort";
		pchar.quest.DefendSP_fort2.function = "DefendSP_FortBattle";
		locations[FindLocation("FortFrance_fort")].QuestCapture = true;
		break;

	case "Fort_attack_2":
		dialog.text = "¡Está hecho, hermano! ¡El fuerte es nuestro!";
		link.l1 = "Es una lástima que haya sufrido tanto daño en la batalla con el escuadrón español... pero aún es bastante capaz de liderar una batalla.";
		link.l1.go = "Fort_attack_3";
		break;

	case "Fort_attack_3":
		dialog.text = "Interpretaré mi papel. ¡Cargaremos los cañones y daremos al enemigo un golpe contundente! Pero solo después de ver a tu escuadrón acercarse, o de lo contrario el navío de línea nos convertirá rápidamente en aserrín.";
		link.l1 = "¡Reúne a la gente, Michel! ¡Voy a regresar inmediatamente a la costa!";
		link.l1.go = "Fort_attack_4";
		break;

	case "Fort_attack_4":
		dialog.text = "Charles, recuerda: ¡la parte más peligrosa del escuadrón es el navío de línea! Intenta eliminarlo primero. También concentraremos el fuego sobre él con lo que queda de la batería del fuerte.";
		link.l1 = "Muy bien, hermano. Quizás, debería capturarla.";
		link.l1.go = "Fort_attack_5";
		break;

	case "Fort_attack_5":
		dialog.text = "¡A juzgar por las circunstancias, no soy yo quien debería enseñarte! ¡Ahora deberíamos dejar de perder el tiempo!";
		link.l1 = "...";
		link.l1.go = "Fort_attack_6";
		break;

	case "Fort_attack_6":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
		LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", false);
		LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", false);
		LocatorReloadEnterDisable("Shore38", "boat", false); // выпустить в море
		// закрываем городские заведения
		for (i = 3; i <= 10; i++)
		{
			LocatorReloadEnterDisable("FortFrance_town", "reload" + i + "_back", true);
		}
		LocatorReloadEnterDisable("FortFrance_town", "reload91", true);
		LocatorReloadEnterDisable("FortFrance_town", "reload_jail", true);
		pchar.quest.DefendSP_fort3.win_condition.l1 = "location";
		pchar.quest.DefendSP_fort3.win_condition.l1.location = "shore38";
		pchar.quest.DefendSP_fort3.function = "DefendSP_BeforeSeaBattle";
		pchar.quest.DefendSP_sea1.win_condition.l1 = "location";
		pchar.quest.DefendSP_sea1.win_condition.l1.location = "Martinique";
		pchar.quest.DefendSP_sea1.function = "DefendSP_SeaBattle";
		AddQuestRecord("Sharlie", "37");
		break;

	case "Victory":
		dialog.text = "¡Gloria victoriosa! ¡Felicitaciones por tu victoria, hermano! ¡Fuiste grandioso! ¡Los españoles están completamente destruidos!";
		link.l1 = "Espero que eso les enseñe a pensarlo dos veces antes de atacar las colonias francesas.";
		link.l1.go = "Victory_1";
		break;

	case "Victory_1":
		dialog.text = "Ahora dime, Charles: ¿cuánto vale tu vida pasada... comparada con esta?";
		link.l1 = "No me lo recuerdes...";
		link.l1.go = "Victory_2";
		break;

	case "Victory_2":
		dialog.text = "¿Recuerdas lo que te dije durante nuestra primera reunión aquí? 'Te encantará esta vida', ¡eso es! Sí, y un enorme gracias a ti, hermano, por tu ayuda. Sin ti probablemente nunca habría logrado escapar de las confines de esa base subterránea.";
		link.l1 = "No lo menciones, Michel. Después de todo, eres mi hermano y estaba obligado a ayudarte.";
		link.l1.go = "Victory_3";
		break;

	case "Victory_3":
		dialog.text = "Solo mírate, hermano, estoy impresionado: tanta fuerza en los ojos, confianza en los movimientos, estatura en la postura... ¿a dónde se fue ese maldito artista y bufón de la corte? ¡En verdad! Has superado mis más atrevidas expectativas, a decir verdad, nunca pensé que te convertirías en... esto.\nIncluso... me asusta un poco. Porque no te detendrás ante nada para lograr tu objetivo. Eres bueno, demasiado bueno...";
		link.l1 = "Por alguna razón tengo problemas para entenderte una vez más. ¿Estás descontento conmigo otra vez?";
		link.l1.go = "Victory_4";
		break;

	case "Victory_4":
		dialog.text = "¡No! ¿De qué estás hablando?... ¡En absoluto! Solo estaba canalizando mi emoción.";
		link.l1 = "Está bien. Entonces, ¿qué harás ahora, hermano? ¿Seguirás sirviendo a la Sociedad? ¿O regresarás a nuestro patrimonio? Sí, y casi lo olvidaba: prometiste contarme sobre una cosa.";
		link.l1.go = "Victory_5";
		break;

	case "Victory_5":
		dialog.text = "¿Sobre qué exactamente?";
		link.l1 = "Sobre tu servicio para de Poincy. Sobre algún oro indio que ibas a traerle. Sobre todo lo que precedió a tu encarcelamiento. Hay mucho que no has logrado contarme, Michel, dejándome bastante a ciegas. Así que...";
		link.l1.go = "Victory_6";
		break;

	case "Victory_6":
		dialog.text = "Hermano, recuerdo perfectamente lo que dije. Te contaré todo. ¡Pero no en medio de una ciudad en llamas!\nAmbos tenemos muchas cosas que hacer ahora. Necesitas organizar tu escuadrón, arreglarlo y preparar los barcos de nuevo. Yo y el gobernador organizaremos y calmaremos a los lugareños.\nDiscutiremos todo mañana por la mañana con una copa de buen vino francés. Confía en mí, hermano, tengo un gran plan. Uno realmente grande. Pero no ahora. Visita al Abad Benoit mañana a las nueve de la mañana. Pasaré la noche en su casa, es un viejo amigo mío.";
		link.l1 = "Está bien, Michel. Entonces, está decidido. Espero con ansias nuestra conversación de mañana.";
		link.l1.go = "Victory_7";
		break;

	case "Victory_6A":
		dialog.text = "Diálogo 28.";
		link.l1 = "Está bien, Michel. Entonces está decidido. Espero con ansias nuestra conversación de mañana.";
		link.l1.go = "Victory_7";
		break;

	case "Victory_7":
		dialog.text = "¡No hace falta despedirse, Charles!";
		link.l1 = "...";
		link.l1.go = "Victory_8";
		break;

	case "Victory_8":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "DefendSP_OpenExit", -1);
		DeleteAttribute(pchar, "GenQuest.CannotWait"); // можно мотать время
		AddQuestRecord("Sharlie", "39");
		pchar.quest.DefendSP_final.win_condition.l1 = "Timer";
		pchar.quest.DefendSP_final.win_condition.l1.date.hour = 9;
		pchar.quest.DefendSP_final.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
		pchar.quest.DefendSP_final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.DefendSP_final.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		pchar.quest.DefendSP_final.function = "DefendSP_finaltalk";
		// раздача экспы
		ChangeCharacterNationReputation(pchar, FRANCE, 30);
		ChangeCharacterComplexReputation(pchar, "nobility", 10);
		ChangeCharacterComplexReputation(pchar, "authority", 10);
		ChangeCharacterComplexReputation(pchar, "fame", 15);
		ChangeOfficersLoyality("good_all", 10);
		AddComplexSeaExpToScill(500, 500, 500, 500, 500, 500, 0);
		AddComplexSelfExpToScill(300, 300, 300, 300);
		AddCharacterExpToSkill(pchar, "Leadership", 2000);
		AddCharacterExpToSkill(pchar, "Fortune", 1000);
		AddSimpleRumour("Todos los que residen en la colonia francesa están en deuda con usted, Capitán. ¡Defender Saint-Pierre del vil ataque de los españoles es toda una hazaña!", FRANCE, 30, 15);
		AddSimpleRumour("¡Es un honor para mí hablar con el valiente capitán que ha dejado huecos a un puñado de invasores españoles!", FRANCE, 30, 15);
		AddSimpleRumour("¡Los colonos franceses pueden dormir en paz, mientras valientes oficiales navales como usted están al servicio del Rey!", FRANCE, 30, 15);
		AddSimpleRumourCity("Todos estamos en deuda con usted, capitán. ¡Has salvado a nuestra colonia de la devastación!", "FortFrance", 30, 15, "");
		AddSimpleRumourCity("Es usted un oficial de marina valiente y astuto. Todos los que residen en Saint-Pierre rezan por usted, ¡sépalo!", "FortFrance", 30, 15, "");
		AddSimpleRumourCity("Eres el orgullo de nuestra nación y el héroe de Saint-Pierre. Nunca lo olvidaremos.", "FortFrance", 30, 15, "");
		npchar.greeting = "mishelle_0";
		break;

	case "kukulkan":
		PlaySound("Voice\Spanish\sharlie\mishelle-04.wav");
		dialog.text = "Así que nos encontramos de nuevo, " + pchar.name + "A pesar de mis advertencias, aún así continuaste buscándome y tus búsquedas te han llevado muy, muy lejos...";
		link.l1 = "¿Michel?... Por alguna razón no me sorprende. ¿Ha regresado Miguel Dichoso a Tayasal por otro montón de tesoros? Hm-hm-hm. Sí, he estado buscando una reunión contigo, querido hermano. Me moría de ganas por mirar en tus ojos descarados. Además, tu intento de asesinato en mí en la cripta del cementerio fue la guinda del pastel. Pero primero, dime, ¿cómo debo llamarte? ¿Michel de Monper o Miguel Dichoso?";
		link.l1.go = "kukulkan_1";
		break;

	case "kukulkan_1":
		dialog.text = "Estos nombres ya no tienen importancia, " + pchar.name + ". Todo está en el pasado, que muy pronto desaparecerá incluso de la misma historia. Ahora es el momento de la verdad, al que he estado acercándome poco a poco durante el largo cuarto de siglo desde que pisé tierra por primera vez...";
		link.l1 = "¿Qué?!! ¡Esto... esto no puede ser!!!";
		link.l1.go = "kukulkan_2";
		break;

	case "kukulkan_2":
		dialog.text = "Sí, " + pchar.name + ". Veo por tu cara que entiendes quién soy, pero no puedes creerlo. Soy aquel que has aspirado a conocer durante los últimos meses. Aquel con quien el representante de tu Dios, el Inquisidor de Santiago, te ha bendecido para la batalla.";
		link.l1 = "¿Kukulcán?!";
		link.l1.go = "kukulkan_change";
		break;

	case "kukulkan_change":
		DialogExit();
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Kanek");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;

	case "kukulkan_3":
		dialog.text = "Estoy de acuerdo, " + pchar.name + ", que es difícil de creer. La vida es más complicada y más sorprendente que cualquier cuento de hadas...";
		link.l1 = "Estaba listo para cualquier cosa, pero... ¡mi hermano!";
		link.l1.go = "kukulkan_4";
		break;

	case "kukulkan_4":
		dialog.text = "¿Hermano? Solo por la sangre de nuestro padre. Tenemos diferentes madres, " + pchar.name + ". Debes saber que mi madre era una hija de Kanek, llamada Shochikezhal. Fue secuestrada por corsarios franceses bajo el mando del famoso Nicolas Gotier después de que tontamente dejara Tayasal. Habían decidido esclavizarla. Un hombre llamado Serge Benoit estaba entre ellos.\nAvergonzado por la acción de su capitán, lo dejó, tomó el hábito y ahora lo conoces como el abad Benoit. Henri de Monper, nuestro padre, era oficial de la marina en ese entonces. Compró a Shochikezhal y la llevó a Francia donde me dio a luz. Alrededor del mismo tiempo tú naciste también, " + pchar.name + ". Tu madre murió al dar a luz y nuestro padre declaró que su esposa legítima había dado a luz a gemelos.\nShochikezhal, mi madre, se convirtió en nodriza para ambos. Fuiste alimentado con la leche de una mujer india del pueblo Itza, " + pchar.name + "¡Más tarde, tu abuela por parte de madre decidió acogerte para darte una educación y te dieron el nombre de tu madre, de Maure!";
		link.l1 = "¡¿Cómo descubriste todo eso?!";
		link.l1.go = "kukulkan_5";
		break;

	case "kukulkan_5":
		dialog.text = "¿No pensarías, hermano, que sé más que la gente común? Además, nuestro padre me ha contado mucho y estoy al tanto de muchas cosas... Es tal como dicen, al filo de mi asiento.";
		link.l1 = "Ahora todo está claro... ¿Y qué pasó con tu madre? ¿Por qué nunca la he visto?";
		link.l1.go = "kukulkan_6";
		break;

	case "kukulkan_6":
		dialog.text = "Murió salvando mi vida. Un poco más de un año después de mi nacimiento, casi muero debido a una enfermedad. Mi madre, la hija de un sacerdote Itza, realizó una ceremonia secreta de sanación mágica maya para mí. Me mejoré, pero esta ceremonia estuvo acompañada de algunos... efectos secundarios destructivos en forma de truenos, relámpagos y un huracán tropical. Shochikezhal fue denunciada y acusada de brujería y quemada en la hoguera de la Inquisición...";
		link.l1 = "Y mejoraste...";
		link.l1.go = "kukulkan_7";
		break;

	case "kukulkan_7":
		dialog.text = "Además de curarme, este ritual me otorgó otras habilidades también, además de abrir una conexión con el mundo de los dioses. Y ya conoces el resto. Como llevaré la luz del conocimiento y la experiencia de la raza blanca al pasado y la transmitiré al pueblo maya. La historia será reescrita y ustedes, los blancos, no dominarán este mundo. Me aseguraré de ello.";
		link.l1 = "¿Así que toda tu vida, estudiando en la mejor academia naval, sirviendo en el ejército y en la Orden de Malta, fue básicamente solo una acumulación de experiencia militar?";
		link.l1.go = "kukulkan_8";
		break;

	case "kukulkan_8":
		dialog.text = "Exactamente. Cuando me di cuenta de que sabía lo suficiente, arreglé que me mandaran al Caribe. Convencí al Caballero de Poincy para crear una base en Martinica. Después, tuve que abrirme camino hacia Tayasal. No fue una tarea sencilla para mí, ya que este cuerpo físico sigue siendo mortal y los portales en el Caribe no funcionaban correctamente.";
		link.l1 = "Y te convertiste en Miguel Dichoso...";
		link.l1.go = "kukulkan_9";
		break;

	case "kukulkan_9":
		dialog.text = "Querido hermano, conseguí este apodo en los campos de batalla de Europa. También conocí allí a Ramón de Mendoza y Riba. ¿Crees que la vida está hecha de casualidades? No, en absoluto, cada casualidad es una regularidad desconocida. Se hizo mucho por el bien de mi regreso a Tayasal. Tuve que vivir dos vidas. Michel de Monper y Miguel Dichoso. También tuve que asegurarme de que la gente creyera que eran personas diferentes.\nTuve que piratear, igual que tú, al servicio de de Poincy para ganarme su confianza, favor y dinero. Tuve que asesinar a Blaze Sharp, uno de los líderes de los piratas, como un favor para Ramón de Mendoza, para conseguir soldados para la expedición.\nTuve que tentar tanto a de Poincy como a de Mendoza con cuentos de los tesoros de Tayasal. Recibí setecientas cincuenta mil piezas de plata del tesoro de de Poincy y vendí la fragata militar española al pirata Dodson. Y entonces ocurrió la expedición. Regresé a Tayasal solo para sufrir un fracaso...";
		link.l1 = "Entiendo... Mientras tú eras solo un niño de cinco años persiguiendo mariposas en el patrimonio de nuestro padre, Kanek, el gran sacerdote, asustado por la invasión de Don Alonso de Maldonado en Tayasal, escondió de manera segura la máscara de Kukulcán, que es tan vital para viajar al pasado... discúlpame, quise decir TU máscara.";
		link.l1.go = "kukulkan_10";
		break;

	case "kukulkan_10":
		dialog.text = "Sí, Kanek se había engañado a sí mismo allí. Realizó el ritual más difícil, un ritual que ni siquiera los antiguos se atrevieron a realizar. Ocultó la máscara en la isla desierta recién creada y logró perder la llave de Ksocheatem, el llamado Guardián de la Verdad.\nTuve que actuar con astucia. El ritual impedía que cualquier barco que transportara objetos protegidos del tesoro de Taysal a bordo, saliera del Caribe arrojando tales embarcaciones a las costas de Ksocheatem. Tenía la intención de usar eso. Tomé suficientes tesoros para apaciguar a Mendoza. También tomé un objeto especial protegido por el ritual.\nUn barco con este objeto a bordo estaría condenado a ser entregado directamente a Ksocheatem, directamente a mi máscara. Así que me hice a la mar y le hice saber a Mendoza sobre mí.";
		link.l1 = "Entonces, ¿saliste de Tayasal por tu cuenta?";
		link.l1.go = "kukulkan_11";
		break;

	case "kukulkan_11":
		dialog.text = "¿Te refieres sin los soldados de Mendoza? Claro. Todos los españoles fueron masacrados aquí, en Tayasal. Los Itza llevaron los tesoros a la orilla ellos mismos y yo le dije a Mendoza que los soldados fueron emboscados por los miskitos. Me creyó ya que solo le interesaba el oro y no la gente.\nTenía planeado colocar el barco con los tesoros bajo los cañones del 'Gryffondor', pero todo salió mucho mejor: el barón decidió enviar los tesoros a España bajo mi supervisión. Fue el mejor resultado posible, solo tenía que esperar hasta que el barco cruzara la frontera invisible del Caribe.\nSin embargo, resultó que el capitán tenía órdenes diferentes. Descubrí que una unidad especial de abordaje se suponía que debía amotinarse tan pronto como llegáramos al océano Atlántico, matando a la tripulación y a todos los oficiales. El capitán tenía órdenes de devolver el oro indio a Mendoza después.\nUn buen espécimen de la raza blanca, ¿no es así, hermano? Tuve que arriesgarme, no sabía cuándo debía suceder el motín. Pero todo salió según el plan: la tormenta nos golpeó tan pronto como el 'Santa Quiteria' alcanzó el lado oriental de la isla de Trinidad y Tobago. La fragata fue arrastrada de regreso al Caribe hacia Ksocheatem.\nEntonces sufrí el mayor fracaso de mi vida: una ola me arrastró fuera del barco y me encontré en la cala Le Marin en Martinica un par de días después. Los pescadores me encontraron y me llevaron a Le Francois. Pero los hombres de de Poincy me capturaron mientras volvía a la vida en la casa de Cesar Craig. El 'Gryffondor' no encontró el 'Santa Quiteria' en el lugar que definí. El caballero de Poincy se enfureció en cuanto supo que el oro indio se había ido junto con el dinero tomado del tesoro de la Orden y sus propios ahorros.\nMe arrestó. Sin embargo, no podía matarme, no quería hacerlo. Quería oro. ¡Oro! ¡Eso es lo único que tu gente quiere y le importa! Harás cualquier cosa para conseguirlo... Estaba en una posición terrible: no tenía mi máscara y me dejaron pudriéndome en una celda sin una sola moneda en mis bolsillos.\nFue entonces cuando te convoqué. Sí, sí, querido hermano, se suponía que debías liberarme, para que pudiera hacer lo que nací para hacer. Y hiciste un trabajo extraordinario. Parece que la leche de Itza que mamaste te hizo algo de bien.";
		link.l1 = "Lo que me interesa saber es, ¿en qué contabas cuando escapaste de Saint-Pierre entonces? ¿Cuál era tu plan?";
		link.l1.go = "kukulkan_12";
		break;

	case "kukulkan_12":
		PlaySound("Voice\Spanish\sharlie\mishelle-05.wav");
		dialog.text = "Siempre fuiste mi plan, hermano. Kukulcán puede leer los corazones de las personas. La carta que te dejé en el monasterio debía hacer que actuaras. Tenía razón contigo. He estado observando tu progreso desde que tuviste el primer encuentro con el Inquisidor de Santiago. Hiciste todo por mí. Creaste al Guardián de la Verdad. Eliminaste a los competidores. Encontraste a Ksocheatem.\nEstuve allí, siguiéndote. Aunque no esperaba que entraras en Tayasal. Has superado todas mis expectativas. Y con tu ayuda, haré lo que nací para hacer. La razón por la que nací en carne mortal.";
		link.l1 = "Hay solo una pequeña salvedad en tu razonamiento, querido hermano. No posees tu máscara y no eres nada sin ella. Yo la tengo. Y no me muero de ganas de entregártela. Más bien la haría pedazos antes que dejarla caer en tus manos.";
		if (CheckCharacterItem(pchar, "mask_true"))
			link.l1.go = "kukulkan_13";
		else
			link.l1.go = "kukulkan_14";
		break;

	case "kukulkan_13":
		dialog.text = "No puedes cambiar lo que está predestinado por el destino. No permitiré que dañes mi artefacto. Puedo sentirlo... Está contigo. Y tú estás aquí, en mi templo, dentro de todo mi poder. ¡Nunca saldrás de este lugar! Es hora de tu prueba final, querido hermano, para ver cuánto vales en una batalla contra Kukulcán.";
		link.l1 = "¡Supongo que tu cuerpo mortal aún puede sangrar!";
		link.l1.go = "kukulkan_fight";
		break;

	case "kukulkan_14":
		dialog.text = "¡Ja! Me das pena, Charles. Esto es realmente triste. Pero mereces una oportunidad de luchar contra un Dios. Aunque sea inútil. Te lo diré más tarde, si sobrevives al primer acto.";
		link.l1 = "¡Supongo que tu cuerpo mortal aún puede sangrar!";
		link.l1.go = "kukulkan_fight";
		break;

	case "kukulkan_fight":
		DialogExit();
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "item", "button04");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocator(npchar, "quest", "defend1", "", -1);
		sld = characterFromId("Kanek");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "quest", "defend2", "", -1);
		DoQuestFunctionDelay("Tieyasal_TempleFightGuard", 3.0);
		break;

	case "kukulkan_twice": // развилка финалов - есть настоящая маска или нет
		if (CheckCharacterItem(pchar, "mask_true"))
		{
			dialog.text = "";
			link.l1 = "Parece que tus poderes te están abandonando, gran Kukulcán... Puedes ser fuerte, pero tu cuerpo sigue siendo mortal!";
			link.l1.go = "kukulkan_win";
		}
		else
		{
			dialog.text = "Creo que eso será suficiente entretenimiento. Eres verdaderamente un maestro espadachín y un gran luchador, me atrevería a decir que el mayor guerrero de tu tiempo, pero esta batalla la has perdido, " + pchar.name + "...";
			link.l1 = "Solo estamos...";
			link.l1.go = "kukulkan_fail";
		}
		break;

	case "kukulkan_fail":
		DialogExit();
		SetMusic("music_teleport");
		LAi_SetActorType(pchar);
		LAi_SetActorType(npchar);
		LAi_ActorAnimation(npchar, "attack_force_1", "Tieyasal_KukulkanKick", 1.0);
		LaunchBlast(npchar);
		PlaySound("Sea Battles\udar_metal_003.wav");
		break;

	case "kukulkan_fail_1":
		dialog.text = "Basta, querido hermano. ¡No puedes resistir el poder de Kukulcán cuando está junto a su artefacto! Te he permitido vivir tanto tiempo solo para ver lo que realmente has sido capaz de lograr.";
		link.l1 = "Maldición... Ese último golpe... ¿Pero de qué artefacto hablas? ¿La máscara? ¡Está conmigo!";
		link.l1.go = "kukulkan_fail_2";
		break;

	case "kukulkan_fail_2":
		dialog.text = "Pobre, pobre Capitán " + GetFullName(pchar) + "... Has llegado tan lejos, sobrevivido a todos los peligros, matado a muchos de los enemigos más fuertes sólo para ser derrotado al final!.. ¡La máscara de jade que encontraste dentro de la caja de metal cerca de los restos del 'Santa Quiteria' en Ksocheatem es una farsa! Es solo una máscara antigua del tesoro de Taysal. ¡NO ES LA MÁSCARA DE KUKULCÁN!.\nLa había tomado personalmente de aquí después de mi fallida expedición, está custodiada por el antiguo ritual. Esta máscara fue la razón por la que la tormenta llevó al Santa Quiteria a Ksocheatem. También tenía un segundo propósito. Se suponía que debía engañar a cualquiera que viniera allí por mi VERDADERO artefacto.";
		link.l1 = "Pero... ¿dónde estaba la máscara real entonces? ¡He buscado por todo Ksocheatem!..";
		link.l1.go = "kukulkan_fail_3";
		break;

	case "kukulkan_fail_3":
		dialog.text = "No lo has hecho, " + pchar.name + ". Mi artefacto estaba en el lado opuesto de la isla del 'Santa Quiteria', en un santuario bien vigilado. El camino hasta allí pasa por cavernas subterráneas. Es complicado de encontrar y no evidente para el ojo poco experto de un mortal. ¡Ahí está! Míralo bien, una última mirada...";
		link.l1 = "¡No puede ser!";
		link.l1.go = "kukulkan_fail_4";
		break;

	case "kukulkan_fail_4":
		dialog.text = "Sobreviviste y ganaste muchas batallas, hermano. Pero has perdido esta, " + pchar.name + "...";
		link.l1 = "¿Y qué ahora?";
		link.l1.go = "kukulkan_fail_5";
		break;

	case "kukulkan_fail_5":
		dialog.text = "Viajaré directamente al siglo décimo, siete siglos atrás. Esto será suficiente para que la civilización Maya alcance un poderío militar y científico inquebrantable sobre la raza blanca.";
		link.l1 = "¿Y qué sucederá con nuestro mundo? ¿Desaparecerá?";
		link.l1.go = "kukulkan_fail_6";
		break;

	case "kukulkan_fail_6":
		dialog.text = "No. Cambiará. Tal vez haya un lugar para ti, pero no recordarás nada de lo que sucedió en este mundo. Algunos de los que nacieron aquí nunca nacerán allí, lo contrario también es cierto. Los muertos volverán a la vida y los vivos morirán, de una forma u otra, todos renacerán. Suum cuique, a cada uno lo suyo, " + pchar.name + ".\nNo tengas miedo, hermanito. Nunca te darás cuenta de lo que ha ocurrido y aceptarás naturalmente la nueva realidad. Solo yo, Kukulcán, conservaré los recuerdos... ¡Pero basta! Kanek ya ha preparado todo para el ritual.\nMe seguirás, " + GetFullName(pchar) + ", y serás testigo de los últimos momentos de la existencia de esta realidad que estabas tan ansioso por preservar.";
		link.l1 = "...";
		link.l1.go = "kukulkan_fail_7";
		break;

	case "kukulkan_fail_7":
		DialogExit();
		LAi_SetActorType(pchar);
		DoQuestCheckDelay("Tieyasal_Fail_ReloadTown", 2.0);
		break;

	case "kukulkan_fail_8":
		dialog.text = "¡Las puertas del tiempo se han abierto! ¡Regocijaos, mis hijos, pues estáis tan cerca de la grandeza! ¡Crearemos el nuevo mundo, un mundo sin lugar para los invasores pálidos!\nAdiós, " + pchar.name + ", y prepárate para aceptar tu nuevo destino, sea cual sea. ¡Suum cuique!";
		link.l1 = "...";
		link.l1.go = "kukulkan_fail_9";
		break;

	case "kukulkan_fail_9":
		DialogExit();
		LAi_SetActorType(pchar);
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocator(npchar, "goto", "kukulkan", "", -1);
		DoQuestCheckDelay("Tieyasal_Fail_TeleportStart", 4.0);
		break;

	case "kukulkan_win":
		dialog.text = "Esta batalla aún no ha terminado, mortal. Estás considerablemente agotado y tengo refuerzos en camino. Entregarás mi artefacto. O eso, o lo tomaré de tu cadáver, para mí no hay diferencia...";
		link.l1 = "... ";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Tieyasal_PrepareToWinBattle");
		break;

	case "kukulkan_win_1":
		dialog.text = "¡Urakan! ¡Te ordeno que mates a este hombre inmediatamente!";
		link.l1 = "...";
		link.l1.go = "kukulkan_win_2";
		break;

	case "kukulkan_win_2":
		dialog.text = "¡Urakan! ¿No me has oído? Repito: ¡te ordeno a ti y a tus guerreros que capturen y maten a este hombre!";
		link.l1 = "...";
		link.l1.go = "kukulkan_win_3";
		break;

	case "kukulkan_win_3":
		dialog.text = "¡Urakan! ¿Qué diablos? ¡Kanek! ¡Repite mi orden a tu maldito hijo!!!";
		link.l1 = "... ";
		link.l1.go = "kukulkan_win_4";
		break;

	case "kukulkan_win_4":
		DialogExit();
		sld = characterFromId("Kanek");
		sld.dialog.currentnode = "kanek_2";
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

	case "kukulkan_win_5":
		dialog.text = "¡Traicionas a tu gente, Urakan! ¡Has temblado ante tales transformaciones eminentes! ¡Guerreros, os ordeno capturar y dar muerte no solo a este hombre que se hace llamar mi hermano, sino también a Urakan, el traidor!";
		link.l1 = "¡Guerreros, en nombre de Cavil y Huracán os ordeno que os quedéis como estáis, si valoráis vuestra vida! ¡Ninguno de vosotros sobrevivirá a una pelea contra Cavil! ¡Dejad que los dioses decidan por sí mismos quién de ellos es el más fuerte en la Tierra!";
		link.l1.go = "kukulkan_win_6";
		break;

	case "kukulkan_win_6":
		DialogExit();
		LAi_SetActorType(PChar);
		LAi_ActorTurnToCharacter(PChar, characterFromID("Mishelle"));
		SetMainCharacterIndex(GetCharacterIndex("Blaze"));
		PChar = GetMainCharacter();
		LAi_SetPlayerType(PChar);
		sld = characterFromId("Mishelle");
		sld.dialog.currentnode = "kukulkan_win_7";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.8);
		break;

	case "kukulkan_win_7":
		dialog.text = "";
		link.l1 = "Este día mejora cada vez más. No esperabas tal curso de acciones, ¿verdad, hermano? Los dioses deben decidir por sí mismos quién de ellos es realmente el más fuerte. Y todos recibirán lo que merecen, Michel. ¡Suum cuique! A cada uno lo suyo...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Tieyasal_WinBattleStart");
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
