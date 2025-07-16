void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	bool ok;
	int iTest;
	ref rColony;
	string sFrom_sea = "";

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "Eso es definitivamente un error. ¿Puedes informar a Jason sobre cuándo y cómo sucedió eso?";
		link.l1 = "Hágase.";
		link.l1.go = "exit";
		break;

	// шаман карибов Туттуатхапак
	case "Tuttuat":
		dialog.text = "¿Por qué has venido a mi choza, hombre blanco? Tuttuathapak no cree que seas su querido invitado.";
		if (GetCharacterFreeItem(pchar, "mushket1") || GetCharacterFreeItem(pchar, "mushket2") || GetCharacterFreeItem(pchar, "mushket7"))
		{
			link.l1 = "Salve a ti, gran chamán Tuttuathapak. He venido a ti en busca de tu ayuda y consejo. Por favor, acepta este mosquete como muestra de mi buena voluntad.";
			link.l1.go = "Tuttuat_1";
		}
		else
		{
			link.l1 = "Salve a ti, gran chamán Tuttuathapak. He venido a ti para buscar tu ayuda y consejo.";
			link.l1.go = "Tuttuat_exit";
		}
		break;

	case "Tuttuat_exit":
		dialog.text = "Tuttuathapak no ayuda al hombre blanco. Los hombres blancos son malos. Ellos matan y conquistan a los indios, hacen esclavos a los indios. Tuttuathapak no da consejos al hombre blanco. Vete ahora.";
		link.l1 = "Hmm...";
		link.l1.go = "Tuttuat_exit_1";
		break;

	case "Tuttuat_exit_1":
		DialogExit();
		npchar.dialog.currentnode = "Tuttuat";
		break;

	case "Tuttuat_1":
		if (GetCharacterFreeItem(pchar, "mushket1"))
		{
			sTemp = "mushket1";
		}
		else
		{
			if (GetCharacterFreeItem(pchar, "mushket2"))
			{
				sTemp = "mushket2";
			}
			else
			{
				sTemp = "mushket7";
			}
		}
		RemoveItems(pchar, sTemp, 1);
		PlaySound("interface\important_item.wav");
		Log_Info("Has entregado: " + XI_ConvertString(sTemp) + "");
		dialog.text = "Tú sabes qué darle a Tuttuathapak, hombre blanco. Tuttuathapak acepta tu regalo. Él hablará. ¿Qué consejo buscas de mí?";
		link.l1 = "Escuché que vienes de un lugar lejano en el sur. Tengo un amuleto indio, y un hombre sabio me dijo que podrías saber cómo se puede usar.";
		link.l1.go = "Tuttuat_2";
		DelLandQuestMark(npchar);
		DelMapQuestMarkIsland("Dominica");
		break;

	case "Tuttuat_2":
		dialog.text = "Muestra el amuleto.";
		link.l1 = "Aquí tienes, gran chamán.";
		link.l1.go = "Tuttuat_3";
		break;

	case "Tuttuat_3":
		PlaySound("interface\important_item.wav");
		dialog.text = "(mirando el amuleto)... Tu amigo dice la verdad, hombre blanco. Este amuleto pertenece a mi gente, grandes indios, Chavin era su nombre. Maldito blasfemo rostro pálido profanó el santuario y lo llevó aquí. Tuttuathapak castigó a ese perro.";
		link.l1 = "¿Le privaste de su juicio, supongo?";
		link.l1.go = "Tuttuat_4";
		break;

	case "Tuttuat_4":
		dialog.text = "El hombre blanco sorprende a Tuttuathapak con su conocimiento. Sí, devoro la mente de ese perro sarnoso. Él y su sucio hombre reciben lo que merecen.";
		link.l1 = "Ya veo... Dime, chamán, ¿para qué se usa este amuleto? ¿Quizás pueda proteger a uno en la batalla o ahuyentar la magia maligna?";
		link.l1.go = "Tuttuat_5";
		break;

	case "Tuttuat_5":
		dialog.text = "Este amuleto no te sirve de nada, capitán blanco. No puedes usar su poder. Solo los grandes chamanes de nuestra tribu saben cómo despertarlo.";
		link.l1 = "Hmm... Entonces, resulta que hice un viaje tan largo en vano. Pero, quizás, ¿puedes despertar el poder de este amuleto, gran chamán? Ciertamente podríamos llegar a un acuerdo...";
		link.l1.go = "Tuttuat_6";
		break;

	case "Tuttuat_6":
		dialog.text = "Aun si despierto el amuleto, no podrás mantener su poder por mucho tiempo. Pero te ofrezco un trato, hombre blanco.";
		link.l1 = "¿Qué clase de trato?";
		link.l1.go = "Tuttuat_7";
		break;

	case "Tuttuat_7":
		dialog.text = "Tres amuletos como este fueron tomados de nuestro santuario. Tienen diferentes poderes, pero si se juntan, serán muy, muy poderosos. Encuentra los tres amuletos y tráemelos, y te recompensaré. Te daré un poder que podrás conservar para siempre.";
		link.l1 = "No entiendo del todo... ¿De qué tipo de poder estás hablando?";
		link.l1.go = "Tuttuat_8";
		break;

	case "Tuttuat_8":
		dialog.text = "Lo sabrás todo a su debido tiempo. Encuentra y tráeme los tres amuletos. Están en el Caribe. Busca y encuentra. Los reconocerás fácilmente - se parecen entre sí. Ve, hombre blanco. Tuttuathapak espera y pide a los espíritus que te ayuden.";
		link.l1 = "...";
		link.l1.go = "Tuttuat_9";
		break;

	case "Tuttuat_9":
		DialogExit();
		npchar.dialog.currentnode = "Tuttuat_10";
		pchar.questTemp.Caleuche = "ghostship";
		AddQuestRecord("Caleuche", "3");
		pchar.quest.Caleuche_ghostship.win_condition.l1 = "location";
		pchar.quest.Caleuche_ghostship.win_condition.l1.location = "Dominica";
		pchar.quest.Caleuche_ghostship.function = "Caleuche_PrepareGhostship";
		break;

	case "Tuttuat_10":
		if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
		{
			dialog.text = "Vete, hombre blanco. Encuentra dos amuletos más.";
			link.l1 = "Ya los he encontrado, gran chamán. Aquí, echa un vistazo.";
			link.l1.go = "Tuttuat_33";
		}
		else
		{
			dialog.text = "Ve, hombre blanco. Encuentra los otros dos amuletos.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_10_1";
		}
		break;

	case "Tuttuat_10_1":
		DialogExit();
		npchar.dialog.currentnode = "Tuttuat_10";
		break;

	case "Tuttuat_11":
		dialog.text = "¿Tú aquí otra vez, hombre blanco? Pareces como si hubieras encontrado un feroz jaguar en la jungla.";
		link.l1 = "Peor, gran chamán. Al adentrarme en el mar, una tormenta masiva apareció de la nada y fui atacado por un barco tripulado por los no-muertos. ¡Su capitán era totalmente invencible! Primero me quitó el amuleto y casi me mata - apenas sobreviví. Y luego casi hundieron mi barco, solo un puñado de mi tripulación sobrevivió.";
		link.l1.go = "Tuttuat_12";
		DelLandQuestMark(npchar);
		break;

	case "Tuttuat_12":
		dialog.text = "Malas noticias, hombre blanco. El Caleuche va a matar de nuevo.";
		link.l1 = "¿El Caleuche? Ese capitán no muerto llamó a su barco el Corazón Volador. Entonces, ¿sabías del barco fantasma y no me lo advertiste? Si hubiera sabido que esta pesadilla marina estaba buscando el amuleto, nunca...";
		link.l1.go = "Tuttuat_13";
		break;

	case "Tuttuat_13":
		dialog.text = "Tuttuathapak ve que el capitán blanco está molesto. El capitán blanco debe calmarse.";
		link.l1 = "¿Calmarme?! ¡¿Estás loco, cómo puedo siquiera sobrevivir contra tal cosa?!";
		link.l1.go = "Tuttuat_14";
		break;

	case "Tuttuat_14":
		dialog.text = "Sí. Cálmate y no grites. Dime, ¿todavía quieres recibir un gran poder de mí, que permanezca contigo para siempre?";
		link.l1 = "Pues, claro que sí. Pero ya no tengo el amuleto.";
		link.l1.go = "Tuttuat_15";
		break;

	case "Tuttuat_15":
		dialog.text = "Os enseño a cómo tomar el amuleto del capitán del Caleuche. No es fácil. Pero si lo hacéis, tomaréis su barco como vuestro premio, encontraréis un tesoro valioso, ganaréis gloria con vuestro pueblo y recibiréis una recompensa de mí.";
		link.l1 = "¡Maldita sea! ¡Con gusto destruiría a ese monstruo marchito! ¿Pero cómo puedo derrotarlo si no puede ser dañado ni por la espada, ni por la bala?!";
		link.l1.go = "Tuttuat_16";
		break;

	case "Tuttuat_16":
		dialog.text = "¿Estás listo para escucharme, capitán blanco?";
		link.l1 = "Sí, lo estoy, gran chamán.";
		link.l1.go = "Tuttuat_17";
		break;

	case "Tuttuat_17":
		dialog.text = "Cuando mi padre era un joven guerrero, los hombres blancos vinieron a mi tierra en el barco el Corazón Volador. Fueron a las montañas. La leyenda dice que allí está escondido un santuario de nuestros antepasados. Santuario de guerreros jaguar. Los hombres blancos encontraron el santuario y el oro y profanaron algo sagrado y antiguo. Se llevaron el gran tesoro de los Chavines: la calavera de jade de Yum Cimil, dios de la muerte y patrón de los hombres jaguar\nLos hombres blancos regresaron a su barco. Decidieron volver para tomar más oro, pero cuando uno de sus hombres pisó tierra firme, murió con un dolor horrible. Yum Cimil maldijo al capitán y su tripulación. Se volvieron inmortales, pero ya no pueden pisar tierra. Navegaron muchos-muchos inviernos, medio siglo según tu calendario. Así es como surgió el Caleuche.\nSus cuerpos se marchitan, su carne se pudre, pero aún viven. Si cortas un brazo o una pierna, vuelve a crecer. Si los partes en dos, vuelven a ser uno. Si su barco se hunde, lo reparan bajo el agua y vuelve a navegar.";
		link.l1 = "Simplemente genial...";
		link.l1.go = "Tuttuat_18";
		break;

	case "Tuttuat_18":
		dialog.text = "El Caleuche aterroriza a los marineros. Ataca sin razón y anuncia una perdición segura. No es un invitado frecuente en el Caribe. Le gusta navegar por las costas de mi tierra natal. Me parece que quiere quitar la maldición. Pero nunca la levantará.";
		link.l1 = "¿Por qué? ¿Qué se necesita hacer para levantar la maldición?";
		link.l1.go = "Tuttuat_19";
		break;

	case "Tuttuat_19":
		dialog.text = "Calavera de jade. Debe regresar al santuario de Yum Cimil, templo de los guerreros jaguar. Hay varios templos. Los ancianos de mi tribu dicen que hay uno en una pequeña isla del Caribe. Por eso el Caleuche navegó hasta allí. Una vez que la calavera esté en el templo, el hechizo de Yum Cimil se rompe, y se vuelven mortales y ya no sanan sus heridas.";
		link.l1 = "¡Ja! Más bien, ¡no van a devolver la calavera! ¿Por qué lo harían, si son inmortales e invencibles? Y además, simplemente no pueden traerla de vuelta, si no se les permite pisar tierra, ¿verdad?";
		link.l1.go = "Tuttuat_20";
		break;

	case "Tuttuat_20":
		dialog.text = "No tienen calavera. El capitán la arrojó en la tierra de mis antepasados, cuando regresó del santuario de los hombres jaguar. El jade no es oro, el hombre blanco no lo necesita, no pudo tomar la hermosa gema verde en los ojos de la calavera. Y la arrojó. Un marinero la recogió, y no fue tocado por la maldición. Cuando el marinero vio en qué se había convertido la tripulación del Caleuche, huyó. Vino a nuestro pueblo. Mi padre vio a ese marinero y la calavera de Yum Cimil. Y luego el hombre blanco fue al norte a lo largo de la costa y se llevó la calavera con él.";
		if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
		{
			if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul"))
			{
				link.l1 = "¿Un cráneo de jade con piedras verdes en las cuencas de los ojos? Lo tuve en mis manos, ¿puedes imaginarlo? Se lo di a Solomon yo mismo. Pero se fue a Europa con su hija, y parece que se llevó el cráneo con él.";
			}
			else
			{
				link.l1 = "¿Un cráneo de jade con gemas verdes en las cuencas de los ojos? Joder... Yo... ¡Lo he tenido en mis propias manos! Y se lo he vendido a unos portugueses... Merriman, o algo así... Sí, eso es lo que dijo, ¡el cráneo de Yum Cimil! ¡Lo quería con desesperación! ¡Pagó medio millón de pesos por él!";
			}
			link.l1.go = "Tuttuat_21_1";
		}
		else
		{
			link.l1 = "¿Un cráneo de jade con gemas verdes en las cuencas de los ojos? ¿Entonces eso es lo que necesitaré encontrar? ¡Pero ese marinero podría haber perecido en la selva hace cincuenta años, y el cráneo podría estar perdido para siempre!";
			link.l1.go = "Tuttuat_21_2";
		}
		break;

	case "Tuttuat_21_1":
		dialog.text = "Yo sé que la calavera está en el Caribe. El Caleuche está aquí no por casualidad. En las últimas seis lunas se le ha visto a menudo en la isla. En tiempos pasados no estaba allí por muchos inviernos. El capitán del Caleuche puede sentir el artefacto de los hombres jaguar. Así es como te encuentra a ti y a tu barco.";
		link.l1 = "Entonces, ¿entiendo correctamente que tengo que encontrar este cráneo otra vez? ¿Y luego qué debo hacer con él?";
		link.l1.go = "Tuttuat_22";
		break;

	case "Tuttuat_21_2":
		dialog.text = "El cráneo debe estar aquí, en el Caribe. Caleuche no está aquí por casualidad. Durante las últimas seis lunas, se le ha visto a menudo en la isla. Antes no estaba allí por muchos inviernos. El capitán del Caleuche puede sentir el artefacto de los hombres jaguar. Así es como te encontró a ti y a tu barco.";
		link.l1 = "Entonces, ¿entiendo correctamente que tengo que encontrar este cráneo de nuevo? ¿Y luego qué debo hacer con él?";
		link.l1.go = "Tuttuat_22";
		break;

	case "Tuttuat_22":
		dialog.text = "Primero, debes encontrar dos amuletos de los que hablamos. Sin ellos no puedes hacer nada. El amuleto te da poder para enfrentarte a los hombres jaguar y cualquier enemigo con el que te encuentres.";
		link.l1 = "¿Enfrentarse a los hombres jaguar? ¿De qué estás hablando?";
		link.l1.go = "Tuttuat_23";
		break;

	case "Tuttuat_23":
		dialog.text = "El templo donde debes llevar la calavera de jade está en una isla desierta del Caribe. Está custodiado por hombres jaguar. Todos están muertos pero ahora vivos. Sin el amuleto no podrás pasarlos. Los hombres jaguar en vida eran guerreros feroces, y tras la muerte se vuelven casi invencibles. La fuerza les es dada por el mismo Yum Cimil.";
		link.l1 = "¿No muertos? ¿Otra vez? Qué suerte la mía...";
		link.l1.go = "Tuttuat_24";
		break;

	case "Tuttuat_24":
		dialog.text = "¿Por qué tan sorprendido, capitán blanco? Yum Cimil es un dios de la muerte, el cráneo de jade da poder sobre los muertos y los vivos. Caribe. Está custodiado por hombres jaguar. Sin amuleto no pasarás por ellos. Con el amuleto puedes entrar al templo y sobrevivir, dejas el cráneo allí, luego encuentras el Caleuche, derrotas a su capitán y tomas el amuleto que te quitó.";
		link.l1 = "¿Y por qué necesita el capitán del Caleuche estos amuletos?";
		link.l1.go = "Tuttuat_25";
		break;

	case "Tuttuat_25":
		dialog.text = "Me parece que quiere ir al templo de los hombres jaguar y piensa que el amuleto le ayudará. Pero puedo estar equivocado. Aún así, el Caleuche siempre es atraído por los artefactos de mi tierra. Navegó cerca de la isla donde está el templo de los hombres jaguar, y navegó por las costas de mi tierra natal.";
		link.l1 = "¿Y dónde está esa isla?";
		link.l1.go = "Tuttuat_26";
		break;

	case "Tuttuat_26":
		dialog.text = "Primero encuentras la calavera de Yum Cimil y los amuletos. Luego hablamos sobre la isla.";
		link.l1 = "Está bien. ¿Puedes darme una pista de dónde buscar la calavera de jade?";
		link.l1.go = "Tuttuat_27";
		break;

	case "Tuttuat_27":
		dialog.text = "No lo sé. Pero está aquí, en el Caribe. Y amuletos, también. Pregunta. Busca. Encuentra.";
		link.l1 = "Heh... Está bien, lo intentaré.";
		link.l1.go = "Tuttuat_28";
		break;

	case "Tuttuat_28":
		dialog.text = "Y ten cuidado, capitán blanco. El Caleuche siente los objetos Chavins. Cuando tengas el amuleto, ella te buscará. Si te encuentra, huye y rápido. Si te atrapa, eres un hombre muerto.";
		link.l1 = "¡Este maldito barco es endiabladamente rápido! Es aproximadamente el doble de rápido que cualquier barco que haya visto. Pero noté que tiene dificultades al navegar contra el viento.";
		link.l1.go = "Tuttuat_29";
		break;

	case "Tuttuat_29":
		dialog.text = "El Caleuche está maldito, por eso es tan rápido. Difícil de escapar. Debes tener un barco que pueda superar al Caleuche. O acabarás muerto. Cuando encuentres el amuleto, tráelo a mí. No mantengas el amuleto en el barco.";
		link.l1 = "Ya lo tengo. Gracias por tu historia, gran chamán. Es hora de que me vaya ahora.";
		link.l1.go = "Tuttuat_31";
		break;

	case "Tuttuat_31":
		dialog.text = "Estaré pidiendo a los espíritus que te ayuden y te salven del Caleuche.";
		link.l1 = "...";
		link.l1.go = "Tuttuat_32";
		break;

	case "Tuttuat_32":
		DialogExit();
		LocatorReloadEnterDisable("Shore27", "boat", false);
		npchar.dialog.currentnode = "Tuttuat_10";
		pchar.questTemp.Caleuche = "mayak";
		AddQuestRecord("Caleuche", "6");
		break;

	case "Tuttuat_33":
		if (CheckCharacterItem(pchar, "kaleuche_amulet2"))
			RemoveItems(pchar, "kaleuche_amulet2", 1);
		else
			RemoveItems(pchar, "kaleuche_amulet3", 1);
		Log_Info("Has entregado el amuleto");
		PlaySound("interface\important_item.wav");
		dialog.text = "(mirando) Sí, es el indicado. El segundo amuleto de Chavins. Eres bueno. Necesitas encontrar aún otro amuleto.";
		link.l1 = "Lo recuerdo, chamán. Pronto lo tendrás.";
		link.l1.go = "Tuttuat_34";
		DelLandQuestMark(npchar);
		DelMapQuestMarkIsland("Dominica");
		break;

	case "Tuttuat_34":
		DialogExit();
		npchar.dialog.currentnode = "Tuttuat_35";
		AddQuestRecord("Caleuche", "22");
		if (!Caleuche_CheckAmulet())
		{
			if (GetCharacterIndex("Map_Caleuche") != -1)
			{
				sld = characterFromId("Map_Caleuche");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter("Map_Caleuche");
			}
		}
		break;

	case "Tuttuat_35":
		if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
		{
			dialog.text = "Ve, hombre blanco. Encuentra un amuleto más.";
			link.l1 = "Ya lo tengo, gran chamán. Aquí, echa un vistazo.";
			link.l1.go = "Tuttuat_36";
		}
		else
		{
			dialog.text = "Ve, hombre blanco. Encuentra un amuleto más.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_35_1";
		}
		break;

	case "Tuttuat_35_1":
		DialogExit();
		npchar.dialog.currentnode = "Tuttuat_35";
		break;

	case "Tuttuat_36":
		if (CheckCharacterItem(pchar, "kaleuche_amulet2"))
			RemoveItems(pchar, "kaleuche_amulet2", 1);
		else
			RemoveItems(pchar, "kaleuche_amulet3", 1);
		Log_Info("Has entregado el amuleto");
		PlaySound("interface\important_item.wav");
		dialog.text = "(mirando) Sí, es el indicado. Tercer amuleto de Chavins. Eres bueno. Encontraste todos los amuletos para pasar a los guerreros jaguar muertos, siervos de Yum Cimil.";
		link.l1 = "Ahora, según entiendo, ¿necesitaré la calavera de jade?";
		link.l1.go = "Tuttuat_37";
		DelLandQuestMark(npchar);
		DelMapQuestMarkIsland("Dominica");
		break;

	case "Tuttuat_37":
		dialog.text = "Habláis verdad. Cráneo de jade de Yum Cimil. Debéis llevarlo al templo de Chavín. Entonces el Caleuche perderá su poder para siempre.";
		link.l1 = "Tuttuathapak, por favor, dime, ¿dónde buscar? ¿Alguna idea?";
		link.l1.go = "Tuttuat_38";
		break;

	case "Tuttuat_38":
		if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
		{
			dialog.text = "No. Piensa dónde viste por última vez la calavera de jade. A quién se la diste. Empieza a buscar allí.";
			link.l1 = "Está bien, gran chamán. Haré todo lo que pueda.";
			link.l1.go = "Tuttuat_39";
		}
		else
		{
			dialog.text = "Un hechicero blanco interesado en el cráneo de Yum Cimil. Él lo busca. Incluso vino a nuestra aldea. Escuché que el hechicero vive en una casa en la isla holandesa. Busca al hechicero en la isla holandesa, y quizás sepas algo.";
			link.l1 = "Está bien, gran chamán. Haré todo lo que pueda.";
			link.l1.go = "Tuttuat_39";
		}
		break;

	case "Tuttuat_39":
		DialogExit();
		npchar.dialog.currentnode = "Tuttuat_40";
		AddQuestRecord("Caleuche", "23");
		if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
		{
			if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul"))
				sTemp = "Empezaré por Curaçao, donde se lo entregué a Salomón. Tal vez encuentre alguna pista y averiguar qué pasó con el cráneo.";
			else
				sTemp = "Empezaré visitando Curaçao: allí vendí la calavera de jade a Joachim Merriman.";
		}
		else
			sTemp = "Tuttuathapak me contó que un 'brujo blanco' se interesó por la calavera de jade y aconsejó buscarla en las islas holandesas. ¿Quién podría ser?";
		AddQuestUserData("Caleuche", "sText", sTemp);
		if (GetCharacterIndex("Map_Caleuche") != -1)
		{
			sld = characterFromId("Map_Caleuche");
			sld.lifeday = 0;
			Map_ReleaseQuestEncounter("Map_Caleuche");
		}
		pchar.questTemp.Caleuche = "skul";
		pchar.quest.Caleuche_villemstad.win_condition.l1 = "location";
		pchar.quest.Caleuche_villemstad.win_condition.l1.location = "Villemstad_town";
		pchar.quest.Caleuche_villemstad.function = "Caleuche_CreateMonk";
		AddMapQuestMarkCity("Villemstad", false);
		break;

	case "Tuttuat_40":
		dialog.text = "Ve, hombre blanco. Encuentra la calavera de jade de Yum Cimil.";
		if (pchar.questTemp.Caleuche == "island")
		{
			link.l1 = "Tengo   esto aquí, gran chamán, echa un vistazo.";
			link.l1.go = "Tuttuat_45";
		}
		else
		{
			link.l1 = "...";
			link.l1.go = "Tuttuat_40_1";
		}
		break;

	case "Tuttuat_40_1":
		DialogExit();
		npchar.dialog.currentnode = "Tuttuat_40";
		break;

	case "Tuttuat_41":
		dialog.text = "Ve, hombre blanco. Encuentra el cráneo de jade de Yum Cimil.";
		link.l1 = "Me temo que no podré hacerlo. He encontrado al brujo, pero en el último momento se escapó con la calavera. No tengo ni la más remota idea de dónde puede estar ahora.";
		link.l1.go = "Tuttuat_42";
		break;

	case "Tuttuat_42":
		dialog.text = "Esto es muy malo, hombre blanco. Ahora no pasarás el templo y no derrotarás al Caleuche. No te doy ningún regalo. Ahora te marchas.";
		link.l1 = "...";
		link.l1.go = "Tuttuat_43";
		break;

	case "Tuttuat_43":
		DialogExit();
		npchar.dialog.currentnode = "Tuttuat_44";
		break;

	case "Tuttuat_44":
		dialog.text = "Te vas ahora, hombre blanco.";
		link.l1 = "...";
		link.l1.go = "Tuttuat_44_1";
		break;

	case "Tuttuat_44_1":
		DialogExit();
		npchar.dialog.currentnode = "Tuttuat_40";
		break;

	case "Tuttuat_45":
		dialog.text = "(mirando) Sí, es el mismo. Muy hermoso. Y muy aterrador.";
		link.l1 = "Claro... Pero lo que es más interesante - crucé todo el mar Caribe desde Cuba hasta Dominica, y el Caleuche nunca intentó atacarme, cuando tenía este cráneo, ni siquiera lo vi. Y cuando te llevaba amuletos, constantemente me perseguía tan pronto como zarpaba, me encontraba en pocas horas.";
		link.l1.go = "Tuttuat_46a";
		break;

	case "Tuttuat_46a":
		dialog.text = "Me parece que el Caleuche teme al cráneo o no puede percibirlo. No tengo otra explicación. Quizás Yum Cimil hace que el cráneo de jade sea muy peligroso para el Caleuche, además de la maldición. Quizás por eso el capitán deseaba tanto llevarse tres amuletos de mi gente. Para obtener sabiduría sobre cómo controlar el hechizo de Yum Cimil.";
		link.l1 = "Entonces, mientras tenga la calavera de jade a bordo de mi barco, ¿no tengo que temer los ataques del Caleuche?";
		link.l1.go = "Tuttuat_46b";
		break;

	case "Tuttuat_46b":
		dialog.text = "Exactamente, cara pálida. Lo ves por ti mismo.";
		link.l1 = "¡Muy bien! Entonces, puedo tomar el mando de un gran barco, contratar a una tripulación decente y preparar una bienvenida agradable para ese muerto viviente, cuando se le levante el hechizo, sin miedo a que me intercepte antes...";
		link.l1.go = "Tuttuat_46c";
		break;

	case "Tuttuat_46c":
		dialog.text = "";
		link.l1 = "...acerca de ese hechizo, por cierto, ¿a dónde debo llevar la calavera de jade?";
		link.l1.go = "Tuttuat_46";
		break;

	case "Tuttuat_46":
		dialog.text = "Debes llevarlo al templo de Chavins y terminar tu viaje. Quiero contarte una historia. ¿Estás listo para escuchar, hombre blanco?";
		link.l1 = "Mis oídos están siempre abiertos para tu sabiduría, Tuttuathapak.";
		link.l1.go = "Tuttuat_47";
		break;

	case "Tuttuat_47":
		dialog.text = "Como dicen las leyendas de mis ancestros, hace mucho tiempo, cuando los hombres de rostro pálido aún no habían llegado a nuestra tierra, el gran jefe de los Chavines construyó una canoa muy, muy grande y la envió con un grupo de guerreros a la tierra de muchas islas. El hijo del gran jefe los lideró, y también iba uno de los altos chamanes. En la tierra de muchas islas encontraron una tierra desierta y fundaron un asentamiento y construyeron un gran templo para Yum Cimil, que solo nuestros grandes ancestros pudieron construir\nLos mensajeros regresaron con buenas noticias, pero nadie volvió a ver ni al hijo del jefe, ni al chamán ni a los guerreros. La leyenda dice que se quedaron allí a vivir, pero los más sabios de los chamanes hablaron con los espíritus y dijeron que ya no vivía gente allí, y que Yum Cimil gobernaba esa tierra\nLa tierra de muchas islas es el Caribe, hombre blanco. El templo de Yum Cimil está en una isla donde no viven ni hombres blancos ni indios. Solo los sirvientes de Yum Cimil, los Chavinavi, aún custodian los corredores del templo.";
		link.l1 = "¿Y dónde está esa isla?";
		link.l1.go = "Tuttuat_48";
		break;

	case "Tuttuat_48":
		dialog.text = "Supongo que es pequeño y al norte del pueblo en alguna parte de esa gran agua que llamáis océano, no está lejos.";
		link.l1 = "Mm... ¿Al norte de Dominica en la frontera oceánica, tal vez? ¡Maldita sea, es un área muy grande en el mar! ¿Cómo se supone que voy a encontrar una pequeña isla allí, si nadie ha oído hablar de ella?";
		link.l1.go = "Tuttuat_49";
		break;

	case "Tuttuat_49":
		dialog.text = "No puedo contar mejor. Pero conozco otra historia. Podrías escucharla de tus hermanos. Hace unos veinte inviernos, un hombre blanco encontró esa isla. Con una mujer y un anciano, entró en el templo de Yum Cimil y se llevó un poderoso artefacto: el orbe del sol naciente. En las costas de la isla, el capitán de rostro pálido fue atacado por el Caleuche. El de rostro pálido fue astuto. Cegó al capitán y a la tripulación del Caleuche con el sol naciente. La maldición del Caleuche se debilitó, y el capitán lo hundió, pero el orbe del sol naciente se disolvió. Si encuentras a ese hombre de rostro pálido, él te dirá dónde está la isla.";
		if (CheckAttribute(pchar, "questTemp.NatanStory"))
			link.l1 = "¡Ja! Creo que conozco a ese 'hombre pálido'... Las historias suenan demasiado similares. Entonces, ¿el Caleuche fue hundido?";
		else
			link.l1 = "Mm... Entonces, ¿el Caleuche fue hundido?";
		link.l1.go = "Tuttuat_50";
		break;

	case "Tuttuat_50":
		dialog.text = "Sí, pero la maldición los protege de la muerte. Lo arreglaron y continuaron su viaje eterno.";
		link.l1 = "Está bien, entendido. Pero, ¿qué debo hacer en el templo? ¿Dónde debo colocar la calavera? ¿Cómo puedo vencer a los guerreros jaguar que la custodian? Si son los Chavinavi como esos invocados por ese brujo Merriman, sería una locura ir allí solo - cada uno de ellos es tan fuerte como diez soldados.";
		link.l1.go = "Tuttuat_51";
		break;

	case "Tuttuat_51":
		dialog.text = "Ellos no lo son. Los Chavinavi invocados por un brujo blanco con calavera son débiles. Mucho más débiles que aquellos invocados por Yum Cimil mismo. Nunca los dañas, y ellos te matan con un solo toque de su arma.";
		link.l1 = "Espera, ¿y cómo logró ese 'hombre de cara pálida' entrar al templo y robar el artefacto?";
		link.l1.go = "Tuttuat_52";
		break;

	case "Tuttuat_52":
		dialog.text = "Antes de que ese primer rostro pálido entrara al templo, estaba custodiado por los espíritus de los antepasados muertos. El rostro pálido era un guerrero fuerte y los venció. Cuando robó el orbe del sol naciente, Yum Cimil estaba furioso. Envió fuego y azufre sobre el hombre rostro pálido y casi destruyó el templo, pero él escapó con el artefacto. Ahora Yum Cimil ha convocado a guerreros jaguares invencibles para custodiar el templo.";
		link.l1 = "¡Glorioso! ¿Y cómo me colaré, entonces?";
		link.l1.go = "Tuttuat_53";
		break;

	case "Tuttuat_53":
		dialog.text = "Te ayudo, hombre blanco. Te doy dos amuletos de los Chavines que me traigas. Yo hablaré con los espíritus ancestrales y empoderaré el amuleto. Cuando tengas uno contigo, podrás luchar contra los guerreros jaguar como soldados comunes, serás como uno de ellos, aunque muy fuerte. El amuleto te protegerá y te dará poder de arma para dañar al Chavinavi del templo.";
		link.l1 = "¿Estás seguro de que los amuletos ayudarán?";
		link.l1.go = "Tuttuat_54";
		break;

	case "Tuttuat_54":
		dialog.text = "Yo saber. Yo hablar con ancestros. Yo gran chamán. Tú confiar en mí. Tú llevar dos amuletos. Uno protege. Otro potencia arma. Un amuleto tú debes usar. Cuál - tú eliges. Si tú no llevar amuleto, tú perecer ante guerreros jaguar\nY tú recordar que a medianoche Yum Cimil devolverá a la vida a todos los guerreros que tú mates. Debes calcular el tiempo para no luchar con ellos dos veces, o hacerlo, los espíritus me dicen que podrías.";
		link.l1 = "Ya veo.";
		link.l1.go = "Tuttuat_55";
		break;

	case "Tuttuat_55":
		dialog.text = "Llevas amuletos. Aquí están. Recuerda, su poder tiene límites. Se debilita en una luna. ¿Recuerdas que te dije que no puedes mantener su poder? Solo el gran chamán de nuestra tribu puede sostenerlo.";
		link.l1 = "Recuerdo. Entonces, ¿solo tengo una luna? ¿Un mes?";
		link.l1.go = "Tuttuat_56";
		break;

	case "Tuttuat_56":
		dialog.text = "Sí. Cuando llegues al templo de Yum Cimil, debes encontrar el santuario y una gran estatua del Cóndor en él. Esta es la parte más importante del templo. Aquí colocas la calavera de jade de Yum Cimil, y se levantará la maldición del Caleuche. Cuando él te ataque de nuevo, lo derrotarás como a un hombre ordinario. Luego me traes el amuleto que te quitó.";
		link.l1 = "¿Condor? ¿Qué es?";
		link.l1.go = "Tuttuat_57";
		break;

	case "Tuttuat_57":
		dialog.text = "El cóndor es un gran ave que vive en las montañas de mi hogar. En memoria del hogar, los ancestros construyeron una estatua del cóndor cerca del santuario.";
		link.l1 = "Está bien, lo buscaré...";
		link.l1.go = "Tuttuat_58";
		break;

	case "Tuttuat_58":
		dialog.text = "Ten cuidado. Muchos peligros acechan en el templo junto a los guerreros jaguar.";
		link.l1 = "¿Qué peligros?";
		link.l1.go = "Tuttuat_59";
		break;

	case "Tuttuat_59":
		dialog.text = "No sé con certeza. Lo ves por ti mismo. Puede ser una trampa, o una... confusión. Entrar al santuario es difícil. La entrada está sellada, y debes encontrar la manera de abrirla. Mis ancestros no solo eran grandes guerreros y chamanes, sino también grandes constructores, para abrirla necesitas pensar.";
		link.l1 = "¡Je! Suena aterrador, pero que vengan todos. ¡No perderé tiempo! ¡Zarparé de inmediato!";
		link.l1.go = "Tuttuat_60";
		break;

	case "Tuttuat_60":
		dialog.text = "Ve, guerrero blanco. Yo convocaré a los espíritus para ayudarte contra los guerreros jaguar y el Caleuche. Recuerda, si usas amuletos puedo ayudar, si no perecerás";
		link.l1 = "Gracias, gran chamán... Lo haré.";
		link.l1.go = "Tuttuat_61";
		break;

	case "Tuttuat_61":
		DialogExit();
		npchar.dialog.currentnode = "Tuttuat_62";
		npchar.greeting = "Tuttuat_3";
		Log_Info("Has recibido dos amuletos");
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "kaleuche_amulet2");
		GiveItem2Character(pchar, "kaleuche_amulet3");
		// преобразуем амулеты
		ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_sword");
		ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_shield");
		sld = ItemsFromID("kaleuche_amulet2");
		sld.picIndex = 13;
		sld.picTexture = "ITEMS_36";
		sld.groupID = TALISMAN_ITEM_TYPE;
		sld.unique = true;
		sld.ItemType = "ARTEFACT";
		sld = ItemsFromID("kaleuche_amulet3");
		sld.picIndex = 14;
		sld.picTexture = "ITEMS_36";
		sld.groupID = TALISMAN_ITEM_TYPE;
		sld.unique = true;
		sld.ItemType = "ARTEFACT";
		SetFunctionTimerCondition("Caleuche_TuttuatAmuletOver", 0, 0, 30, false); // таймер
		// делаем доступным Хаэль Роа
		n = FindIsland("KhaelRoa");
		Islands[n].visible = true;
		Island_SetReloadEnableGlobal(Islands[n].id, true);
		Islands[n].reload.l1.radius = 150.0;
		Islands[n].reload.l2.label = "Shore64_1";
		Islands[n].reload.l2.name = "reload_2";
		Islands[n].reload.l2.go = "";
		Islands[n].reload.l2.emerge = "";
		Islands[n].reload.l2.radius = 0.0;
		Islands[n].reload.l2.pic = 0;
		Islands[n].reload.l2.tex = "t1";
		pchar.questTemp.Caleuche = "khaelroa";
		pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1 = "location";
		pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1.location = "KhaelRoa_port";
		pchar.quest.Caleuche_khaelroa_arrive.function = "Caleuche_KhaelRoaArrive";
		AddQuestRecord("Caleuche", "34");
		if (CheckAttribute(pchar, "questTemp.NatanStory"))
		{
			pchar.questTemp.Caleuche.NatanInfo = "true";
			AddQuestUserData("Caleuche", "sText", "Pero tengo una pista: parece que ese capitán blanco, que había visitado el templo de los chavines, no es otro que mi buen amigo Nathaniel Hawk. Recuerdo que me dijo que tenía un mapa de esa isla en Maroon Town. Supongo que le haré una visita a Nathan.");
		}
		else
			AddQuestUserData("Caleuche", "sText", "Es un área enorme en el mar, pero no tengo elección. Tendré que recorrerla entera. Chamán dijo que al norte de Dominica, y no demasiado lejos, así que podría moverme constantemente hacia el norte, podría muy bien estar un poco al este o al oeste. También mencionó a un capitán que destruyó el barco de los no muertos, tal vez tenga suerte y pueda encontrarlo algún día, por desgracia, dijo que sólo tengo un mes para mantener este poder o lo que sea, oh bueno, es lo que es, ¡que comience la búsqueda!");
		break;

	case "Tuttuat_62":
		if (pchar.questTemp.Caleuche == "regard" && CheckCharacterItem(pchar, "kaleuche_amulet1") && CheckCharacterItem(pchar, "kaleuche_amulet2") && CheckCharacterItem(pchar, "kaleuche_amulet3"))
		{
			dialog.text = "Yo hablo con los espíritus. Estuviste en la isla en el templo de Yum Cimil. ¿Encontraste el Caleuche y el amuleto?";
			link.l1 = "Tienes razón, gran chamán. He encontrado la isla, entrado en el templo y dejado la calavera de jade dentro.";
			link.l1.go = "Tuttuat_63";
		}
		else
		{
			dialog.text = "Ve, guerrero blanco.";
			if (CheckAttribute(pchar, "questTemp.Caleuche.AmuletOver"))
			{
				link.l1 = "Tuttuathapak, ves... No llevé la calavera al templo a tiempo, y tus amuletos perdieron su poder.";
				link.l1.go = "Tuttuat_82";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Tuttuat_62_1";
			}
		}
		break;

	case "Tuttuat_62_1":
		DialogExit();
		npchar.dialog.currentnode = "Tuttuat_62";
		break;

	case "Tuttuat_63":
		npchar.greeting = "Tuttuat_2";
		pchar.quest.Caleuche_TuttuatAmuletOver.over = "yes"; // снять таймер
		if (IsEquipCharacterByArtefact(pchar, "kaleuche_amulet2"))
			RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
		if (IsEquipCharacterByArtefact(pchar, "kaleuche_amulet3"))
			RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
		dialog.text = "¿Levantaste la maldición del Caleuche? ¿Ella te encontró después?";
		link.l1 = "Sí. Nos encontramos justo en la isla. Me enfrenté a ella en combate y salí victorioso. Ahora tengo los tres amuletos. Aquí, tómelos.";
		link.l1.go = "Tuttuat_64";
		break;

	case "Tuttuat_64":
		RemoveItems(pchar, "kaleuche_amulet1", 1);
		RemoveItems(pchar, "kaleuche_amulet2", 1);
		RemoveItems(pchar, "kaleuche_amulet3", 1);
		Log_Info("Has entregado tres amuletos Chavin");
		PlaySound("interface\important_item.wav");
		dialog.text = "Eres un guerrero rápido y fuerte, cara pálida. Tuttuathapak no gusta de los hombres blancos, pero yo respeto a un guerrero valiente y hábil. Lo hiciste muy bien. Has librado los mares del Caleuche. Me traes tres amuletos. Yo te recompensaré.";
		link.l1 = "¿Prometiste algo sobre 'poder que podré mantener para siempre'?";
		link.l1.go = "Tuttuat_65";
		break;

	case "Tuttuat_65":
		dialog.text = "Habláis verdad. Os daré ese poder. Ninguno en el Caribe conoce el secreto de la planta que yo conozco. ¡Escuchadme, cara pálida! En mi hogar, hay una planta medicinal. La llamamos Manga Rosa. ¿Habéis oído hablar de esa planta?";
		if (CheckAttribute(pchar, "questTemp.Mangarosa.Tell"))
		{
			link.l1 = "Sí. Lo tuve en mis manos. Los gitanos muestran gran interés en él. Y uno de ellos, la curandera Amelia, incluso puede...";
			link.l1.go = "Tuttuat_66";
		}
		else
		{
			link.l1 = "Ni idea...";
			link.l1.go = "Tuttuat_66_1";
		}
		break;

	case "Tuttuat_66":
		dialog.text = "Yo oí hablar de la herborista Amelia. Ella no sabe poco pero tampoco mucho. Ella no conoce el secreto de la Manga Rosa. Solo un gran chamán de mi tierra natal, de donde la Manga Rosa fue traída aquí, puede usar todo su poder.";
		link.l1 = "¿Qué poder?";
		link.l1.go = "Tuttuat_67";
		break;

	case "Tuttuat_66_1":
		dialog.text = "Esta hierba crece en mi tierra natal, pero también se encuentra en el Caribe. Es una planta alta de color verde claro, con hojas como palmas con los dedos extendidos, y un agradable aroma. La reconocerás al instante y no la confundirás con nada. Yo conozco los secretos de esta planta. Puedo extraer poder de ella.";
		link.l1 = "Entiendo, pero ¿qué tipo de poder?";
		link.l1.go = "Tuttuat_67";
		break;

	case "Tuttuat_67":
		dialog.text = "Yo puedo hacer pociones de Manga Rosa. Pociones muy fuertes. Nadie más que yo en el Caribe puede hacer esas. Mis pociones hacen al hombre para siempre más fuerte, más rápido, más inteligente, con mejor vista, más guapo y más afortunado. Te preparo tres de esas pociones.";
		link.l1 = "¡Muy interesante!";
		link.l1.go = "Tuttuat_68";
		break;

	case "Tuttuat_68":
		dialog.text = "Eres un gran guerrero, así que primero necesitas una poción para hacerte más resistente y otra para hacerte más rápido. Y eliges la tercera poción después de que haga las dos primeras. Pero debes traerme Manga Rosa para hacerlas - no tengo ninguna.";
		link.l1 = "¿Dónde debo buscar la Manga Rosa?";
		link.l1.go = "Tuttuat_69";
		break;

	case "Tuttuat_69":
		dialog.text = "La Manga Rosa es una hierba rara en el Caribe. Crece donde la gente no camina mucho. Los tontos la recogen, la secan y la fuman. Muy tontos. ¡NO LA FUMES! Es un desperdicio de poder... Busca en la jungla y las calas, lugares secretos donde los necios no pisan. Mira cuidadosamente. Para cada poción necesito cinco tallos de Manga Rosa.";
		link.l1 = "Está bien, gran chamán. Volveré a ti una vez que tenga suficiente Manga Rosa.";
		link.l1.go = "Tuttuat_70";
		break;

	case "Tuttuat_70":
		dialog.text = "Ve, guerrero blanco. Tráeme Manga Rosa. No te arrepentirás. Mis pociones son las mejores. Le diré a los espíritus que te ayuden en tu búsqueda.";
		link.l1 = "¡Gracias! ¡Nos vemos, chamán!";
		link.l1.go = "Tuttuat_71";
		break;

	case "Tuttuat_71":
		DialogExit();
		npchar.dialog.currentnode = "Tuttuat_72";
		pchar.questTemp.Caleuche = "mangarosa";
		pchar.questTemp.Caleuche.Mangarosa = 0;
		AddQuestRecord("Caleuche", "41");
		break;

	case "Tuttuat_72":
		dialog.text = "¿Llevas cinco tallos de Manga Rosa para la poción?";
		if (GetCharacterItem(pchar, "cannabis7") >= 5)
		{
			link.l1 = "Sí. Aquí tienes cinco plantas que necesitas.";
			link.l1.go = "Tuttuat_73";
		}
		link.l2 = "Aún no, gran chamán. Mi búsqueda continúa...";
		link.l2.go = "Tuttuat_72_1";
		break;

	case "Tuttuat_72_1":
		DialogExit();
		npchar.dialog.currentnode = "Tuttuat_72";
		break;

	case "Tuttuat_73":
		RemoveItems(pchar, "cannabis7", 5);
		switch (sti(pchar.questTemp.Caleuche.Mangarosa))
		{
		case 0:
			dialog.text = "Muy bien. Ven mañana, cuando se ponga el sol. Te prepararé pociones que aumentarán tu reacción y destreza.";
			link.l1 = "Está bien, chamán. Vendré mañana por la tarde.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 1;
			break;

		case 1:
			dialog.text = "Muy bien. Ven mañana, cuando el sol se ponga. Te prepararé pociones que aumentarán tu resistencia.";
			link.l1 = "Está bien, chamán. Vendré mañana por la tarde.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 2;
			break;

		case 2:
			dialog.text = "Muy bien. ¿Cuál es tu poción para elegir? ¿Poción de fuerza, visión aguda, inteligencia, belleza o suerte?";
			link.l1 = "Poción de fuerza.";
			link.l1.go = "Tuttuat_77_1";
			link.l2 = "Poción de visión aguda.";
			link.l2.go = "Tuttuat_77_2";
			link.l3 = "Poción de inteligencia.";
			link.l3.go = "Tuttuat_77_3";
			link.l4 = "Poción de belleza.";
			link.l4.go = "Tuttuat_77_4";
			link.l5 = "Poción de la suerte.";
			link.l5.go = "Tuttuat_77_5";
			break;
		}
		break;

	case "Tuttuat_74":
		DialogExit();
		npchar.dialog.currentnode = "Tuttuat_75";
		pchar.quest.Caleuche_mangarosa_potion.win_condition.l1 = "Timer";
		pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.hour = 19.0;
		pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.Caleuche_mangarosa_potion.function = "Caleuche_MangarosaPotion";
		break;

	case "Tuttuat_75":
		if (CheckAttribute(pchar, "questTemp.Caleuche.Potion"))
		{
			sTemp = "";
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1)
				sTemp = "  Hace que tus movimientos sean más rápidos y que luches mejor con armas ligeras y finas.";
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2)
				sTemp = "  Te hace más resistente en viajes largos, y luchas mejor con sables afilados.";
			dialog.text = "Poción lista, guerrero pálido. Tómala tú. " + sTemp + "";
			link.l1 = "Gracias, gran chamán.";
			link.l1.go = "Tuttuat_76";
		}
		else
		{
			dialog.text = "No está listo aún, hombre blanco. Ven más tarde. No me molestes.";
			link.l1 = "Está bien...";
			link.l1.go = "Tuttuat_75_1";
		}
		break;

	case "Tuttuat_75_1":
		DialogExit();
		npchar.dialog.currentnode = "Tuttuat_75";
		break;

	case "Tuttuat_76":
		if (sti(pchar.questTemp.Caleuche.Mangarosa) > 2)
		{
			dialog.text = "Prepararé para ti todas las pociones que prometí. Te harás más fuerte. ¿Tú feliz?";
			link.l1 = "Sí, gran chamán. Esa fue realmente una recompensa digna.";
			link.l1.go = "Tuttuat_78";
		}
		else
		{
			dialog.text = "Encuentras cinco tallos más de Manga Rosa, me los traes. Te hago otra poción.";
			link.l1 = "Te traeré más de ellos. ¡Nos vemos!";
			link.l1.go = "Tuttuat_77";
		}
		break;

	case "Tuttuat_77":
		DialogExit();
		npchar.dialog.currentnode = "Tuttuat_72";
		DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
		if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1)
		{
			ChangeItemDescribe("kaleuche_amulet1", "itmdescr_kaleuche_amulet1_potion");
			sld = ItemsFromID("kaleuche_amulet1");
			sld.name = "itmname_kaleuche_amulet1_potion";
			sld.groupID = SPECIAL_ITEM_TYPE;
			sld.picIndex = 15;
			sld.picTexture = "ITEMS_35";
			sld.price = 0;
			sld.Weight = 1.0;
			sld.ItemType = "SUPPORT";
			GiveItem2Character(pchar, "kaleuche_amulet1");
		}
		if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2)
		{
			ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_potion");
			sld = ItemsFromID("kaleuche_amulet2");
			sld.name = "itmname_kaleuche_amulet2_potion";
			sld.groupID = SPECIAL_ITEM_TYPE;
			sld.picIndex = 15;
			sld.picTexture = "ITEMS_35";
			sld.price = 0;
			sld.Weight = 1.0;
			sld.ItemType = "SUPPORT";
			GiveItem2Character(pchar, "kaleuche_amulet2");
		}
		break;

	case "Tuttuat_77_1":
		dialog.text = "Ven mañana, como de costumbre. Te preparo una poción para hacerte más fuerte, y será mejor que pelees con un hacha grande.";
		link.l1 = "Bien.";
		link.l1.go = "Tuttuat_74";
		pchar.questTemp.Caleuche.Mangarosa = 31;
		break;

	case "Tuttuat_77_2":
		dialog.text = "Ven mañana, como de costumbre. Te preparo una poción para agudizar tus ojos y que veas cada objetivo, y mejor será que aciertes con armas de fuego que rugen.";
		link.l1 = "Bien.";
		link.l1.go = "Tuttuat_74";
		pchar.questTemp.Caleuche.Mangarosa = 32;
		break;

	case "Tuttuat_77_3":
		dialog.text = "Ven mañana, como de costumbre. Te prepararé una poción para hacerte más listo, y será mejor que te escondas de los enemigos.";
		link.l1 = "Bien.";
		link.l1.go = "Tuttuat_74";
		pchar.questTemp.Caleuche.Mangarosa = 33;
		break;

	case "Tuttuat_77_4":
		dialog.text = "Ven mañana, como siempre. Te preparo una poción para hacerte más apuesto, y será mejor que persuadas a la gente.";
		link.l1 = "Bien.";
		link.l1.go = "Tuttuat_74";
		pchar.questTemp.Caleuche.Mangarosa = 34;
		break;

	case "Tuttuat_77_5":
		dialog.text = "Ven mañana, como de costumbre. Te preparo una poción para hacerte más afortunado, y tendrás buena suerte.";
		link.l1 = "Bien.";
		link.l1.go = "Tuttuat_74";
		pchar.questTemp.Caleuche.Mangarosa = 35;
		break;

	case "Tuttuat_78":
		dialog.text = "Me alegra que te guste mi arte, el arte del gran chamán.";
		link.l1 = "Decidme, Tuttuathapak, ¿para qué necesitabais estos tres amuletos? Solo tengo curiosidad...";
		link.l1.go = "Tuttuat_79";
		break;

	case "Tuttuat_79":
		dialog.text = "Ya sientes el poder de estos dos amuletos. Los espíritus me ayudarán a darles poder, y los tres amuletos juntos otorgan la gran sabiduría chamánica y la iluminación de mis antepasados, los grandes Chavins.";
		link.l1 = "Ya veo. Muy bien, gracias una vez más por tus excelentes pociones. Eres verdaderamente un gran chamán. Es hora de que me vaya ahora. Adiós, Tuttuathapak, espero verte de nuevo.";
		link.l1.go = "Tuttuat_80";
		break;

	case "Tuttuat_80":
		dialog.text = "Adiós, guerrero blanco. Ya no me buscas. Me voy al retiro, a comprender la sabiduría de mis ancestros. ¡Que los espíritus te ayuden en tus viajes!";
		link.l1 = "Bueno entonces... jaj... que los espíritus iluminen tu camino también, gran chamán. Adiós...";
		link.l1.go = "Tuttuat_81";
		break;

	case "Tuttuat_81":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		GiveItem2Character(pchar, "kaleuche_amulet3");
		ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_potion");
		sld = ItemsFromID("kaleuche_amulet3");
		sld.name = "itmname_kaleuche_amulet3_potion";
		sld.groupID = SPECIAL_ITEM_TYPE;
		sld.picIndex = 15;
		sld.picTexture = "ITEMS_35";
		sld.price = 0;
		sld.Weight = 1.0;
		sld.reaction = sti(pchar.questTemp.Caleuche.Mangarosa);
		sld.ItemType = "SUPPORT";
		i = sti(sld.reaction);
		ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet" + i + "_potion");
		AddQuestRecord("Caleuche", "42");
		pchar.questTemp.Caleuche = "end";
		CloseQuestHeader("Caleuche");
		DeleteAttribute(pchar, "questTemp.Caleuche.Mangarosa");
		DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
		break;

	case "Tuttuat_82":
		Log_Info("Has entregado unos amuletos");
		RemoveItems(pchar, "kaleuche_amulet2", 1);
		RemoveItems(pchar, "kaleuche_amulet3", 1);
		dialog.text = "Haces que me ponga triste, cara pálida. Yo realizo un ritual con los espíritus para dar poder a estos amuletos, y tú lo desperdicias. Yo triste. Ahora vete. Tuttuathapak no tiene nada más que decirte.";
		link.l1 = "Lo siento, tuve muy mala suerte... Bueno, adiós, chamán.";
		link.l1.go = "Tuttuat_83";
		break;

	case "Tuttuat_83":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		AddQuestRecord("Caleuche", "43");
		pchar.questTemp.Caleuche = "end";
		CloseQuestHeader("Caleuche");
		sld = ItemsFromID("SkullAztec");
		sld.price = 10000;
		break;

	// капитан Калеуче
	case "CaleucheCap":
		PlaySound("Voice\Spanish\LE\Baltazar_de_Kortes\Baltazar_01.wav");
		dialog.text = "¡Déjalo, marinero! ¡No puedes vencerme! Y todos mis hombres que yacen en la cubierta unirán sus huesos y se levantarán de nuevo antes del amanecer. No podemos ser asesinados, porque la muerte nos abandonó para siempre.";
		link.l1 = "¡Maldita sea! ¿Estás muerto o vivo? Más probable que sigas vivo - los muertos suelen estar quietos y no blandir espadas. Pero, ¿quién eres y por qué atacaste mi barco?";
		link.l1.go = "CaleucheCap_1";
		break;

	case "CaleucheCap_1":
		dialog.text = "Soy Balthazar de Cordes del Corazón Volador. Cobardes lamentables, que no saben nada de mí, me llaman Van der Decken, capitán del Holandés Errante. Pero no importa. Lo que importa es que llevas un amuleto, que ahora tomaré. ¡Lo necesito! ¡Lo siento! ¡El gran amuleto de los Chavines, uno de los tres, finalmente será mío! ¡Arrodíllate ante mí, mortal! ¡Y podría hacer que tu muerte sea indolora!";
		link.l1 = "¡Vete a la mierda, cadáver!";
		link.l1.go = "CaleucheCap_2";
		break;

	case "CaleucheCap_2":
		DialogExit();
		npchar.MultiFighter = 4.0;
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		AddDialogExitQuest("MainHeroFightModeOn");
		LAi_SetCheckMinHP(pchar, 10, true, "Caleuche_GhostshipGetOut");
		break;

	case "CaleucheCap_3":
		PlaySound("Voice\Spanish\LE\Baltazar_de_Kortes\Baltazar_02.wav");
		dialog.text = "¡Es imposible! Hacía tanto tiempo que no sentía dolor, ni veía mi propia sangre...¿CÓMO?!";
		link.l1 = "Esta vez has perdido, Balthazar de Cordes. Conozco tu historia. La calavera de jade ha sido devuelta al templo de los Chavins, y la maldición de Yum Cimil ya no pesa sobre ti ni sobre tus tripulantes. Ya no devolverás a tus marineros a la vida.";
		link.l1.go = "CaleucheCap_4";
		break;

	case "CaleucheCap_4":
		dialog.text = "Oh, ¿así que te consideras un redentor, quizás? ¡No! ¡Balthazar de Cordes venderá caro lo poco de vida que le queda!";
		link.l1 = "El último viaje del Corazón Volador termina aquí, en Khael Roa. Y no haréis que vuestro barco se levante del fondo del mar, como lo hicisteis hace veinticinco años.";
		link.l1.go = "CaleucheCap_5";
		break;

	case "CaleucheCap_5":
		PlaySound("Voice\Spanish\LE\Baltazar_de_Kortes\Baltazar_03.wav");
		dialog.text = "¡Halcones! Han pasado veinticinco años, y todavía lo recuerdo como si fuera ayer. El resplandor de ese orbe que nos cegó y partió mi barco por la mitad. Esa fue la primera y última derrota del Corazón Volador y Balthazar de Cordes... ¡En guardia, capitán! ¡La muerte en batalla es rápida y afortunada!";
		link.l1 = "...";
		link.l1.go = "CaleucheCap_6";
		break;

	case "CaleucheCap_6":
		DialogExit();
		LAi_SetCurHPMax(npchar);
		QuestAboardCabinDialogFree();
		LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Caleuche_ChangeShip");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	// --> // наш матрос на берегу
	case "on_coast":
		dialog.text = "Finalmente, te despertaste, capitán... ¿Cómo te sientes?";
		link.l1 = "Maldita sea, ¿qué pasó? Me duele la cabeza como si se estuviera partiendo en dos...";
		link.l1.go = "on_coast_1";
		break;

	case "on_coast_1":
		dialog.text = "Cuando entramos en la cabina del capitán, yacías en el suelo, sin un solo movimiento. Los muchachos te recogieron y te arrastraron a nuestro barco y justo a tiempo, ya que los muertos que yacían en la cubierta comenzaron a levantarse de nuevo\n¡Santísima Virgen y todos los Santos! Cortamos rápidamente las amarras e intentamos zarpar, pero una andanada de su barco convirtió rápidamente nuestra vieja bañera en astillas y perdimos el control sobre ella. Luego izaron las velas y desaparecieron en un abrir y cerrar de ojos\nNuestro barco encalló, y todos los que lograron sobrevivir, llegaron a la orilla en un bote. Muchos buenos hombres murieron hoy... si tan solo nos hubiéramos quedado a bordo... Pero estábamos seguros de que la tormenta acabaría con el barco para siempre.";
		link.l1 = "No es culpa vuestra, caballeros. Fue la decisión correcta. Gracias, lo recordaré.";
		link.l1.go = "on_coast_2";
		break;

	case "on_coast_2":
		dialog.text = "Te arrastramos al barco y luego te llevamos a la orilla. Estabas casi muerto...";
		link.l1 = "Te debo la vida. ¿Cuánto tiempo he estado aquí, inconsciente?";
		link.l1.go = "on_coast_3";
		break;

	case "on_coast_3":
		dialog.text = "Por todo un día. Lavamos y vendamos tus heridas, te dimos medicina y te echamos un poco de ron. Deberías recuperarte pronto.";
		link.l1 = "Seguramente no moriré esta vez. Aunque no me siento muy bien...";
		link.l1.go = "on_coast_4";
		break;

	case "on_coast_4":
		dialog.text = "Eso es seguro... ¿Era el Holandés Errante, capitán? ¿Por qué nos atacaron? ¿Y por qué no nos dispararon antes del abordaje, pero casi hundieron nuestro barco con solo una descarga después?";
		link.l1 = "Su capitán necesitaba el amuleto, del cual había hablado con Tuttuathapak, un chamán indio. Por eso no nos hundieron de inmediato, pero cuando su líder se llevó el amuleto, rápidamente se deshicieron de nosotros... ¡Qué pesadilla! ¡Un barco tripulado por los muertos! Imposible de creer...";
		link.l1.go = "on_coast_5";
		break;

	case "on_coast_5":
		dialog.text = "Sí, ahora nos tocó a nosotros encontrarnos con el Holandés Errante. Cuando tenga la oportunidad, iré a la iglesia, encenderé una vela por mi milagrosa liberación y rezaré a nuestro Señor...";
		link.l1 = "Yo también... Supongo. Pero primero volveré a esa aldea. Necesito contarle todo a Tuttuathapak al respecto. ¡Ese maldito barco nos atacó por el amuleto! Estoy seguro de que ese demonio de piel roja tenía algunas ideas, ¿por qué demonios esos muertos vivientes podrían haberlo necesitado?";
		link.l1.go = "on_coast_6";
		break;

	case "on_coast_6":
		dialog.text = "Está bien. Pero ten cuidado, capitán, tus heridas apenas han sanado, al menos lleva a alguien contigo por si acaso.";
		link.l1 = "Seré cuidadoso, lo prometo. ¡Gracias por no abandonarme!";
		link.l1.go = "on_coast_7";
		break;

	case "on_coast_7":
		dialog.text = "¿De qué hablas, capitán? ¡Iríamos hasta el fin del mundo por ti y lucharíamos contra miles de no-muertos! Es una maldita vergüenza que hayamos perdido tanto, pero esta historia vivirá en las leyendas.";
		link.l1 = "...";
		link.l1.go = "on_coast_8";
		break;

	case "on_coast_8":
		chrDisableReloadToLocation = false; // открыть локацию
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		AddQuestRecord("Caleuche", "5");
		break;

	// Фергус Хупер
	case "fergus":
		dialog.text = "¡Oye! Aún no he reunido suficientes pieles de serpiente para vendértelas, ¡así que vete al diablo!";
		link.l1 = "Mm... ¿Eres Fergus Hooper?";
		link.l1.go = "fergus_1";
		break;

	case "fergus_1":
		dialog.text = "No, mi nombre es Tuttuathapak, y te maldeciré si no te largas de inmediato. Así que será mejor que te apresures, o tú...";
		link.l1 = "...perderé la cabeza, quemaré mi propio barco, y mis marineros me matarán y se llevarán todas mis pertenencias. ¿Verdad?";
		link.l1.go = "fergus_2";
		break;

	case "fergus_2":
		sld = characterFromId(pchar.questTemp.Caleuche.Amuletmaster);
		dialog.text = "Arrgh... ¿Qué demonios, quién eres tú!? ¿Cómo te...?";
		link.l1 = "Tenemos un amigo en común, Fergus. Es un farero, y su nombre es " + GetFullName(sld) + ". Me habló de ti y me envió a buscarte. Por cierto, conozco personalmente al chamán Tuttuathapak, así que tu broma no funcionó, lo siento. Escucha, no estoy buscando problemas. Quiero comprarte algo, y no son las pieles de serpiente.";
		link.l1.go = "fergus_3";
		break;

	case "fergus_3":
		dialog.text = "¡Oh, así que conoces a mi viejo amigo! ¿Cómo está? ¿No murió de aburrimiento en su faro todavía? ¡Por favor, siéntate, marinero, toma una copa conmigo!";
		link.l1 = "Lo siento, Fergus, realmente no tengo mucho tiempo. Escucha, necesito ese amuleto indio, uno de aquellos que tu difunto capitán tomó del Continente con Tuttuathapak. Pagaré un buen precio por él, y te librarás de un amuleto peligroso.";
		link.l1.go = "fergus_4";
		break;

	case "fergus_4":
		dialog.text = "¿Y qué tiene de peligroso? No he visto ningún daño de eso hasta ahora. Es solo una piedra inútil";
		link.l1 = "Eso es porque ya no navegas los mares. Yo solía tener un amuleto similar hasta hace poco. Un barco fantasma está cazando estas cosas.";
		link.l1.go = "fergus_5";
		break;

	case "fergus_5":
		dialog.text = "¿Estás bromeando, camarada? ¿Quizás conocer a Tuttuathapak te ha pasado factura? Ten cuidado, capitán, ese diablo de piel roja devorará tu mente...";
		link.l1 = "Créeme o no, pero estoy diciendo la verdad. Yo mismo no lo creería si no lo hubiera visto con mis propios ojos, puedo jurarlo sobre el Libro o puedes preguntar a los que estaban conmigo. Apenas sobreviví después de ese encuentro con el Caleuche.";
		link.l1.go = "fergus_6";
		break;

	case "fergus_6":
		dialog.text = "¿El Caleuche?";
		link.l1 = "Bueno, la mayoría lo llaman el Holandés Errante, pero su verdadero nombre es Corazón Volador. Como sea. Sólo véndeme ese amuleto. De todos modos no te sirve de nada, lo sé.";
		link.l1.go = "fergus_7";
		break;

	case "fergus_7":
		dialog.text = "Eso es correcto. Esto es solo una baratija inútil, aunque bastante hermosa. Escucha, te la habría vendido sin más preámbulos, pero ya ves, ya no la tengo. Fue robada de mi choza entre otras cosas, mientras cazaba en la jungla. Eso sucedió hace poco, hace aproximadamente un mes. Lo siento, pero no hay nada con lo que pueda ayudarte.";
		link.l1 = "¿Y quién lo robó?";
		link.l1.go = "fergus_8";
		break;

	case "fergus_8":
		dialog.text = "¿De verdad piensas que estaría sentado aquí si supiera quién saqueó mi casa? Hay una banda de ladrones y bandidos operando fuera de Belice, y tienen informantes en el pueblo. Bueno, al menos eso es lo que piensa el comandante. Estoy seguro de que fueron ellos.";
		link.l1 = "¿El comandante sabe sobre los bandidos y aún así no hace nada?";
		link.l1.go = "fergus_9";
		break;

	case "fergus_9":
		dialog.text = "Si está haciendo algo o no, no lo sé. Lo único que sé con certeza es que mis cosas se han ido, y tu preciado amuleto con ellas. Trata de buscar a esos bandidos, tal vez lo encuentres en sus bolsillos. Es improbable que hayan logrado venderlo, los mercaderes no tienen necesidad de tales cosas.";
		link.l1 = "Está bien, iré a ver al comandante. ¡Buena suerte, Fergus!";
		link.l1.go = "fergus_10";
		break;

	case "fergus_10":
		DialogExit();
		AddQuestRecord("Caleuche", "9");
		pchar.questTemp.Caleuche.Bandos = "start";
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		break;

	// бандит в городе
	case "Beliz_townbandos":
		dialog.text = "¡Oye! ¿Qué necesitas? No espero ningún invitado. ¡Piérdete!";
		link.l1 = "¿Por qué tan grosero, amigo? Solo quería preguntar...";
		link.l1.go = "Beliz_townbandos_1";
		break;

	case "Beliz_townbandos_1":
		dialog.text = "¿No lo has oído? ¡Lárgate al carajo, o te echo a patadas por la puerta!";
		link.l1 = "Hmm... Bueno, quizás seas la persona que estoy buscando después de todo. Pareces demasiado nervioso, camarada...";
		link.l1.go = "Beliz_townbandos_2";
		break;

	case "Beliz_townbandos_2":
		dialog.text = "¿Te crees muy listo, no es así? Una vez más: o te pierdes ahora mismo, o llamo a los guardias, ¡y te echarán tras las rejas!";
		link.l1 = "¿Echarme tras las rejas? Qué interesante. Sabes, ahora estoy casi seguro de que he encontrado a quien estaba buscando. Muy bien, estoy de acuerdo. Llamemos a los guardias, y luego caminaremos juntos a la oficina del comandante, como una familia feliz. Acabo de estar allí, así que recuerdo el camino... ¡Guardias! ¡GUARDIAS!";
		link.l1.go = "Beliz_townbandos_3";
		break;

	case "Beliz_townbandos_3":
		dialog.text = "¡Que te jodan! ¡Te atravesaré con mi espada!";
		link.l1 = "¡Oh, jo-jo! ¡Bueno, puedes intentarlo!";
		link.l1.go = "Beliz_townbandos_4";
		break;

	case "Beliz_townbandos_4":
		DialogExit();
		DeleteAttribute(npchar, "CityType");
		DeleteAttribute(npchar, "city"); // чтобы не было НЗГ
		LAi_SetImmortal(npchar, false);
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Caleuche_BelizTownbandosDie");
		AddDialogExitQuest("MainHeroFightModeOn");
		pchar.quest.Caleuche_letter.win_condition.l1 = "item";
		pchar.quest.Caleuche_letter.win_condition.l1.item = "kaleuche_letter";
		pchar.quest.Caleuche_letter.function = "Caleuche_FindLetter";
		break;

	// главарь лесных бандосов
	case "Beliz_forestbandos":
		dialog.text = "¡Eh, viajero! Bienvenido, bienvenido... Cena, alojamiento - todo por tu dinero. Así que, prepárate para vaciar tus bolsillos.";
		link.l1 = "No tan rápido, buen hombre. Tengo asuntos contigo.";
		link.l1.go = "Beliz_forestbandos_1";
		break;

	case "Beliz_forestbandos_1":
		dialog.text = "¿Negocios? ¡Ja, ja! ¡Tu único negocio es darme toda tu plata y oro!";
		link.l1 = "Cállate ya. Te traje una carta de Belice que has estado esperando. El mensajero no pudo entenderse con los guardias y me confió el asunto a mí.";
		link.l1.go = "Beliz_forestbandos_2";
		break;

	case "Beliz_forestbandos_2":
		dialog.text = "¡Muéstramelo!";
		link.l1 = "Aquí...";
		link.l1.go = "Beliz_forestbandos_3";
		break;

	case "Beliz_forestbandos_3":
		Log_Info("Has entregado una nota");
		PlaySound("interface\important_item.wav");
		RemoveItems(pchar, "kaleuche_letter", 1);
		dialog.text = "(leyendo) Hm... Eso es ciertamente extraño... ¿Cómo te involucraste?";
		link.l1 = "Ya te dije, capturaron a tu hombre, así que tomé su trabajo. Prometió dinero y una cálida bienvenida de tu parte...";
		link.l1.go = "Beliz_forestbandos_4";
		break;

	case "Beliz_forestbandos_4":
		dialog.text = "¿Una cálida bienvenida? De acuerdo, amigo. Te daremos calor, comida, dinero y todo eso, pero tú también tendrás que demostrarnos que no eres un sabueso de la guardia. Tenemos una cuenta que saldar ahora\nUn mercader ha llegado recientemente a una cala cercana; al parecer, quiere colarse en la ciudad con sus mercancías sin pasar por la aduana. Pero aun así le exigiremos el pago de los derechos. Al fin y al cabo, somos gente de ley. Vendrás con nosotros. ¿Sabes qué extremo de la espada va dónde?";
		link.l1 = "¿Y recibiré una parte de este deber?";
		link.l1.go = "Beliz_forestbandos_5";
		break;

	case "Beliz_forestbandos_5":
		dialog.text = "¡Claro que lo harás! Si eres valiente en la batalla y si te mantienes con vida. Pero no esperes un paseo, el comerciante no está solo, tiene escolta, y una escolta muy grande. Bueno, es hora de irnos - nuestra presa está cerca. ¡Chicos! Preparen sus armas, ¡nos vamos!";
		link.l1 = "...";
		link.l1.go = "Beliz_forestbandos_6";
		break;

	case "Beliz_forestbandos_6":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		pchar.GenQuest.CannotWait = true; // запрет ожидания
		LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
		LocatorReloadEnterDisable(pchar.location, "reload3_back", true);
		for (i = 1; i <= 6; i++)
		{
			sld = characterFromId("Beliz_forestbandos_" + i);
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, "TMP_FRIEND");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Beliz_ExitTown", "goto", "goto" + (rand(1) + 1), "", 10.0);
		}
		DoQuestCheckDelay("OpenTheDoors", 12.0);
		pchar.quest.Caleuche_bandosrobb.win_condition.l1 = "location";
		pchar.quest.Caleuche_bandosrobb.win_condition.l1.location = "Beliz_ExitTown";
		pchar.quest.Caleuche_bandosrobb.function = "Caleuche_JungleBandosRobbery";
		break;

	case "Beliz_forestbandos_7":
		dialog.text = "Veo que no eres un cobarde. ¡Bien hecho! Te has ganado tu parte. ¿Cómo la quieres? ¿Dinero? ¿Mercancía? Llevaban mucho alcohol, seguro que vale mucho.";
		link.l1 = "Efectivo.";
		link.l1.go = "Beliz_forestbandos_8_1";
		link.l2 = "Mercancía.";
		link.l2.go = "Beliz_forestbandos_8_2";
		break;

	case "Beliz_forestbandos_8_1":
		Log_Info("Has recibido 100 doblones");
		PlaySound("interface\important_item.wav");
		TakeNItems(pchar, "gold_dublon", 100);
		dialog.text = "¡Aquí tienes! Y esta bolsa es por entregar la carta.";
		link.l1 = "¡Gracias! ¡Así es como me gusta!";
		link.l1.go = "Beliz_forestbandos_9";
		break;

	case "Beliz_forestbandos_8_2":
		Log_Info("Has recibido 30 botellas de ron");
		Log_Info("Has recibido 12 botellas de vino");
		PlaySound("interface\important_item.wav");
		TakeNItems(pchar, "potionrum", 30);
		TakeNItems(pchar, "potionwine", 12);
		dialog.text = "¡Aquí tienes! Solo no te bebas hasta morir, ¡ja-ja-ja! Y esta bolsa es por entregar la carta.";
		link.l1 = "¡Gracias! ¡Así es como me gusta!";
		link.l1.go = "Beliz_forestbandos_9";
		break;

	case "Beliz_forestbandos_9":
		Log_Info("Has recibido un bolso");
		PlaySound("interface\important_item.wav");
		TakeNItems(pchar, "purse2", 1);
		dialog.text = "Me pareces un tipo decente. ¿Qué tal otra tarea? Es sobre esa carta que me hiciste llegar.";
		link.l1 = "Por supuesto.";
		link.l1.go = "Beliz_forestbandos_10";
		break;

	case "Beliz_forestbandos_10":
		dialog.text = "Entonces ven a la cueva. Hay dos de ellas. Ve a la jungla hasta el punto donde nos encontramos la última vez, luego toma el camino de la izquierda. Nos reunimos en tres días en la entrada de la cueva, desde la medianoche hasta la una. ¿Entendido? Si eres un buen chico, te aceptaremos en nuestra banda. Pero ten en cuenta que si sueltas algo en la ciudad, estás acabado. Tengo un brazo largo.";
		link.l1 = "Deja de asustarme ya. Lo entiendo. Estaré silencioso como un pez. Espérame en tres días, estaré allí. ¡Me encanta el dinero fácil!";
		link.l1.go = "Beliz_forestbandos_11";
		break;

	case "Beliz_forestbandos_11":
		dialog.text = "Está bien, camarada. Ahora piérdete antes de que lleguen los guardias. Nosotros también nos vamos.";
		link.l1 = "Nos vemos, camarada...";
		link.l1.go = "Beliz_forestbandos_12";
		break;

	case "Beliz_forestbandos_12":
		DialogExit();
		LAi_SetImmortal(npchar, false);
		LocatorReloadEnterDisable("Beliz_Jungle_01", "reload2_back", false);
		LocatorReloadEnterDisable("Beliz_Jungle_01", "reload3_back", false);
		LocatorReloadEnterDisable("Beliz_CaveEntrance_2", "reload1_back", true); // закрываем пещеру
		SetFunctionTimerCondition("Caleuche_CaveOpen", 0, 0, 1, false);			 // таймер
		SetFunctionTimerCondition("Caleuche_BelizbandosClear", 0, 0, 4, false);	 // таймер
		DeleteAttribute(pchar, "GenQuest.CannotWait");							 // можно мотать время
		for (i = 1; i <= 6; i++)
		{
			if (GetCharacterIndex("Beliz_forestbandos_" + i) != -1)
			{
				sld = characterFromId("Beliz_forestbandos_" + i);
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "OpenTheDoors", 20.0);
			}
		}
		AddQuestRecord("Caleuche", "13");
		// костер
		ref location = &Locations[FindLocation("Beliz_Jungle_01")];
		DeleteAttribute(location, "fire");
		sld = ItemsFromID("fire");
		sld.shown = false;
		// пакуем схрон в пещере
		pchar.GenQuestBox.Beliz_Cave_2 = true;
		pchar.GenQuestBox.Beliz_Cave_2.box1.items.kaleuche_amulet2 = 1;
		pchar.GenQuestBox.Beliz_Cave_2.box1.items.suit4 = 1;
		pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse1 = 7; // Addon-2016 Jason
		pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse2 = 3; // Addon-2016 Jason
		pchar.GenQuestBox.Beliz_Cave_2.box1.items.potion2 = 10;
		pchar.GenQuestBox.Beliz_Cave_2.box1.items.potionrum = 55;
		pchar.GenQuestBox.Beliz_Cave_2.box1.items.indian_3 = 1;
		pchar.GenQuestBox.Beliz_Cave_2.box1.items.obereg_4 = 1;
		pchar.GenQuestBox.Beliz_Cave_2.box1.items.berserker_potion = 1;
		pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry2 = 15;
		pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry3 = 33;
		// меняем флаг
		pchar.questTemp.Caleuche.Bandos = "know";
		SaveCurrentQuestDateParam("questTemp.Caleuche.belizbandos");
		break;

	// спалили бандосы в пещере
	case "Beliz_cavebandos":
		dialog.text = "¡Qué! ¿Decidiste reclamar alguna de nuestras propiedades? ¡No te saldrás con la tuya, gusano asqueroso!";
		link.l1 = "¿A quién acabas de llamar gusano, ¡escoria?!";
		link.l1.go = "Beliz_cavebandos_1";
		break;

	case "Beliz_cavebandos_1":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		LAi_group_Delete("EnemyFight");
		DialogExit();
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromId("Beliz_cavebandos_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		if (MOD_SKILL_ENEMY_RATE > 4)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Beliz_cavebandos_3", "citiz_23", "man", "man", 30, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 30, 70, 70, "blade_10", "pistol1", "bullet", 150);
			ChangeCharacterAddressGroup(sld, pchar.location, "monsters", "monster16");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Caleuche_CaveBandosDie");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	// капитан гарпии
	case "reginald":
		dialog.text = "¡Hola, colega! ¿Qué te trae por aquí?";
		link.l1 = TimeGreeting() + ", mynheer Jackson. Me alegra finalmente encontrarte.";
		link.l1.go = "reginald_1";
		break;

	case "reginald_1":
		dialog.text = "'¡Mynheer Jackson', ja, ja! Bueno, para ser honesto, pronto me voy a llamar así también. Estoy trabajando para esta maldita Compañía sin parar... pero pagan bien, muy bien... Entonces, ¿qué te trae por aquí, camarada?";
		link.l1 = "Nuestro conocido común, el guardián del faro, me dijo que tenías un amuleto indio antiguo. Supongo que nunca le diste uso y lo necesito con urgencia. Quisiera comprártelo.";
		link.l1.go = "reginald_2";
		break;

	case "reginald_2":
		dialog.text = "Oh, ¿te refieres a ese elegante chisme, del cual había preguntado a ese contramaestre retirado? Sí, amigo, tienes razón, en realidad nunca fue útil, solo se ve bonito.";
		link.l1 = "¿Cuánto quieres por ello?";
		link.l1.go = "reginald_3";
		break;

	case "reginald_3":
		dialog.text = "Verás, hay un pequeño problema... Déjame explicar. No lo tengo conmigo en este momento. Como nunca le encontré utilidad, lo dejé en mi cofre en la orilla, entre mis otras pertenencias.";
		link.l1 = "Oh, eso explica que todavía estás... bueno, no importa. Vamos a ese cofre tuyo, y te compraré el amuleto. Así de simple. ¿Dónde lo tienes?";
		link.l1.go = "reginald_4";
		break;

	case "reginald_4":
		dialog.text = "No es exactamente tan simple. Mi cofre está ubicado en Barbados, en la torre del faro, y está bien cerrado, para que nadie pueda aprovecharse de él en mi ausencia. Y lo siento mucho, pero no puedo ir contigo a Barbados, según mi contrato con los holandeses, tengo que navegar entre Philipsburg y Port Royal y seguir exactamente el itinerario. Y Barbados no está en ese rumbo.";
		link.l1 = "¿Y qué podemos hacer? ¡Realmente, realmente necesito ese amuleto!";
		link.l1.go = "reginald_5";
		break;

	case "reginald_5":
		dialog.text = "Hmm... Bueno, hay una opción. Te doy la llave de mi cofre, y tú navegas a Barbados por tu cuenta. Pero tendrás que compensarme por todas las cosas que hay dentro y puedes quedártelas. Lo siento por la desconfianza, pero debes entender. Nunca te había visto antes.";
		link.l1 = "¿Cuánto?";
		link.l1.go = "reginald_6";
		break;

	case "reginald_6":
		dialog.text = "Quinientas monedas de oro. Ni una menos.";
		if (PCharDublonsTotal() >= 500)
		{
			link.l1 = "¡Lo tienes! Aquí está tu oro.";
			link.l1.go = "reginald_10";
		}
		link.l2 = "Mm... No tengo tantos doblones conmigo.";
		link.l2.go = "reginald_7";
		break;

	case "reginald_7":
		dialog.text = "Entonces ven a verme de nuevo una vez que hayas juntado el dinero. Si me encontraste una vez, me encontrarás de nuevo. Voy a navegar entre San Martín y Jamaica por bastante tiempo ahora.";
		link.l1 = "De acuerdo, trato.";
		link.l1.go = "reginald_8";
		break;

	case "reginald_8":
		DialogExit();
		NextDiag.CurrentNode = "reginald_9";
		npchar.DeckDialogNode = "reginald_9";
		break;

	case "reginald_9":
		dialog.text = "¿Tú otra vez, amigo? ¿Tienes 500 monedas?";
		if (PCharDublonsTotal() >= 500)
		{
			link.l1 = "Sí. Aquí está tu oro.";
			link.l1.go = "reginald_10";
		}
		link.l2 = "Aún no, pero estoy trabajando en ello.";
		link.l2.go = "reginald_8";
		break;

	case "reginald_10":
		Log_Info("Has entregado 500 doblones");
		PlaySound("interface\important_item.wav");
		RemoveDublonsFromPCharTotal(500);
		DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
		dialog.text = "¡Estupendo! Y aquí está tu llave. Y tengo solo una petición: después de que tomes todo lo que hay dentro, por favor deja la llave en la cerradura. Odiaría tener que encargar una nueva cerradura y una llave para ella.";
		link.l1 = "Está bien.";
		link.l1.go = "reginald_11";
		break;

	case "reginald_11":
		dialog.text = "¡Entonces buena suerte para ti, amigo! ¡Buen viaje!";
		link.l1 = "Y lo mismo para usted... ¡Buen viaje, señor Jackson!";
		link.l1.go = "reginald_12";
		break;

	case "reginald_12":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		npchar.DontDeskTalk = true;
		DeleteAttribute(pchar, "questTemp.Caleuche.Garpiya");
		DeleteAttribute(pchar, "questTemp.Garpiya");
		GiveItem2Character(pchar, "kaleuche_key");
		ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
		AddQuestRecord("Caleuche", "20");
		// сундук со схроном
		i = Findlocation("Mayak2");
		Locations[i].models.always.locators = "lighthouse_Blocators";
		locations[i].private1.key = "kaleuche_key";
		locations[i].private1.key.delItem = true;
		locations[i].private1.items.kaleuche_amulet3 = 1;
		locations[i].private1.items.pistol9 = 1;
		locations[i].private1.items.indian_6 = 1;
		locations[i].private1.items.map_barbados = 1;
		locations[i].private1.items.map_part2 = 1;
		locations[i].private1.items.jewelry22 = 5;
		locations[i].private1.items.jewelry17 = 6;
		locations[i].private1.items.jewelry12 = 3;
		locations[i].private1.items.jewelry16 = 2;
		locations[i].private1.items.jewelry20 = 7;
		locations[i].private1.items.jewelry53 = 11;
		locations[i].private1.items.mineral25 = 1;
		locations[i].private1.items.mineral21 = 1;
		locations[i].private1.items.mineral22 = 5;
		locations[i].private1.items.mineral26 = 1;
		locations[i].private1.items.mineral10 = 1;
		locations[i].private1.items.mineral3 = 10;
		pchar.quest.caleuche_amulet3.win_condition.l1 = "item";
		pchar.quest.caleuche_amulet3.win_condition.l1.item = "kaleuche_amulet3";
		pchar.quest.caleuche_amulet3.function = "Caleuche_ThirdAmuletFind";
		break;

	// монах в Виллемстаде
	case "monk_caleuche":
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("villemstad");
		npchar.lifeday = 1;
		dialog.text = "Hola, capitán " + GetFullName(pchar) + ". Encantado de darte la bienvenida a Willemstad.";
		link.l1 = "Hola, Padre. No te recuerdo. ¿Nos conocemos?";
		link.l1.go = "monk_caleuche_1";
		break;

	case "monk_caleuche_1":
		dialog.text = "Hice averiguaciones sobre ti, una vez que tu barco atracó. Y creo que puedo pedirte ayuda.";
		link.l1 = "Muy interesante. ¿Y por qué yo?";
		link.l1.go = "monk_caleuche_2";
		break;

	case "monk_caleuche_2":
		if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
		{
			dialog.text = "Porque has hecho mucho por la República de Provincias Libres. Estás en buenos términos con la Compañía y eres amigo del gobernador. Ya he apelado a varias instancias y fui reprendido, pero espero que una persona noble como tú no rechace una humilde petición del siervo de nuestro Señor.";
		}
		else
		{
			dialog.text = "Porque no estás al servicio de nuestro gobernador. No trabajas para la Compañía y no tienes tratos con nuestro ejército; de lo contrario, lo más probable es que simplemente me apartaras como a una mosca molesta, ya que ya he apelado a varias instancias y fui rechazado.";
		}
		link.l1 = "Está bien, entonces. ¿Cuál es la naturaleza de tu petición?";
		link.l1.go = "monk_caleuche_3";
		break;

	case "monk_caleuche_3":
		sld = characterFromId("Villemstad_Priest");
		dialog.text = "Hay una casa en la parte trasera del banco. Una dama que vivía allí estaba alquilando una habitación a un tipo muy sospechoso, no del lugar, y no era holandés. Y así, nuestro padre superior, el Padre " + sld.name + ", lo había reconocido\nEra Joachim Merriman, un portugués, acusado por la Inquisición de brujería y tratos con poderes impíos. Se escondió de la Inquisición en el Nuevo Mundo. Sabes, los españoles a menudo acusan de herejía y brujería a quienes caen en desgracia para quemarlos en la hoguera, pero... En este caso tenían razón. Merriman es un brujo\nAsí que, había estado viviendo en Willemstad por un tiempo, y luego desapareció tan repentinamente como había surgido. Y después de algún tiempo, una mujer, la que le alquiló la habitación, nunca fue vista saliendo de esa casa. ¡Nunca! Y nunca se la ha visto en ningún lugar desde entonces\nY por las noches los ciudadanos ocasionalmente pueden ver luces rojo-azules parpadeando en las ventanas del segundo piso y escuchar sonidos extraños, casi como si fueran gritos impíos. Padre " + sld.name + " apeló al comandante. Envió una patrulla de cuatro soldados, registraron la casa, pero no encontraron nada: ni a la casera misma, ni a nadie más, ni nada sospechoso en absoluto.\nPero estas cosas extrañas continúan sucediendo. La casera nunca ha aparecido, y esa luz infernal todavía se puede ver allí por las noches. Además, dos mendigos han desaparecido recientemente también. Los escuché hablando en el pórtico; sabían que no había dueños en la casa, así que decidieron alojarse allí. Nadie los ha visto desde entonces.";
		link.l1 = "Supongo que quieres que entre en esa casa y averigüe qué ocurrió realmente, ¿no?";
		link.l1.go = "monk_caleuche_4";
		break;

	case "monk_caleuche_4":
		dialog.text = "Exactamente, noble señor. Por favor, ayude a la Santa Iglesia. El comandante dice que estamos imaginando cosas, ya que su patrulla nunca encontró nada. El gobierno piensa lo mismo. A los plebeyos simplemente no les importa, porque no lo ven como una amenaza clara para ellos.";
		link.l1 = "¿Hmm... Y necesitaré ir allí por la noche?";
		link.l1.go = "monk_caleuche_5";
		break;

	case "monk_caleuche_5":
		sld = characterFromId("Villemstad_Priest");
		dialog.text = "Sí, señor. Está tranquilo allí durante el día, por eso los soldados no encontraron nada, creo que el comandante tiene miedo por sus hombres, yo también lo estaría. Pero, por favor, se lo ruego. Padre " + sld.name + " te lo agradecerá y te recompensará por tu servicio. Una vez que hayas estado en ese antro durante la noche, por favor dile lo que encuentres allí. Te aseguro, nuestras sospechas están bien fundamentadas.";
		link.l1 = "Está bien. Lo pensaré.";
		link.l1.go = "monk_caleuche_6";
		break;

	case "monk_caleuche_6":
		dialog.text = "Gracias, capitán. Espero que no rechace mi humilde petición. Por favor, hágalo en nombre de nuestro Señor, nuestra fe y todo lo que es sagrado. Vaya con mis bendiciones.";
		link.l1 = "...";
		link.l1.go = "monk_caleuche_7";
		break;

	case "monk_caleuche_7":
		DialogExit();
		chrDisableReloadToLocation = false; // открыть локацию
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "none", "", "", "", -1);
		AddQuestRecord("Caleuche", "24");
		if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
		{
			if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul"))
				sTemp = "visitar la casa de Joaquim Merriman, donde, según él, ocurren cosas extrañas por la noche. Al recordar aquel brillo especial en los ojos de Merriman cuando miró la calavera de jade, siento un poco de escalofrío. Parece que el viejo judío no pudo resistirse a la suma de medio millón de pesos. Sea como fuere, no me apetece ir a la antigua morada de Merriman por la noche.";
			else
				sTemp = "visitar la casa de mi viejo conocido Joachim Merriman, donde, al parecer, ocurren cosas extrañas por las noches. Aún recuerdo aquel brillo en los ojos de Merriman, cuando miraba la calavera, y sinceramente me siento asustado. No me entusiasma la idea de visitar su antigua morada por la noche, quién sabe qué clase de demonios acechan allí.";
		}
		else
			sTemp = "visitar la casa en la parte trasera del banco, donde un tal Joachim Merriman había estado alquilando una habitación. Al parecer se trata de ese brujo, del que hablaba Tuttuathapak. Según el monje, en esta casa ocurren cosas extrañas por la noche. Realmente me siento incómodo visitando la antigua casa del brujo, quién sabe qué clase de demonios acechan allí.";
		AddQuestUserData("Caleuche", "sText", sTemp);
		i = Findlocation("Villemstad_town");
		DeleteAttribute(&locations[i], "reload.l14.close_for_night");
		pchar.quest.Caleuche_villemstadhouse.win_condition.l1 = "location";
		pchar.quest.Caleuche_villemstadhouse.win_condition.l1.location = "Villemstad_houseSp1_room";
		pchar.quest.Caleuche_villemstadhouse.win_condition.l2 = "Hour";
		pchar.quest.Caleuche_villemstadhouse.win_condition.l2.start.hour = 1.00;
		pchar.quest.Caleuche_villemstadhouse.win_condition.l2.finish.hour = 3.00;
		pchar.quest.Caleuche_villemstadhouse.function = "Caleuche_CreateJoakimSkel";
		break;

	// охотник у пещеры
	case "cavehunter":
		dialog.text = "Espera, camarada. Más te vale no ir allí, si aprecias tu vida.";
		link.l1 = "¿Y cuál es el trato?";
		link.l1.go = "cavehunter_1";
		break;

	case "cavehunter_1":
		dialog.text = "Créeme, no quieres saberlo. Pero la Muerte misma está a la vuelta de la esquina, y puedo jurar sobre el Libro que no volverás con vida, hay cosas más allá de tu imaginación.";
		link.l1 = "Bueno, si lo dices, no tentaré al destino. Gracias por la advertencia.";
		link.l1.go = "cavehunter_2";
		break;

	case "cavehunter_2":
		dialog.text = "De nada. Mantente alejado de ese camino.";
		link.l1 = "...";
		link.l1.go = "cavehunter_3";
		break;

	case "cavehunter_3":
		DialogExit();
		npchar.dialog.currentnode = "cavehunter_4";
		break;

	case "cavehunter_4":
		dialog.text = "Mantente alejado de ese camino, camarada.";
		link.l1 = "Sí, recuerdo...";
		link.l1.go = "cavehunter_4_1";
		break;

	case "cavehunter_4_1":
		DialogExit();
		npchar.dialog.currentnode = "cavehunter_4";
		break;

	case "cavehunter_5":
		sld = characterFromId("Havana_Priest");
		dialog.text = "¿Estás seguro de que quieres ir allí?";
		link.l1 = "Absolutamente. " + sld.name + ", padre superior de la iglesia en La Habana, me envió aquí. Debo determinar qué está sucediendo aquí y tomar medidas adecuadas.";
		link.l1.go = "cavehunter_6";
		break;

	case "cavehunter_6":
		dialog.text = "¿Qué está pasando aquí? Me temo que estarías temblando de miedo, una vez que veas lo que está sucediendo aquí con tus propios ojos.";
		link.l1 = "¿Te refieres a los muertos vivientes?";
		link.l1.go = "cavehunter_7";
		break;

	case "cavehunter_7":
		dialog.text = "Sí. Y será mejor que creas mis palabras.";
		link.l1 = "Y te creo. Ya me he encontrado con esa cosa impía en Willemstad y la destruí. Y ahora entraré allí y destruiré toda la inmundicia que acecha en esta cueva.";
		link.l1.go = "cavehunter_8";
		break;

	case "cavehunter_8":
		int icpy = GetOfficersQuantity(pchar);
		switch (icpy)
		{
		case 0:
			dialog.text = "¿Vas a ir allí solo? Eres un hombre muerto, compañero. No tienes idea de cuántas de esas cosas hay allí. Bueno, ve, si debes, y yo iré a la iglesia a encender una vela por la paz de tu alma.";
			link.l1 = "No seas tan rápido en enterrarme. He visto peores.";
			link.l1.go = "cavehunter_exit";
			break;

		case 1:
			dialog.text = "¿Sólo ustedes dos? Me temo que no llegarán lejos. No tienen idea de cuántas de esas cosas hay. Es un suicidio.";
			link.l1 = "Simplemente no nos conoces bien, amigo. Hazte a un lado, y purificaremos este antro impío.";
			link.l1.go = "cavehunter_exit";
			break;

		case 2:
			dialog.text = "¿Sólo ustedes tres? Deben ser luchadores experimentados si se atreven a hacerlo. Pero aún así tengo miedo de que no lo logren. No tienen idea de cuántas de esas cosas hay dentro de esa gruta.";
			link.l1 = "Simplemente no nos conoces bien, amigo. Hazte a un lado, y purificaremos este antro impío.";
			link.l1.go = "cavehunter_exit";
			break;

		case 3:
			dialog.text = "Vosotros no sois cobardes, veo. Pero realmente no tenéis idea de cuántas de esas cosas hay allí. En tal asunto, cada hombre cuenta. ¡Al diablo con esto, iré con vosotros y dispararé a esa inmundicia con mi mosquete!";
			link.l1 = "Eres un alma valiente, amigo. No rechazaré tu ayuda. ¡Vámonos!";
			link.l1.go = "cavehunter_9";
			break;
		}
		break;

	case "cavehunter_exit":
		DialogExit();
		npchar.lifeday = 0;
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		break;

	case "cavehunter_9":
		DialogExit();
		npchar.quest.caleuche = true;
		npchar.dialog.currentnode = "cavehunter_10";
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		// закрываем локаторы выхода
		LocatorReloadEnterDisable("Cuba_Jungle_07", "reload1_back", true);
		LocatorReloadEnterDisable("Cuba_Jungle_07", "reload3_back", true);
		break;

	case "cavehunter_10":
		dialog.text = "¡Vamos! ¡Muerte a los inmundos no muertos!";
		link.l1 = "...";
		link.l1.go = "cavehunter_10_1";
		break;

	case "cavehunter_10_1":
		DialogExit();
		npchar.dialog.currentnode = "cavehunter_10";
		break;

	case "cavehunter_11":
		dialog.text = "¡Vaya masacre la que tuvimos! ¡Quién hubiera pensado que tantos muertos se escondían en este lugar! Bueno, al menos ahora podemos descansar... Por favor, dile a ese padre superior tuyo sobre esto, el que te envió aquí. Espero que la Inquisición se ponga manos a la obra después de tu informe. Lidiar con los no muertos es su terreno, después de todo, yo solo soy un simple cazador.";
		link.l1 = "Definitivamente se lo diré. Gracias por la ayuda, camarada. ¡Eres una clase rara, pocos se atreverían a desafiar a la misma muerte! ¡Buena suerte!";
		link.l1.go = "cavehunter_exit";
		break;

	// солдат в крипте при провале
	case "cryptguard":
		dialog.text = "¡Quieto donde estás! ¡Este lugar está fuera de límites!";
		link.l1 = "Eh... ¿Y qué hay ahí?";
		link.l1.go = "cryptguard_1";
		break;

	case "cryptguard_1":
		dialog.text = "Un peligroso hechicero fue encontrado allí. Sólo los santos padres y los soldados que los acompañan pueden entrar.";
		link.l1 = "Ya veo. ¿Arrestaron al hechicero?";
		link.l1.go = "cryptguard_2";
		break;

	case "cryptguard_2":
		dialog.text = "No estoy autorizado para responder a tales preguntas, señor. Es hora de que se vaya.";
		link.l1 = "Está bien, lo tengo. ¡Buena suerte!";
		link.l1.go = "cryptguard_3";
		break;

	case "cryptguard_3":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		AddQuestRecord("Caleuche", "31");
		CloseQuestHeader("Caleuche");
		pchar.questTemp.Caleuche = "end";
		break;

	// чавинави-вождь
	case "Chavinavi":
		PlaySound("Voice\Spanish\LE\Chavinavi\Chavinavi_01.wav");
		dialog.text = "¡Quieto, humano! Estás en el mismo corazón del templo, y has ido demasiado lejos para retroceder ahora.";
		link.l1 = "¿Quién eres?!";
		link.l1.go = "Chavinavi_1";
		break;

	case "Chavinavi_1":
		dialog.text = "Soy el jefe del pueblo Chavinavi, el custodio de las tradiciones, y el guardián de este templo sagrado. No eres el primero en entrar a este lugar, pero sólo dos hombres y una mujer entraron y salieron vivos antes que tú. Esa es la única razón por la que me digno a hablar contigo ahora. ¿Por qué has venido aquí, cara pálida?";
		link.l1 = "He traído una reliquia antigua aquí, el cráneo de jade. Hace cincuenta años fue tomado de un templo indio en lo profundo del continente. Iba a encontrar el santuario y devolver la reliquia a vuestro dios.";
		link.l1.go = "Chavinavi_2";
		break;

	case "Chavinavi_2":
		dialog.text = "Es extraño escuchar tales palabras de alguien de tu clase. No te creo. Vosotros, los de cara pálida, siempre venís a tomar algo, pero nunca para devolver nada.";
		link.l1 = "No miento. Al devolver el cráneo levantaré la maldición impuesta al capitán del barco fantasma que aterroriza el mar Caribe, lo que lo hará mortal de nuevo, y me libraré de él para siempre.";
		link.l1.go = "Chavinavi_3";
		break;

	case "Chavinavi_3":
		dialog.text = "¿Cómo sabes que nuestro Dios levantará esa maldición, cara pálida? ¿Nuestro Dios te habla?";
		link.l1 = "No. Vine aquí por consejo de un gran chamán llamado Tuttuathapak. Como él dijo, la calavera es la clave para la maldición, y este es el único templo en el Caribe. Y sabes qué, creo que él realmente puede conversar con los espíritus del pasado. Quizás incluso contigo, jefe de los guerreros jaguar.";
		link.l1.go = "Chavinavi_4";
		break;

	case "Chavinavi_4":
		dialog.text = "Tus palabras me sorprenden, cara pálida, pero aún no puedo confiar en ti completamente. Sin embargo, si viniste a este templo para devolver nuestra reliquia, seguramente nuestro chamán te habrá contado sobre este lugar, su creación, su historia y sus habitantes\nSi es así, responderás fácilmente a todas mis preguntas. Entonces admitiré que has sido sincero conmigo, te permitiré pasar y, además, te recompensaré.";
		link.l1 = "¡Entonces pregunta!";
		link.l1.go = "question1";
		break;

	case "question1":
		dialog.text = "Soy el jefe de los Chavinavi y de los guerreros jaguar. Hace mil años era humano; ahora cumplo mi deber sagrado en estas cámaras. ¿Qué dios me ordena?";
		link.l1 = "Mictlantecuhtli.";
		link.l1.go = "question1_l";
		link.l2 = "Kukulcán.";
		link.l2.go = "question1_l";
		link.l3 = "Yum Cimil.";
		link.l3.go = "question1_r";
		link.l4 = "Inti.";
		link.l4.go = "question1_l";
		link.l5 = "Kauil.";
		link.l5.go = "question1_l";
		break;

	case "question1_r":
		dialog.text = "Antes de que llegaran tus pálidos compatriotas, toda esta tierra, desde la gran nieve en el norte hasta las grandes llanuras en el sur, nos pertenecía a nosotros, hermanos de una sola familia...";
		link.l1 = "";
		link.l1.go = "question2";
		break;

	case "question1_l":
		dialog.text = "Antes de que vinieran tus gentes pálidas, toda esta tierra, desde la gran nieve en el norte hasta las grandes llanuras en el sur, nos pertenecía a nosotros, hermanos de una misma familia...";
		link.l1 = "";
		link.l1.go = "question2";
		pchar.questTemp.Caleuche.QuestionFail = "true";
		break;

	case "question2":
		dialog.text = "¿Qué tribu india construyó este templo?";
		link.l1 = "Inca.";
		link.l1.go = "question2_l";
		link.l2 = "Chavins.";
		link.l2.go = "question2_r";
		link.l3 = "Maya.";
		link.l3.go = "question2_l";
		link.l4 = "Azteca.";
		link.l4.go = "question2_l";
		link.l5 = "Arawac.";
		link.l5.go = "question2_l";
		break;

	case "question2_r":
		dialog.text = "Nuestra gente progresó, aprendiendo sabiduría, y subyugó nuevos bosques, llanuras e islas. Las personas, que habían construido este templo, llegaron desde los bosques al otro lado del Gran Agua...";
		link.l1 = "";
		link.l1.go = "question3";
		break;

	case "question2_l":
		dialog.text = "Nuestra gente progresó, aprendiendo sabiduría, y sometieron nuevos bosques, llanuras e islas. Las personas, que habían construido este templo, llegaron desde los bosques al otro lado del Gran Agua...";
		link.l1 = "";
		link.l1.go = "question3";
		pchar.questTemp.Caleuche.QuestionFail = "true";
		break;

	case "question3":
		dialog.text = "¿Quién lideró la partida de esas gloriosas personas?";
		link.l1 = "Gran cacique.";
		link.l1.go = "question3_l";
		link.l2 = "Gran sacerdote.";
		link.l2.go = "question3_l";
		link.l3 = "Hijo del gran cacique.";
		link.l3.go = "question3_r";
		link.l4 = "Hijo del gran sacerdote.";
		link.l4.go = "question3_l";
		link.l5 = "La tripulación no tenía líder.";
		link.l5.go = "question3_l";
		break;

	case "question3_r":
		dialog.text = "Los indios, valientes guerreros y viajeros, siempre amaron y reverenciaron su tierra natal, incluso después de establecerse en un nuevo lugar. Como muestra de su amor por su hogar, construyeron una estatua en el templo en forma de un pájaro, el símbolo de su hogar. Está detrás de mí...";
		link.l1 = "";
		link.l1.go = "question4";
		break;

	case "question3_l":
		dialog.text = "Los indios, valientes guerreros y viajeros, siempre amaron y reverenciaron su tierra natal, incluso después de establecerse en un nuevo lugar. Como muestra de su amor por su hogar construyeron una estatua en el templo en forma de un pájaro, el símbolo de su hogar. Está detrás de mí...";
		link.l1 = "";
		link.l1.go = "question4";
		pchar.questTemp.Caleuche.QuestionFail = "true";
		break;

	case "question4":
		dialog.text = "¿Cuál es el nombre de este pájaro?";
		link.l1 = "Albatros.";
		link.l1.go = "question4_l";
		link.l2 = "Águila.";
		link.l2.go = "question4_l";
		link.l3 = "Buitre.";
		link.l3.go = "question4_l";
		link.l4 = "Roc.";
		link.l4.go = "question4_l";
		link.l5 = "Condor.";
		link.l5.go = "question4_r";
		break;

	case "question4_r":
		dialog.text = "Años de prosperidad han pasado y se han desvanecido, como la llama de la lámpara, y la vida abandonó la isla. Solo el templo quedó aquí como un recordatorio del gran poder de los antiguos indios. El último chamán dejó en un pedestal una sagrada esfera solar, que daba poder a los valientes y castigaba a los malvados. Fue tomada por el hombre que estuvo aquí antes que tú.";
		link.l1 = "";
		link.l1.go = "question5";
		break;

	case "question4_l":
		dialog.text = "Los años de prosperidad han pasado y se han desvanecido, como la llama de la lámpara, y la vida abandonó la isla. Solo el templo quedó en pie aquí como recordatorio del gran poder de los antiguos indios. El último chamán dejó en un pedestal un orbe solar sagrado, que daba poder a los valientes y castigaba a los malvados. Fue tomado por el hombre que estuvo aquí antes que tú.";
		link.l1 = "";
		link.l1.go = "question5";
		pchar.questTemp.Caleuche.QuestionFail = "true";
		break;

	case "question5":
		dialog.text = "¿Cuál era el nombre de ese orbe sagrado?";
		link.l1 = "Orbe del sol resplandeciente.";
		link.l1.go = "question5_l";
		link.l2 = "Orbe de los rayos del sol.";
		link.l2.go = "question5_l";
		link.l3 = "Orbe del sol del mediodía.";
		link.l3.go = "question5_l";
		link.l4 = "Orbe del sol naciente.";
		link.l4.go = "question5_r";
		link.l5 = "Orbe del sol poniente.";
		link.l5.go = "question5_l";
		break;

	case "question5_r":
		if (CheckAttribute(pchar, "questTemp.Caleuche.QuestionFail"))
		{
			PlaySound("Voice\Spanish\LE\Chavinavi\Chavinavi_02.wav");
			dialog.text = "¡Las respuestas incorrectas indican que me mentiste, hombre blanco! ¡Has venido con malas intenciones! Lograste escabullirte más allá de los guardianes del templo y el santuario, descubriste cómo funcionaba el mecanismo de la puerta, pero aún así no escaparás de un combate mortal conmigo. ¡Prepárate para morir, rostro pálido!";
			link.l1 = "Bueno, si insistes - veamos, qué tan gran guerrero eres...";
			link.l1.go = "chavinavi_fight";
		}
		else
		{
			dialog.text = "Tu conocimiento de mi gente y mi templo te honra, rostro pálido. Ahora te creo. Ve y cumple con aquello para lo que viniste aquí. Coloca la reliquia sagrada en un pedestal frente al cóndor, donde solía residir el orbe del sol naciente.\nLuego regresa a mí. Tu adoración a Yum Cimil y la decisión de devolver voluntariamente lo que fue robado por tus hermanos deben ser recompensadas.";
			link.l1 = "Gracias por vuestra confianza, gran cacique.";
			link.l1.go = "chavinavi_exit";
		}
		break;

	case "question5_l":
		PlaySound("Voice\Spanish\LE\Chavinavi\Chavinavi_02.wav");
		dialog.text = "¡Respuestas incorrectas indican que me mentiste, hombre blanco! ¡Has venido con intenciones malvadas! Lograste escabullirte más allá de los guardianes del templo y del santuario, descubriste cómo funcionaba el mecanismo de la puerta, pero aún así no escaparás de un combate mortal conmigo. ¡Prepárate para morir, rostro pálido!";
		link.l1 = "Bueno, si insistes - veamos qué tan gran guerrero eres...";
		link.l1.go = "chavinavi_fight";
		break;

	case "chavinavi_fight":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		LAi_group_Delete("EnemyFight");
		DialogExit();
		n = 1;
		if (MOD_SKILL_ENEMY_RATE > 2)
			n = 3;
		if (MOD_SKILL_ENEMY_RATE > 4)
			n = 5;
		for (i = 1; i <= n; i++)
		{
			sld = characterFromId("TopChavinavi_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Caleuche_TopChavinaviDie");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "chavinavi_exit":
		DialogExit();
		sld = ItemsFromID("SkullAztec");
		sld.shown = "0";
		sld.useLocation = "KhaelRoa_Treasure_Alcove";
		sld.useLocator = "button01";
		LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;

	case "Chavinavi_5":
		PlaySound("Voice\Spanish\LE\Chavinavi\Chavinavi_03.wav");
		dialog.text = "Te creo. Vamos, cumple con la tarea que viniste a hacer aquí. Me alegra que no fueras el mentiroso como la mayoría de tus hermanos. Yo también cumpliré mi palabra. Aquí, toma este regalo de mí parte, el símbolo del poder de los guerreros jaguar. El propio Yum Cimil infundió a esta piel un poco de su fuerza.";
		link.l1 = "¡Vaya! ¡Es tan hermoso!";
		link.l1.go = "Chavinavi_6";
		break;

	case "Chavinavi_6":
		GiveItem2Character(pchar, "KhaelRoa_item");
		Log_Info("Has recibido la piel de jaguar");
		PlaySound("interface\important_item.wav");
		dialog.text = "Esta no es una simple piel. Una vez que te la pongas, ganarás la fuerza del guerrero jaguar. El poder de tu arma que respira fuego y dispara plomo aumentará diez veces, y podrás llenar el campo de batalla con los cadáveres de tus enemigos\nPero ningún mortal puede sostener el poder que Yum Cimil puso en esta piel. Una vez que la liberes, te acompañará solo hasta la próxima medianoche, y luego se desvanecerá. Cuídala, cara pálida, y no desperdicies su poder en una escaramuza insignificante.";
		link.l1 = "¡Gracias! Solo lo usaré cuando esté totalmente abrumado por los enemigos.";
		link.l1.go = "Chavinavi_7";
		break;

	case "Chavinavi_7":
		dialog.text = "Ahora ve. Y advierte a tus hermanos que no alteren la serenidad de estas cámaras sagradas. Los guerreros jaguar no muestran piedad a los rostros pálidos y no les darán cuartel.";
		link.l1 = "Adiós, cacique.";
		link.l1.go = "Chavinavi_8";
		break;

	case "Chavinavi_8":
		DialogExit();
		LAi_SetPlayerType(pchar);
		n = 1;
		if (MOD_SKILL_ENEMY_RATE > 2)
			n = 3;
		if (MOD_SKILL_ENEMY_RATE > 4)
			n = 5;
		for (i = 1; i <= n; i++)
		{
			sld = characterFromId("TopChavinavi_" + i);
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
		}
		AddQuestRecord("Caleuche", "38");
		AddCharacterExpToSkill(pchar, "Fortune", 200);
		AddCharacterExpToSkill(pchar, "Leadership", 200);
		ChangeCharacterComplexReputation(pchar, "authority", 2);
		ChangeIndianRelation(10.0);
		break;

	case "":
		dialog.text = "";
		link.l1 = "";
		link.l1.go = "";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
