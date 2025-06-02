// Жоаким Мерриман - португальский сумрачный гений
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbySeekIsland" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "¡Buen día, señor! Soy el Doctor Joachim Merriman. ¿Tengo el placer de dirigirme al Capitán "+GetFullName(pchar)+"?";
					link.l1 = "¡Ay, ese soy yo! ¿Cómo demonios sabes mi nombre? No recuerdo haberte conocido antes.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					dialog.text = "Me alegra verte, capitán. Puedo notar por el brío en tu paso que estás a punto de hacerme muy feliz. ¿Tienes el cráneo de Yum Cimil?";
					link.l1 = "Tengo la calavera de la que hablas. Casi chisporrotea con energía, como un rugiente horno.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "¿Tiene algo más que decir, capitán?";
				link.l1 = "No, señor Merriman. Me voy...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "JoakimMeeting" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "¡Buen día, señor! Soy el Doctor Joachim Merriman. ¿Tengo el placer de dirigirme al Capitán "+GetFullName(pchar)+"?";
					link.l1 = "Sí, ese soy yo. ¿Cómo diablos sabes mi nombre? No recuerdo haberte conocido antes.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("Villemstad");
					dialog.text = "Me alegra verte, capitán. Puedo ver por el brío en tu paso que estás a punto de hacerme muy feliz. ¿Tienes el cráneo de Yum Cimil?";
					link.l1 = "Tengo la calavera de la que hablas. Crepita con energía, como un horno rugiente.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "¿Tienes algo más que añadir, capitán?";
				link.l1 = "No, Doctor Merriman. Me voy.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Buen día. ¿Quieres algo de mí?";
			link.l1 = "No, lo siento.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Landlady"://хозяйка дома
			dialog.text = "Si has venido a ver al Doctor Merriman, no está aquí. Ya no vive aquí.";
			link.l1 = "Ya veo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady";
		break;
		
		case "Landlady_1"://хозяйка дома
			dialog.text = "Si has venido a ver al Doctor Merriman, entonces debo decirte que no está en casa. Está de viaje en este momento y no sé cuándo regresará.";
			link.l1 = "Ya veo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_1";
		break;
		
		case "Landlady_2"://хозяйка дома
			dialog.text = "Si has venido a ver al Doctor Merriman, no está aquí. Ya no vive aquí.";
			link.l1 = "Ya veo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_2";
		break;
		
		case "JoakimSeekSkull":
			PlaySound("Voice\Spanish\hambit\Joakim Merriman-01.wav");
			dialog.text = "¡Tus asuntos no son tan privados como podrías creer, capitán! Pero no te alarmes, ¡tengo una proposición para ti! Soy un hombre de ciencia, una especie de filósofo natural que estudia la fascinante cultura de los paganos indios del Litoral español y las Indias Occidentales. ¿Serías tan amable de caminar conmigo hasta mi casa y discutir los detalles potencialmente muy lucrativos en mi sala de estar?";
			link.l1 = "Tienes mi curiosidad y mi atención. Lleva el camino.";
			link.l1.go = "JoakimSeekSkull_1";
		break;
		
		case "JoakimSeekSkull_1":
			dialog.text = "¡No rechace esto, señor! Mi casa no está lejos de aquí. ¡Sígame!";
			link.l1 = "... ";
			link.l1.go = "JoakimSeekSkull_2";
		break;
		
		case "JoakimSeekSkull_2":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "Villemstad_houseSp1_room", "goto", "goto1", "JoakimInRoom", -1);
		break;
		
		case "JoakimSeekSkull_3":
			PlaySound("Voice\Spanish\hambit\Joakim Merriman-01.wav");
			dialog.text = "Podemos hablar aquí sin temor a oídos curiosos. Has estado visitando recientemente a mi vecino Solomon Shneur. Estaba caminando cerca y, debes perdonarme capitán, accidentalmente escuché algunos detalles de tu conversación con Solomon. ¡Fue todo tan fascinante que tuve que escuchar toda la charla!";
			link.l1 = "Un espía que teme a otros espías, ¿eh?";
			link.l1.go = "JoakimSeekSkull_4";
		break;
		
		case "JoakimSeekSkull_4":
			dialog.text = "¡Ahora, ahora, capitán! ¡No es así en absoluto! ¡Salomón es mi vecino y a menudo me visita! ¡Somos buenos amigos a pesar de nuestras diferencias religiosas! Estoy al tanto de sus desventuras... ¡como todos los demás en Willemstad! Salomón proclama sus problemas a cualquiera que quiera escuchar mañana, tarde y noche. Pero basta de eso. El viejo judío ya debe haberte contado sobre un viejo cráneo de jade que está escondido junto con su oro en alguna isla desconocida. ¿Te habló de ello?";
			link.l1 = "Me habló de una calavera, no mencionó que estuviera hecha de jade. También dijo que era la calavera de su abuelo, para decir la verdad, pensé que era o bien algún horror cabalístico o que el viejo chiflado tenía murciélagos en el campanario.";
			link.l1.go = "JoakimSeekSkull_5";
		break;
		
		case "JoakimSeekSkull_5":
			dialog.text = "No, capitán, Salomón está bastante cuerdo, solo un poco excéntrico. El cráneo sí existe. Es un antiguo tesoro indio, ¡el cráneo de jade de Yum Cimil! No tengo idea de cómo el viejo judío consiguió ponerle las garras encima. He estado buscándolo durante la mitad de mi vida. Busca esa isla donde Salomón escondió el dinero de su familia. El cráneo debe estar allí en su cofre. Tráeme ese cráneo de jade y te pagaré medio millón de pesos.";
			link.l1 = "¿Medio millar? Eso apenas vale mi tiempo... espera un momento... ¿dijiste medio millón de piezas de a ocho? ¿Me estás tomando el pelo? ¡Nunca he visto tanto dinero junto en un solo lugar en mi vida!";
			link.l1.go = "JoakimSeekSkull_6";
		break;
		
		case "JoakimSeekSkull_6":
			dialog.text = "Sigues siendo un joven capitán... ¿Entonces, estás dentro? Me das la calavera de jade y yo te daré quinientos mil piezas de a ocho a cambio. ¿Trato hecho?";
			link.l1 = "Ja, ¿una fortuna por una calavera vieja? Por supuesto que estoy dentro.";
			link.l1.go = "JoakimSeekSkull_7";
		break;
		
		case "JoakimSeekSkull_7":
			dialog.text = "Espléndido. Siempre es un placer trabajar con un hombre que entiende el beneficio. Puedes encontrarme aquí en mi casa si me necesitas más. ¡Buena suerte!";
			link.l1 = "Gracias, Doctor Merriman. No te haré esperar mucho tiempo.";
			link.l1.go = "exit";
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			AddDialogExitQuestFunction("CheckIslandCoordinates");//вот тут-то мы и проверим, есть ли у нас координаты острова, и далее будем исходить из результата.
		break;
		
		case "JoakimFindSkull":
			PlaySound("Voice\Spanish\hambit\Joakim Merriman-02.wav");
			dialog.text = "¡Oh, sí! Definitivamente tienes razón sobre su poder... Pero basta de palabras, déjame verlo, estoy temblando de impaciencia.";
			link.l1 = "Aquí, por favor, tómalo. ¿Espero no haberme equivocado?";
			link.l1.go = "JoakimFindSkull_1";
			DelLandQuestMark(npchar);
		break;
		
		case "JoakimFindSkull_1":
			RemoveItems(PChar, "SkullAztec", 1);
			dialog.text = "¡Ah, increíble! Sí, esto es. ¡Excelente, capitán, muy excelente! ¡Por fin! Lo tengo conmigo, ¡por fin! He estado esperando este momento durante tantos años.";
			link.l1 = "¿Qué pasa con el dinero que prometiste, Doctor Merriman?";
			link.l1.go = "JoakimFindSkull_2";
		break;
		
		case "JoakimFindSkull_2":
			AddMoneyToCharacter(pchar, 500000);
			dialog.text = "¡Oh, sí, por supuesto! Medio millón de piezas de a ocho. Tómalas, te las has ganado.";
			link.l1 = "Un placer hacer negocios contigo. Es difícil creer que algo tan pequeño pueda valer tanto...";
			link.l1.go = "JoakimFindSkull_3";
		break;
		
		case "JoakimFindSkull_3":
			dialog.text = "¿Cosa pequeña? No sabes de lo que hablas. Esto es... bah, tu mente filistea apenas puede comprender la magnitud del increíble poder detrás de este precioso cráneo. A decir verdad, no tengo tiempo que perder de todos modos\nGracias, capitán, por lo que has hecho. Ahora es momento de despedirnos. Debo irme.";
			link.l1 = "Adiós, Doctor Merriman. Tal vez nos volvamos a encontrar.";
			link.l1.go = "JoakimFindSkull_4";
		break;
		
		case "JoakimFindSkull_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Landlady");
			sld.Dialog.Filename = "Quest\HollandGambit\Joakim.c";
			sld.dialog.currentnode = "Landlady_2";
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
		break;
		
		case "JoakimSeekSkull_8":
			PlaySound("Voice\Spanish\hambit\Joakim Merriman-01.wav");
			DelLandQuestMark(npchar);
			dialog.text = "Podemos hablar aquí, capitán. Sé que eres un íntimo asociado de Abigail Shneur, la hija de mi vecino Salomón. Ella ha zarpado en tu barco hacia su amante... pero eso realmente no importa.";
			link.l1 = "¿Qué insinúas, Doctor?";
			link.l1.go = "JoakimSeekSkull_9";
		break;
		
		case "JoakimSeekSkull_9":
			dialog.text = "Si conoces a Salomón, entonces debes conocer su historia del naufragio y sus tesoros perdidos que ha escondido en alguna isla desconocida. Ya ha contado esta historia a todos en Willemstad.";
			link.l1 = "¿Por qué supones que he oído algo al respecto y me importan las desgracias del viejo judío?";
			link.l1.go = "JoakimSeekSkull_10";
		break;
		
		case "JoakimSeekSkull_10":
			dialog.text = "¿No te gusta Salomón? Te aseguro que es solo un viejo excéntrico inofensivo. Olvídate de él. Hablemos de negocios\nTuve varias largas conversaciones con Salomón. ¡No puedes imaginar cómo me sentí cuando descubrí que este viejo judío es dueño de un antiguo artefacto invaluable que he estado buscando durante años! El viejo loco lo escondió junto con su patético dinero en alguna isla y ni siquiera puede recordar su ubicación\nNecesito este artefacto. Tráemelo y te pagaré medio millón de piezas de a ocho.";
			link.l1 = "¿Medio millón de piezas de a ocho? Debes estar bromeando, doctor. ¡Nunca he visto todo ese dinero junto en un solo lugar en mi vida!";
			link.l1.go = "JoakimSeekSkull_11";
		break;
		
		case "JoakimSeekSkull_11":
			dialog.text = "Aún eres un hombre joven. ¿Entonces, estás dentro? Me das la calavera y yo te daré quinientos mil piezas de a ocho a cambio. Además, puedes llevarte el dinero de Salomón también. Según las palabras del viejo, deben ser unos doscientos mil pesos... Así que setecientas mil piezas de a ocho en total para ti. ¿Trato, capitán?";
			link.l1 = "¡Que me parta un rayo! ¡Por supuesto que es un trato! Pero, ¿cómo se supone que debo encontrar esta isla?";
			link.l1.go = "JoakimSeekSkull_12";
		break;
		
		case "JoakimSeekSkull_12":
			dialog.text = "Habla con Abigail. Tal vez recuerde algo. Pregunta a Solomon. Mira, si yo supiera dónde encontrar la isla, no habría pedido tu ayuda en primer lugar.";
			link.l1 = "Ya veo. Perdona por mi pregunta estúpida. Ahora a encontrar esta isla. Solo asegúrate de estar esperando con mi pago.";
			link.l1.go = "JoakimSeekSkull_13";
		break;
		
		case "JoakimSeekSkull_13":
			dialog.text = "Exactamente. Me alegra que nos entendamos, capitán. Buena suerte con su búsqueda. Siempre puede encontrarme aquí en mi casa.";
			link.l1 = "¡No te haré esperar mucho, Doctor Merriman. ¡Adiós!";
			link.l1.go = "JoakimSeekSkull_14";
		break;
		
		case "JoakimSeekSkull_14":
			DialogExit();
			pchar.questTemp.HWIC.Self = "SeekAbiIsland";
			AddQuestRecord("Holl_Gambit", "3-55");
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", true);//закроем комнату Аби
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "First time";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		// калеуче
		case "caleuche":
			PlaySound("Voice\Spanish\LSC\Chymiset-05.wav");
			dialog.text = "Síííí. ¡Las piedras sacrificiales corren rojas con la sangre de mis enemigos! ¡Yum Cimil me ha concedido su poder para comandar a los muertos! ¡Con este poder pronto gobernaré a los vivos!";
			link.l1 = "Muy melodramático, Merriman. ¿Qué planeas hacer con tu ejército de cadáveres ambulantes? ¿Estás jugando a ser César, tratando de conquistar el mundo?";
			link.l1.go = "caleuche_1";
			CreateLocationParticles("large_smoke", "goto", "goto37", 0.5, 0, 0, "");
		break;
		
		case "caleuche_1":
			dialog.text = "¡Silencio, imbécil! ¿Esperas que revele mi plan secreto en un monólogo? Bueno, no veo razón para no hacerlo, ¡no vas a sobrevivir a este encuentro! Mis legiones de no-muertos primero ocuparán todas las cuevas oscuras y mazmorras del Caribe. Mis puestos avanzados estarán ubicados en cada aldea, esperando mi señal. Y cuando llegue el momento, mis cadáveres andantes saldrán y cubrirán las tierras de los vivos.\n¡Lástima que no vivirás para verlo, patético tonto bienintencionado, aspirante a protagonista! ¡Has entrado en mi santuario, y no saldrás vivo de él! ¡Lideraré mi ejército de la oscuridad!";
			link.l1 = "Escucha, colega, no estás liderando nada excepto a Jack y a mierda, y Jack acaba de irse del pueblo.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			PlaySound("Types\Spanish\warrior07.wav");
			dialog.text = "¡Oh ho ho! ¿Te atreverías a desafiarme a mí y a mis sirvientes esqueléticos? ¡Entonces contempla lo que realmente soy y tiembla de miedo!";
			link.l1 = "Ven a por algo.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			npchar.model = "Meriman_2";
			Characters_RefreshModel(npchar);
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			dialog.text = "";
			link.l1 = "¡Ahhh! ¡Dulce Jesús!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			PlaySound("Voice\Spanish\hambit\Joakim Merriman-04.wav");
			dialog.text = "¿Ahora entiendes quién está delante de ti, gusano gimoteante? ¡Tengo cuentas pendientes contigo! ¡El mismo Yum Cimil me favorece! Me comeré tu higado, ya verás.";
			link.l1 = "Está bien, cabeza hueca. Vamos a bailar.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto37", "none", "", "", "Caleuche_MerrimanTeleport", -1);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto37");
			pchar.questTemp.Caleuche.Merriman_hide = "true";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Eres un "+GetSexPhrase("¡Ladrón, señor! Guardias, agárrenlo","¡ladrona, chica! Guardias, llévensela")+"!!!","¡Mira nada más! Tan pronto como di la espalda, decidiste revisar mi cofre. ¡Atrapen al ladrón!","¡Guardias! ¡Robo! ¡Atrapen al ladrón!!!");
			link.l1 = "¡Maldita sea!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
