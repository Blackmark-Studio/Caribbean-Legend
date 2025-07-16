// Соломон Шнеур - старый еврей
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
//--------------------------------------за Голландию------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyFather")
				{
					dialog.text = "¿Qué quieres de este viejo judío, joven?";
					link.l1 = "Salomón, necesito que pienses bien y recuerdes la isla perdida en la que naufragaste. Escondiste un alijo allí. He hablado con tu hija. Mi jefe Lucas Rodenburg me dio carta blanca para actuar por el bien de tu familia. Como lo veo, lo más importante para ti en este momento es recuperar el capital de tu familia, y no podrás oler ese oro sin mi ayuda.";
					link.l1.go = "SolomonBonanza";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "¡Oh, mi joven, eres tú? ¿No puedes decirme nada bueno? ¿Acaso los cristianos están aquí para atormentar a este pobre viejo judío con preguntas otra vez?";
					if (CheckCharacterItem(pchar, "SkullAztec"))
					{
						link.l1 = "He encontrado la isla, aunque fue bastante difícil. También he encontrado tu cofre con el dinero y esta calavera. Supongo que esta es la calavera de tu abuelo-patriarca, lo que sea de lo que hablabas.";
						link.l1.go = "SolomonBonanza_2";
					}
					link.l2 = "He encontrado la isla, aunque no fue tarea fácil. También he encontrado tu cofre con el dinero. Pero no había calaveras en ese cofre.";
					link.l2.go = "SolomonBonanza_3";
					link.l3 = "No, no tengo preguntas en este momento.";
					link.l3.go = "exit";
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "GiveLucasMoney" && GetQuestPastDayParam("questTemp.HWIC.Holl.LucasMoney") > 7)
				{
					dialog.text = "¡Oh, mi joven, eres tú? ¿Puedes contarme algo bueno? ¿O vas a atormentar a este pobre viejo judío con preguntas de nuevo?";
					link.l1 = "He encontrado la isla, aunque fue bastante difícil. También he encontrado tu cofre con el dinero. Aquí lo tienes.";
					link.l1.go = "SolomonBonanza_5";
					break;
				}
				dialog.text = "Hola, joven. ¿Qué quieres de este pobre viejo judío?";
				link.l1 = "Buenas tardes. No, nada, solo he venido a saludar.";
				link.l1.go = "exit";
				break;
			}
//----------------------------------------за Англию-----------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "toAbigile")
				{
					dialog.text = "Buenas tardes, joven. Veo que has venido con un propósito... ¿Qué deseas? ¿Ganaré algo con esto o me he perdido de algo?";
					link.l1 = "Buenas tardes, Salomón. Me gustaría hablar con Abigail.";
					link.l1.go = "Solomon_treasure";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Hola, joven. ¿Qué deseas de este pobre viejo judío?";
				link.l1 = "Buenas tardes, Solomon. Nada, solo he venido a saludar.";
				link.l1.go = "exit";
				break;
			}
//-----------------------------------------против всех-------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "Buenas tardes, joven. Veo que has venido con un propósito... ¿Qué deseas? ¿Estoy sacando algo de esto o me perdí de algo?";
					link.l1 = "Tengo que hablar con Abigail. Tengo una carta para ella.";
					link.l1.go = "Abigile_kidnap";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDayOver")
				{
					dialog.text = "Hola joven. ¿Qué quieres? ¿Otra carta para mi hija?";
					link.l1 = "No. ¿Dónde está Abigail?";
					link.l1.go = "Abigile_GoOver";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistory")
				{
					dialog.text = "Eh... ¿Estás hablando de mi dinero, joven?";
					link.l1 = "Sí, señor. Sobre el dinero que escondió en alguna isla. ¿Es cierto que usted y Abigail no pueden recordar su ubicación?";
					link.l1.go = "Solomon_history";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryAfter")
				{
					dialog.text = "Está bien. Recuerdo el fluyt y a su capitán. Incluso lo había visto una vez antes en Ámsterdam. El fluyt se llamaba 'Leiden' y el capitán se llamaba Toff Keller.";
					link.l1 = "¡Eso es un comienzo! Ahora tengo una pista.";
					link.l1.go = "Solomon_history_3";
					pchar.questTemp.HWIC.Self = "SolomonHistoryEnd";
					break;
				}
				dialog.text = "¡Ay, ay, ay! ¿Qué quieres de este pobre viejo judío esta vez?";
				link.l1 = "Buenas tardes. No, nada, solo he venido a saludar.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "¡Ay, ay, ay, ¿qué quiere de este pobre viejo judío esta vez?";
			link.l1 = "Buenas tardes. No, nada, solo he venido a saludar.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-----------------------------------------------За Голландию-----------------------------------
		case "SolomonBonanza":
			PlaySound("Voice\Spanish\hambit\Solomon Shneur-03.wav");
			dialog.text = "¿Y qué quieres de mí? ¿Acaso parezco un hombre que sabe algo? ¿Cómo podría saber en un día tan olvidado por Dios exactamente dónde había una parcela de tierra con bienes y oro listo para ser tomado? ¡Imagínate cómo cualquiera de los gentiles por ahí caminando por las calles quiere engañar a un judío como yo y quitarme mi dinero!\nHay una isla. No hay un solo hombre allí, excepto Abi y yo. Ninguno. Nadie en absoluto. Había una gruta en el medio de ella. Puse mi cofre allí para salvarlo de ese pirata goyim Amalec. ¡Un cofre lleno de oro, ni un chisme entre él! ¡Lo arrastré todo el camino desde el Viejo País! Todo lo que había ganado con el sudor de mi frente está allí. Además, el cráneo de mi abuelo... Créeme, esa cosa nos salvó, sí-sí\n¡Oh-ho-ho, es un talismán antiguo cargado con magia talmúdica! ¡Dios nos salve de Amalec! ¡Oy vey, es difícil empezar de nuevo en esta era de los gentiles! ¡Ojalá lo supieras, joven! ¡Oh, ojalá lo supieras!";
			link.l1 = "¿De qué demonios estás balbuceando, lunático? No importa. Lo resolveré por mi cuenta. ¡Adiós!";
			link.l1.go = "SolomonBonanza_1";
		break;
		
		case "SolomonBonanza_1":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbySeekIsland";
			pchar.quest.Joakim_meeteng.win_condition.l1 = "location";
			pchar.quest.Joakim_meeteng.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Joakim_meeteng.function = "Create_Joakim";
		break;
		
		case "SolomonBonanza_2"://отдаем всё
			dialog.text = "¡Oy, hay un Dios y eres un verdadero mensch! ¡Has recuperado no solo mi oro, sino que también has redimido el nombre de Shneur! ¡Qué shande has prevenido! Mynheer Rodenburg puede estar legítimamente orgulloso de tener capitanes como tú bajo su mando. Le daré el cráneo a mynheer Rodenburg, prometió pagar una suma significativa por él. Me gustaría agradecerte personalmente, eres un buen shabbos goy - por favor, acepta este amuleto como una pequeña muestra de gratitud de este judío.";
			link.l1 = "Uh, gracias, supongo.";
			link.l1.go = "SolomonBonanza_4";
			RemoveItems(PChar, "SkullAztec", 1);
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			AddDialogExitQuestFunction("DeleteJoakimFromRoom");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Joakim"));
			pchar.questTemp.Caleuche.SolomonSkul = true;
		break;
		
		case "SolomonBonanza_3":
			dialog.text = "¡Oye, hay un Dios y tú eres un verdadero mensch! ¡Has traído de vuelta no solo mi oro, sino que también has redimido el nombre de Shneur! ¡Qué vergüenza has prevenido! En cuanto al cráneo, bueno, no importa, ¡de todas formas era un meshuggeneh schmuck! Mynheer Rodenburg puede estar justamente orgulloso de tener capitanes como tú bajo su mando. Me gustaría agradecerte personalmente, eres un buen shabbos goy - por favor, acepta este amuleto como recuerdo.";
			link.l1 = "Eh, gracias, supongo.";
			link.l1.go = "SolomonBonanza_4";
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "obereg_10");
			pchar.questTemp.HWIC.Holl.ScullnotReturn = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			DelLandQuestMark(npchar);
		break;
		
		case "SolomonBonanza_4":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyLeavesMarried";//теперь можно говорить с Аби
			AddQuestRecord("Holl_Gambit", "1-32");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "SolomonBonanza_5":
			dialog.text = "¿Qué? ¿Qué dices, joven? ¿Es esto cierto? Déjame ver...";
			link.l1 = "Aquí está tu dinero. Pertenece a ti y a Abigail. Pero, ay, no he encontrado el cráneo de tu abuelo.";
			link.l1.go = "SolomonBonanza_6";
		break;
		
		case "SolomonBonanza_6":
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			dialog.text = "Oh dinero dinero dinero, maravilloso dinero... Hmm, aunque esto no parece mi dinero... No huele a mi amado lucro. Pero, después de todo, el dinero es todo igual, ¿no es así, joven? No me quejaré por eso. 'A caballo regalado no se le mira el diente', como solemos decir. Muchas gracias por devolverme mis ahorros. Me gustaría agradecerte también, por favor, acepta este amuleto. Ahora ve y dile a Abi las buenas noticias. Necesito contar esto.";
			link.l1 = "Muchas felicidades, Salomón.";
			link.l1.go = "SolomonBonanza_4";
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

//-------------------------------------------за Англию------------------------------------------------
		
		case "Solomon_treasure":
			dialog.text = "¡Oy vey, cuidao contigo! Mynheer Rodenburg está a un paso de ser mi yerno goy. ¡Todos los soldados de la guarnición estarán aquí en un santiamén si pido ayuda!";
			link.l1 = "¿Quién carajo eres tú?";
			link.l1.go = "Solomon_treasure_1";
		break;
		
		case "Solomon_treasure_1":
			dialog.text = "Escúchame, capitán. Soy su padre Salomón. Haz lo correcto, tráeme mis monedas perdidas y la calavera de jade de su bisabuelo. Este viejo judío puede que no sea tan astuto como tú, pero incluso él sabe que quieres algo de su hija. \nTal vez te haya enviado alguien, algún capitán que me conoce, le contaré todo a Abi, no te preocupes. Ella no está en casa ahora, está rezando por las almas de los pecadores gentiles como tú.";
			link.l1 = "Eso apenas tiene sentido...Joder, eres un verdadero pedazo de obra. Adiós, viejo tacaño.";
			link.l1.go = "Solomon_treasure_2";
		break;
		
		case "Solomon_treasure_2":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-17");
			pchar.questTemp.HWIC.Eng = "AbigileInChurch";
			sld = characterFromId("Abigile");
			sld.greeting = "abigile_3";
			ChangeCharacterAddressGroup(sld, "Villemstad_church", "goto", "goto1");//Аби в церковь
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
//----------------------------------------------против всех---------------------------------------------	
		
		case "Abigile_kidnap":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Villemstad");
			dialog.text = "¿Una carta? ¡No me digas! Escucha aquí, goy, Mynheer Rodenburg está a un paso de ser mi yerno. Puedes mover tu tuchis de aquí porque él me gusta.";
			link.l1 = "Escuche, me importa un bledo quién sea su yerno. Estoy obligado a entregar esta carta a Abigail. ¿Sabe dónde puedo encontrarla? ¿Y quién diablos es usted?";
			link.l1.go = "Abigile_kidnap_1";
		break;
		
		case "Abigile_kidnap_1":
			dialog.text = "¿Quién soy yo? Soy su padre Salomón... Y no me gustas, goy.";
			link.l1 = "Me preocuparía más si dijeras que te gusto. ¿Vas a seguir tratándome condescendientemente o vas a buscar a Abigail? ¡Te lo repito, soy un mensajero! ¡Tengo una carta para tu hija!";
			link.l1.go = "Abigile_kidnap_2";
		break;
		
		case "Abigile_kidnap_2":
			dialog.text = "Dame esta carta. Se la entregaré a mi hija.";
			link.l1 = "Te afeitaré los rizos y te retorceré la nariz antes de entregarte esta carta. Tengo órdenes de entregar este mensaje personalmente a ella. No me dijeron una palabra sobre su padre y no me importa en absoluto. ¿Dónde puedo encontrar a Abigail?";
			link.l1.go = "Abigile_kidnap_3";
		break;
		
		case "Abigile_kidnap_3":
			dialog.text = "Tan pronto como grite, joven goy, todos los soldados de la ciudad estarán aquí de inmediato. No seas tan terco, puedes ver que tengo todas las cartas.";
			link.l1 = "¡Jesús, María y José! ¿De verdad? ¿Y luego qué? ¿Esperas que me pongan grilletes por entregar una carta? ¡No seas ridículo!";
			link.l1.go = "Abigile_kidnap_4";
		break;
		
		case "Abigile_kidnap_4":
			DialogExit();
			sld = characterFromId("Abigile");
			ChangeCharacterAddressGroup(sld, "Villemstad_houseSP2", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_GoOver":
			dialog.text = "¿Estás meshuggeneh? Has emocionado a mi pobre hija hasta la muerte con tu carta... ¡Decidió ir tras ese capitán inglés patán! ¡Zarpó en el primer barco disponible! ¡Oy veyy, mi pobre hija! ¿Qué hará ahora este viejo judío? ¡Mi vida está arruinada! ¡Es una vergüenza! Déjame en mi miseria, o quédate y regocíjate, ¡no me importa! ¡Ohhh mi pobre Abigail! ¡Has llevado la cabeza gris de tu padre al Sheol en la desesperación!";
			link.l1 = "¡Bueno, qué tal eso! Supongo que ella no pudo esperar un momento más. ¡Adiós, Salomón!";
			link.l1.go = "Abigile_GoOver_1";
		break;
		
		case "Abigile_GoOver_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-69");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
		break;
		
		case "Solomon_history":
			PlaySound("Voice\Spanish\hambit\Solomon Shneur-03.wav");
			dialog.text = "¿Cómo se ve? Es solo una isla sin gente, solo yo y Abigail. Allí escondí mi cofre, para evitar que ese pirata goy Amalek lo tome. Todo lo que había ganado honestamente con el sudor de mi frente está en ese cofre...";
			link.l1 = "Dime, Salomón, ¿acaso podrías recordar el nombre del fluyt del que hablaba tu hija? ¿Y cómo se llamaba su capitán?";
			link.l1.go = "Solomon_history_1";
		break;
		
		case "Solomon_history_1":
			dialog.text = "Hmm... Bueno, no lo sé. ¡La cabeza de este pobre viejo judío está revuelta como una sartén de gefilte fish! ¿Y por qué preguntas, joven?";
			link.l1 = "Solo quiero ayudar a tu hija, Solomon. No puedo prometer nada, pero me gustaría intentarlo. Mi antiguo jefe la trató mal, y después de eso creo que estoy obligado a ayudarla a establecerse de alguna manera.";
			link.l1.go = "Solomon_history_2";
		break;
		
		case "Solomon_history_2":
			dialog.text = "Vaya, bueno si ese es el caso...";
			link.l1 = "";
			link.l1.go = "Solomon_history_3";
			pchar.questTemp.HWIC.Self = "SolomonHistoryNext";
		break;
		
		case "Solomon_history_3":
			DialogExit();
			sld = characterFromId("Abigile");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Solomon_thanks":
			dialog.text = "¡Joven! ¡Espera!";
			link.l1 = "¿Sí?";
			link.l1.go = "Solomon_thanks_1";
		break;
		
		case "Solomon_thanks_1":
			dialog.text = "¡Joven mensch! Quisiera agradecerte por todo lo que has hecho por mí y mi hija. Nos salvaste. Lamento haberte recibido de manera hostil la primera vez que nos encontramos y por mis dudas sobre tu sincero deseo de ayudar. Por favor, perdona a este viejo judío. Realmente eres un hombre bendito entre los gentiles. Ahora dime, ¿no has encontrado nada más aparte de mi dinero en la gruta?";
			link.l1 = "No, Solomon. No había nada más que dinero. Tuve que luchar contra los asesinos de van Berg - fue él quien hundió tu barco hace meses. Podría ser que ya hubieran robado algo... ¿Qué más se suponía que debía estar allí?";
			link.l1.go = "Solomon_thanks_2";
		break;
		
		case "Solomon_thanks_2":
			dialog.text = "Oh, nada importante... Una antigua reliquia de familia... Bueno, ¡no importa! ¡Olvídalo, era un imbécil de todos modos! Y... Solo una cosa más, joven... ";
			link.l1 = "Continúa.";
			link.l1.go = "Solomon_thanks_3";
		break;
		
		case "Solomon_thanks_3":
			dialog.text = "Tú... bueno, he descubierto algo sobre ti. Nuestro gobernador te tiene en alta estima, y eres un capitán notable. Te contaré un secreto... a mi hija le gustas mucho. Ella misma me lo dijo. Tal vez... pienses en esto. Abigail es una muy buena chica, te lo aseguro, mejor que cualquiera de las furcias shiksa que puedas haber encontrado en tus viajes.";
			link.l1 = "¡Ay, caray... No es tan simple, Salomón. Tu hija es realmente una joya rara. Cuídala bien!";
			link.l1.go = "Solomon_thanks_4";
		break;
		
		case "Solomon_thanks_4":
			dialog.text = "Piénsalo bien, joven. ¡Piénsalo otra vez y vuelve! ¡Nos encantaría verte de nuevo!";
			link.l1 = "Claro... adiós, Salomón.";
			link.l1.go = "Solomon_thanks_5";
		break;
		
		case "Solomon_thanks_5":
			DialogExit();
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload1", false);
			AddQuestRecord("Holl_Gambit", "3-65");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "Solomon_poor":
			dialog.text = "Oyyy... A veces es imposible empezar una nueva vida, joven. Vivir en la pobreza, ¿qué puede ser peor para un viejo tonto como yo?";
			link.l1 = "Lo siento, Salomón. Mantente firme y busca a Cristo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Solomon_poor";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Eres un "+GetSexPhrase("¡ladrón, señor! Guardias, cójanlo","¡ladrona, chica! Guardias, llévensela")+"!!!","¡Solo mira eso! Tan pronto como estaba perdido en la contemplación, ¡decidiste revisar mi cofre! ¡Atrapen al ladrón!!!","¡Guardias! ¡Robo! ¡Atrapen al ladrón!!!");
			link.l1 = "¡Maldita sea!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
