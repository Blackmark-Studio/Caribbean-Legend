// Абрахам Норман
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Hay algo que necesites?";
		link.l1 = "No, nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "norman_us":
		if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
		{
			dialog.text = LinkRandPhrase("¿Qué necesitas, camarada? Sigue tu camino, ocúpate de tus asuntos. Sólo déjame en paz.", "Eh, eh, amigo. ¿Vas de paseo? Bueno, sigue caminando y deja al señor Abraham en paz. Él también está dando un paseo. Está tomando un poco de aire fresco del mar.", "Hola, amigo. ¿Quieres charlar? Hay solo un problema: no estoy de humor para conversar. Así que ve a buscar a otro a quien molestar. Ve a relajarte en la taberna. Tómate un poco de ron...");
			link.l1 = "Escucha, Abraham, ¿te has topado recientemente con un hombre llamado Miguel Dichoso en Isla Tesoro? Es un tipo bastante conocido por aquí.";
			link.l1.go = "tieyasal";
			break;
		}
		dialog.text = NPCStringReactionRepeat(LinkRandPhrase("¿Qué necesitas, camarada? Sigue tu camino, ocúpate de tus asuntos. Sólo déjame en paz.", "Eh, eh, camarada. ¿Vas a dar un paseo? Bueno, tú sigue caminando y deja al señor Abraham en paz. Él también va a dar un paseo. Está tomando un poco de aire fresco del mar.", "Hola, camarada. ¿Quieres charlar? Hay solo un problema: no estoy de humor para conversar. Así que ve a molestar a otro. Anda a relajarte en la taberna. Tómate un poco de ron..."), LinkRandPhrase("Hola, marinero. ¿Qué, eres cabezón o qué? Pensé que lo había dejado bastante claro.", "Amigo, ve a descansar un poco. Parece que estás un poco duro de oído.", "Eh compadre, ¿qué, eres tonto o qué? Ya te lo he dicho claramente."), "Compañero, no me hagas enfadar. He masacrado a tantos grumetes en mi tiempo, uno más o menos realmente no hace diferencia.", "Está bien, me has cabreado. Ahora saca tu espada oxidada o corre tan rápido como puedas. Recomiendo la segunda opción...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Está bien, amigo. No voy a molestarte.", "Está bien, está bien. Lo entiendo...", "¡Vaya, pareces ser el trueno de los mares! Muy bien, me largo de aquí.", "¿Qué?!", npchar, Dialog.CurrentNode);
		link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
		NextDiag.TempNode = "norman_us";
		break;

	case "norman_fes":
		if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
		{
			dialog.text = LinkRandPhrase("¿Qué necesitas, camarada? Sigue tu camino, ocúpate de tus asuntos. Solo déjame en paz.", "Eh, eh, amigo. ¿Vas a dar un paseo? Bueno, sigue caminando y deja al señor Abraham en paz. Él también va a dar un paseo. Está tomando un poco de aire fresco del mar.", "Hola, compadre. ¿Quieres charlar? Hay solo un problema: no estoy de humor para conversar. Así que ve a molestar a otro. Ve a relajarte en la taberna. Tómate un poco de ron...");
			link.l1 = "Escucha, Abraham, ¿te encontraste recientemente con un hombre llamado Miguel Dichoso en Isla Tesoro? Es un tipo bastante conocido por aquí.";
			link.l1.go = "tieyasal";
			break;
		}
		switch (hrand(5))
		{
		case 0:
			dialog.text = "¡Quieto! Soy el gobernador de esta isla. ¿Qué, no me crees?!";
			link.l1 = "¡Por supuesto que sí! ¿Quién no conoce al gobernador de Isla Tesoro...?";
			link.l1.go = "norman_fes0_fight";
			link.l2 = "Ja, llámate almirante mientras estás en eso, ¡definitivamente me lo creo!";
			link.l2.go = "norman_fes0_peace";
			break;

		case 1:
			dialog.text = "¡Firmes! ¡Mirad, al almirante Barbarigo! ¿No reconoces mi famosa espada de caballería?";
			link.l1 = "¡Mis disculpas, señor Almirante! A partir de ahora, estaré más atento.";
			link.l1.go = "norman_fes1_peace";
			link.l2 = "Tu espada de caballería es bien conocida. Lástima que esté en manos de un necio.";
			link.l2.go = "norman_fes1_fight";
			break;

		case 2:
			dialog.text = "Como puedes ver, estoy aquí en exilio. Estoy esperando más notificaciones del General Monk. Te pido que no divulgues mi identidad real oculta. La inteligencia de Cromwell tiene oídos largos.";
			link.l1 = "Pero por supuesto, su Majestad. Nadie jamás sabrá que Karl II se esconde en las Indias Occidentales.";
			link.l1.go = "norman_fes2_fight";
			link.l2 = "Pues, y yo soy el Papa Inocencio X entonces.";
			link.l2.go = "norman_fes2_peace";
			break;

		case 3:
			dialog.text = "¿Qué te pasó, Blaze? Te he estado buscando durante dos días. ¡Has olvidado por completo a tu padre Nicolás!";
			link.l1 = "¡No tengo tiempo para ti, padre! Estoy hasta el cuello.";
			link.l1.go = "norman_fes3_peace";
			link.l2 = "Está equivocado, señor. Mi nombre es " + GetFullName(pchar) + ".";
			link.l2.go = "norman_fes3_fight";
			break;

		case 4:
			dialog.text = "Sh-sh... Soy Davy Jones. Dime, ¿tienes miedo a la muerte?";
			link.l1 = "Por supuesto que sí, señor Jones. Especialmente después de una resaca.";
			link.l1.go = "norman_fes4_fight";
			link.l2 = "Una muerte es una tragedia, mil muertes son solo una estadística.";
			link.l2.go = "norman_fes4_peace";
			break;

		case 5:
			dialog.text = "Tengo prisa por terminar mi nueva obra. ¡Debes ayudarme a terminar la frase '¿Ser o no ser'?! ";
			link.l1 = "¡Esa es la cuestión! ¿Deberemos soportar la ofensa y seguir adelante...?";
			link.l1.go = "norman_fes5_fight";
			link.l2 = "Una bebida, seguro. ¡Pero no me sorprendería agarrarme una enfermedad en un burdel!";
			link.l2.go = "norman_fes5_peace";
			break;
		}
		break;

	case "norman_fes0_fight":
		dialog.text = "¿De qué demonios estás hablando? ¡¿'Tesoro'?! ¡Podrías llamarlo las Bermudas! ¡Esta isla se llama Isla Norman por mí y no lo olvides! Voy a tener que enseñarte geografía...";
		link.l1 = "¡Eh! ¿Qué quieres decir?!";
		link.l1.go = "fight";
		NextDiag.TempNode = "norman_fight_again";
		break;

	case "norman_fes0_peace":
		dialog.text = "Tienes razón, marinero. Soy realmente el Almirante Barbarigo, pero eso es estrictamente entre nosotros. Prepárate para marchar. Pronto nos moveremos. Eso te será de utilidad.";
		link.l1 = "¡Estoy extremadamente agradecido!";
		link.l1.go = "norman_fes0_exit";
		break;

	case "norman_fes0_exit":
		DialogExit();
		NextDiag.CurrentNode = "norman_fes_again";
		PlaySound("interface\important_item.wav");
		if (GetDataDay() == 12)
		{
			GiveItem2Character(pchar, "pistol2");
			Log_Info("Has recibido una escopeta de tres cañones");
		}
		else
		{
			if (GetDataDay() == 23 && GetDataMonth() == 2)
			{
				GiveItem2Character(pchar, "mushket1");
				Log_Info("Has recibido un mosquete de mecha");
			}
			else
			{
				GiveItem2Character(pchar, "cartridge");
				Log_Info("Has recibido un cartucho de papel");
			}
		}
		break;

	case "norman_fes1_fight":
		dialog.text = "Veremos quién es el tonto ahora mismo. ¡En guardia!";
		link.l1 = "¿¡Hablas en serio?!";
		link.l1.go = "fight";
		NextDiag.TempNode = "norman_fight_again";
		break;

	case "norman_fes1_peace":
		dialog.text = "¡Qué te dije! Aquí, bebe a mi salud.";
		link.l1 = "¡Fondo blanco, almirante!";
		link.l1.go = "norman_fes1_exit";
		break;

	case "norman_fes1_exit":
		DialogExit();
		NextDiag.CurrentNode = "norman_fes_again";
		PlaySound("interface\important_item.wav");
		if (GetDataDay() == 13)
		{
			GiveItem2Character(pchar, "gold_dublon");
			Log_Info("Has recibido un doblón de oro");
		}
		else
		{
			if (GetDataDay() == 1 && GetDataMonth() == 4)
			{
				GiveItem2Character(pchar, "chest");
				Log_Info("Has recibido un cofre con doblones");
			}
			else
			{
				AddMoneyToCharacter(pchar, 5);
			}
		}
		break;

	case "norman_fes2_fight":
		dialog.text = "¡Te pedí que no divulgaras mi nombre! Ahora tendré que deshacerme de ti como testigo peligroso...";
		link.l1 = "¡Oh, he estado esperando esto!";
		link.l1.go = "fight";
		NextDiag.TempNode = "norman_fight_again";
		break;

	case "norman_fes2_peace":
		dialog.text = "¡Perdonadme, su Gracia! No os reconocí con este atuendo. Por favor, aceptad este modesto regalo de un verdadero católico.";
		link.l1 = "La locura se manifiesta...";
		link.l1.go = "norman_fes2_exit";
		break;

	case "norman_fes2_exit":
		DialogExit();
		NextDiag.CurrentNode = "norman_fes_again";
		PlaySound("interface\important_item.wav");
		if (GetDataDay() == 14)
		{
			GiveItem2Character(pchar, "amulet_10");
			Log_Info("Has recibido el Amuleto del Trabajador Maravilloso");
		}
		else
		{
			if (GetDataDay() == 25 && GetDataMonth() == 12)
			{
				GiveItem2Character(pchar, "totem_04");
				Log_Info("Has recibido el Talismán del Cómplice");
			}
			else
			{
				GiveItem2Character(pchar, "Mineral3");
				Log_Info("Has recibido un vela de cera");
			}
		}
		break;

	case "norman_fes3_fight":
		dialog.text = "¡Todos vienen por mí! ¡Atrapé a un espía que se parece a mi hijo! ¡Estoy seguro de que Thomas lo envió para sacarme el segundo ojo!";
		link.l1 = "¡Lárgate, imbécil!";
		link.l1.go = "fight";
		NextDiag.TempNode = "norman_fight_again";
		break;

	case "norman_fes3_peace":
		dialog.text = "Estás cansado y no tienes buen aspecto, joven. Anda, ve y recibe algo de tratamiento.";
		link.l1 = "¡Gracias!";
		link.l1.go = "norman_fes3_exit";
		break;

	case "norman_fes3_exit":
		DialogExit();
		NextDiag.CurrentNode = "norman_fes_again";
		PlaySound("interface\important_item.wav");
		if (GetDataDay() == 15)
		{
			GiveItem2Character(pchar, "potion4");
			Log_Info("Has recibido una poción");
		}
		else
		{
			if (GetDataDay() == 19 && GetDataMonth() == 6)
			{
				GiveItem2Character(pchar, "talisman8");
				Log_Info("Has recibido el Amuleto del Escorpión");
			}
			else
			{
				GiveItem2Character(pchar, "potion1");
				Log_Info("Has recibido esencia correctiva")
			}
		}
		break;

	case "norman_fes4_fight":
		dialog.text = "No temas, camarada. Mira, morir no da miedo en absoluto...";
		link.l1 = "¡Parece que no estás bromeando!";
		link.l1.go = "fight";
		NextDiag.TempNode = "norman_fight_again";
		break;

	case "norman_fes4_peace":
		dialog.text = "Al parecer, no tienes miedo. Lo sabía. ¡Eso es valentía!";
		link.l1 = "Eres un viejo gracioso...";
		link.l1.go = "norman_fes4_exit";
		break;

	case "norman_fes4_exit":
		DialogExit();
		NextDiag.CurrentNode = "norman_fes_again";
		PlaySound("interface\important_item.wav");
		if (GetDataDay() == 17)
		{
			GiveItem2Character(pchar, "cirass6");
			Log_Info("Has recibido un chaleco tragafuegos");
		}
		else
		{
			if (GetDataDay() == 1 && GetDataMonth() == 1)
			{
				GiveItem2Character(pchar, "cirass3");
				Log_Info("Has recibido una coraza de desfile");
			}
			else
			{
				GiveItem2Character(pchar, "Mineral18");
				Log_Info("Has recibido tabaco");
			}
		}
		break;

	case "norman_fes5_fight":
		dialog.text = "Eres un poeta de pacotilla, Marinero. ¿Podría ser que tu espada sea más ágil que tu lengua?";
		link.l1 = "¡Caramba! ¡Ese sable de caballería tuyo no es una farsa en absoluto!";
		link.l1.go = "fight";
		NextDiag.TempNode = "norman_fight_again";
		break;

	case "norman_fes5_peace":
		dialog.text = "¡Caray! ¡Las cosas te han ido bastante bien! ¿Qué tal eso para tu imaginación?";
		link.l1 = "Vuelve otra vez.";
		link.l1.go = "norman_fes5_exit";
		break;

	case "norman_fes5_exit":
		DialogExit();
		NextDiag.CurrentNode = "norman_fes_again";
		PlaySound("interface\important_item.wav");
		PlaySound("interface\important_item.wav");
		if (GetDataDay() == 16)
		{
			GiveItem2Character(pchar, "potionrum");
			Log_Info("Has recibido una botella de ron");
		}
		else
		{
			if (GetDataDay() == 28 && GetDataMonth() == 11)
			{
				GiveItem2Character(pchar, "totem_01");
				Log_Info("Has recibido un amuleto 'Garganta de hierro fundido'");
			}
			else
			{
				GiveItem2Character(pchar, "Mineral17");
				Log_Info("Has recibido un frasco de vidrio");
			}
		}
		break;

	case "norman_fight_again":
		dialog.text = "¡Ajá, te reconozco! ¡Ja-ja!";
		link.l1 = "De nuevo...";
		link.l1.go = "fight";
		break;

	case "norman_fes_again":
		dialog.text = "Está bien, amigo, ya hemos hablado. Ahora sigue tu camino.";
		link.l1 = "Como digas...";
		link.l1.go = "exit";
		NextDiag.TempNode = "norman_fes_again";
		break;

	case "tieyasal":
		dialog.text = "Dichoso? ¿Para qué lo necesitas, eh?";
		link.l1 = "Bueno, lo necesito. Simplemente lo necesito. Entonces, ¿lo has visto?";
		link.l1.go = "tieyasal_1";
		link.l2 = "¿Qué quieres decir con que para qué lo necesito? Miguel es mi viejo camarada, un amigo podrías decir. Se supone que él...";
		link.l2.go = "tieyasal_2";
		link.l3 = "Quiero que me traiga un nuevo navío, tal como lo hizo una vez para Shark Dodson.";
		link.l3.go = "tieyasal_3";
		if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
		{
			link.l4 = "Miguel Dichoso ha matado a un hombre. Por eso lo estoy buscando.";
			link.l4.go = "tieyasal_4";
		}
		npchar.quest.Tieyasal = "true";
		break;

	case "tieyasal_1":
		dialog.text = "Solo lo necesitas a él... ¡Solo lo necesitas a él! ¡Todo lo que necesitas es Miguel Dichoso! No, no lo he visto. No lo he visto en mucho tiempo. No hay nada con lo que pueda ayudarte, marinero.";
		link.l1 = "Mm... Está bien, adiós.";
		link.l1.go = "exit";
		break;

	case "tieyasal_2":
		dialog.text = "Un amigo, dices... Parece que ha cultivado un montón de amigos. Está a punto de tener un amigo menos...";
		link.l1 = "Eh, viejo. ¿Qué te pasa?";
		link.l1.go = "fight";
		NextDiag.TempNode = "norman_fight_again";
		break;

	case "tieyasal_3":
		dialog.text = "Sí, Dichoso es un maestro en tales oficios de cualquier manera que lo mires. Pero no sé dónde está. Vino por aquí pero se fue de nuevo. Así que ve a ver a Alexus, Marinero. Él te armará una maravillosa bañera.";
		link.l1 = "Mm... Gracias por el consejo, camarada.";
		link.l1.go = "exit";
		break;

	case "tieyasal_4":
		dialog.text = "¿Y a quién fue que Dichoso le dio matarile para que andes buscándolo, eh compadre? ";
		link.l1 = "";
		Link.l1.edit = 8;
		link.l1.go = "tieyasal_5";
		break;

	case "tieyasal_4_1":
		dialog.text = "¿Qué quieres decir? ¿A cuál Sharp mató exactamente? Hay muchos Sharps, ya sabes.";
		link.l1 = "";
		Link.l1.edit = 8;
		link.l1.go = "tieyasal_5";
		break;

	case "tieyasal_5":
		sTemp = GetStrSmallRegister(dialogEditStrings[8]);
		if (sTemp == "blaze sharp")
		{
			dialog.text = "Sh-sh-sh...(mirando alrededor) ¿Así que tú también piensas que Blaze Sharp fue asesinado por Dichoso?";
			link.l1 = "Sí. No solo tengo mis sospechas, sino pruebas sólidas. Entradas en su diario de bitácora...";
			link.l1.go = "tieyasal_6";
			break;
		}
		if (sTemp == "sharp")
		{
			dialog.text = "Adelante, pequeño marinero...";
			link.l1 = "¿Qué quieres decir? Cuéntame más.";
			link.l1.go = "tieyasal_4_1";
			break;
		}
		dialog.text = "Ah...Bueno. Lo mató y eso es todo. ¿Sabes cuántos asesinos tenemos por aquí corriendo? ¡Cada segundo hombre! No, Marinero. No he visto a Dichoso en mucho tiempo. No puedo ayudarte con nada.";
		link.l1 = "Lástima...";
		link.l1.go = "exit";
		break;

	case "tieyasal_6":
		dialog.text = "Cálmate, camarada. ¿Cómo te llamas, eh? De alguna manera se me ha escapado de la memoria...";
		link.l1 = "Capitán " + GetFullName(pchar) + ".";
		link.l1.go = "tieyasal_7";
		break;

	case "tieyasal_7":
		dialog.text = "Escucha, " + pchar.name + ". Dichoso mató al pobre Blaze. Lo vi con mis propios ojos, sí-sí. Pero no me creen. Verás, piensan que estoy loco. Uno de los suyos, pero loco. ¡Y solía ser el mejor oficial de abordaje en la tripulación del propio Nicolas Sharp! ¡Buenos tiempos! Pero eventualmente perdí mis garras, pezuña y lente y me quedé varado.\n¿Qué? ¡Ah, cierto! Todos pensaron que Shark era el culpable, pero no lo era. No-no-no. Había un diente de tiburón, un talismán de Dodson, pero fue Dichoso quien lo plantó allí.\nDebió haberlo robado de Shark cuando navegaban juntos en una fragata llamada Fortuna. No dormí bien ese día y salí a dar un paseo. Vi que Dichoso se había colado en la residencia de Sharp, escuché a alguien gritar y luego gemir. Poco después, Dichoso salió de la residencia y sus manos estaban ensangrentadas.\nNo me creyeron, no-no. Porque ese día no había Dichoso en la isla, pero Shark sí. Y encontraron su diente. Pero yo vi a Dichoso, estoy seguro de ello. Nadie sabía que él estaba allí ese día. 'El Afortunado' es un hombre muy astuto y temible...";
		link.l1 = "¿No eres el primero en llamar a Dichoso 'el Afortunado'. ¿Por qué es eso? ¿Es su apodo?";
		link.l1.go = "tieyasal_8";
		break;

	case "tieyasal_8":
		dialog.text = "¿No sabes español, chico? 'Dichoso' significa 'afortunado' en el idioma papista. Miguel el Afortunado, Miguel el Dichoso. Así se llama.";
		link.l1 = "¿Miguel el Afortunado?... Hm. Eso me recuerda a algo. Hm. Esa frase me suena tan familiar...";
		link.l1.go = "tieyasal_9";
		break;

	case "tieyasal_9":
		dialog.text = "Bueno, aunque su apellido es Dichoso, todavía no creo que sea español. No, no. No es español. Aunque parece un español.";
		link.l1 = "¿Entonces qué podría ser? ¿Inglés, francés?";
		link.l1.go = "tieyasal_10";
		break;

	case "tieyasal_10":
		dialog.text = "De eso no estoy hablando, Marinero... Oh, perdóname, Capitán. Sí, Dichoso parlotea en francés de manera fabulosa, no peor que tú. Y en inglés también. Sin embargo, por sus venas corre sangre india. He visto a muchas personas así en mi vida. No se nota a simple vista, pero es un mestizo. Te lo garantizo.";
		link.l1 = "¿Habla indio?";
		link.l1.go = "tieyasal_11";
		break;

	case "tieyasal_11":
		dialog.text = "Oh, el demonio lo sabe. Tal vez lo haga. Aunque, espera. ¡Sí lo hace! Solía pronunciar constantemente frases extrañas en algún idioma bizarro y hacía una cara de sabio aterradora y inflaba sus mejillas mientras las pronunciaba. Por ejemplo, decía algo como: cogito ergo sum! Y luego ponía los ojos en blanco y buscaba la reacción de los marineros. O exclamaba así: aut Caesar, aut nihil! También soltaba muchas otras cosas. No recuerdo todo lo que solía decir.";
		link.l1 = "Eso no es idioma indio. Eso es latín. Latín... ¿Latín?! ¡Maldita sea!";
		link.l1.go = "tieyasal_12";
		break;

	case "tieyasal_12":
		dialog.text = "¿Por qué tan nervioso, muchacho? ¿Por qué gritas? ¿Te ha mordido una serpiente o algo así? ¿A dónde se fue?";
		link.l1 = "¡Por qué no lo vi desde el principio! ¡Todo estaba mirándome directamente a la cara! ¡Latín! ¡Miguel... Miguel el Afortunado!";
		link.l1.go = "tieyasal_13";
		break;

	case "tieyasal_13":
		dialog.text = "Hola, compadre. ¿Podrías dejar de gritar ya? La gente nos está mirando. ¿Qué te pasa, Marinero... perdón Capitán?";
		link.l1 = "¡Sé quién es realmente Miguel Dichoso! ¡No es español, es francés! ¡Oh, estuve tan ciego!";
		link.l1.go = "tieyasal_14";
		break;

	case "tieyasal_14":
		dialog.text = "¡No, no, tonto! No es francés. Es un mestizo. Su padre blanco se juntó con una niñita india, una de esas arawaks o miskitos del Caribe o incluso una itzá, y así llegó al mundo el Santo Miguel Dichoso. Tú no lo ves, pero yo sí. Está escrito en sus ojos...";
		link.l1 = "Dejemos de lado la cuestión de su origen por un momento. ¿Dónde está, Abraham?! ¿Estuvo aquí?!";
		link.l1.go = "tieyasal_15";
		break;

	case "tieyasal_15":
		dialog.text = "Ch-ch... Sí, estuvo aquí. Pero se fue. Ya no está en Isla Tesoro.";
		link.l1 = "¿Para qué ha venido aquí? ¿Qué tipo de barco tiene?";
		link.l1.go = "tieyasal_16";
		break;

	case "tieyasal_16":
		dialog.text = "Su barco es un galeón. Un gran galeón de guerra. ¿Para qué vino aquí...? Bueno, anduvo husmeando haciendo preguntas. Pero escuché sus conversaciones, ¡sí, sí! Estaba buscando a un tal Charles de Maure. Sí, eso es. Charles de Maure. Espera, ¡eres tú, Charles de Maure! Te estaba buscando a ti, compañero.";
		link.l1 = "¿Sabes para qué?";
		link.l1.go = "tieyasal_17";
		break;

	case "tieyasal_17":
		dialog.text = "Bueno, definitivamente no para visitar la taberna y sorber un poco de ron contigo. Estaba incitándote a capturarte. ¡Sí, sí! ¡Capturarte! ¡Estás en un gran lío, capitán!";
		link.l1 = "No lo dudo...";
		link.l1.go = "tieyasal_18";
		break;

	case "tieyasal_18":
		dialog.text = "¿Y tú? ¿Por qué lo buscas? ¡Ah, ya entiendo, ya entiendo: para matarlo! ¡Mátalo, mátalo, al bastardo! ¡Venga a Blaze Sharp! Blaze era un tipo fenomenal. Lo recuerdo, incluso de niño era igual que Nicholas.";
		link.l1 = "¿A dónde se fue Dichoso?";
		link.l1.go = "tieyasal_19";
		break;

	case "tieyasal_19":
		dialog.text = "Se dirigía a Blueweld. Dijo que a Charles de Maure deben buscarlo bajo el ala de Forest Devil. Pero dejó a su gente aquí... Espera. ¡Creo que ya te han notado!";
		link.l1 = "¿Quién me ha notado?";
		link.l1.go = "tieyasal_20";
		break;

	case "tieyasal_20":
		dialog.text = "Los hombres de Dichoso. Ha ordenado vigilarte aquí. ¡Oh, lo sé, lo sé! Mantente alerta, capitán: los arrecifes de Isla Tesoro están rodeados de barcos y están esperando allí por tu cabeza. El capitán es astuto como un zorro. No te dejes engañar.";
		link.l1 = "Lo intentaré...";
		link.l1.go = "tieyasal_21";
		break;

	case "tieyasal_21":
		dialog.text = "Y una cosa más: aquí, toma mi espada de caballería. Tómala, tómala. La necesitarás. Esta es la espada del mismo Capitán Barbarigo. Es una hoja excelente. La mejor del archipiélago. No seas tímido, tómala. ¡La Muerte Afilada será vengada!";
		link.l1 = "Gracias, Abraham.";
		link.l1.go = "tieyasal_22";
		break;

	case "tieyasal_22":
		RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		RemoveItems(npchar, "blade_29", 1);
		sTemp = GetBestGeneratedItem("blade_29");
		GiveItem2Character(pchar, sTemp);
		sld = ItemsFromID(sTemp);
		sld.Balance = 2.0;
		GiveItem2Character(npchar, "blade_19");
		EquipCharacterbyItem(npchar, "blade_19");
		Log_Info("Has recibido la espada de Barbarigo");
		PlaySound("interface\important_item.wav");
		dialog.text = "Vete ahora. Vete, te están vigilando. Haz que parezca que eres listo. O tonto. No importa. ¡Solo ten cuidado!";
		link.l1 = "Gracias, amigo. Ni siquiera sabes cuánto me has ayudado. ¡Buena suerte!";
		link.l1.go = "tieyasal_23";
		break;

	case "tieyasal_23":
		DialogExit();
		pchar.questTemp.Tieyasal.MigelKnow = "true";
		AddQuestRecord("Tieyasal", "4");
		pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
		pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
		pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
		pchar.questTemp.Tieyasal = "islatesoro";
		break;

	case "fight":
		iTemp = 20 - sti(GetCharacterItem(npchar, "potion2"));
		TakeNItems(npchar, "potion2", iTemp);
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		LAi_group_Attack(NPChar, Pchar);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
