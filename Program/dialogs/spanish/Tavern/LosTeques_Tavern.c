#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	bool bLock = (CheckAttribute(pchar, "GenQuest.BrothelLock")) && (GetCharacterIndex("Mary") != -1);
	bool bLock1 = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) && (IsOfficer(characterFromId("Helena")));

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("¡Ha habido una alarma en el pueblo! ¡Todos te están buscando! Yo no me quedaría aquí mucho tiempo si fuera tú.","¡Toda la guardia está peinando el pueblo tratando de encontrarte! ¡No soy un idiota y no pienso hablar contigo!","Corre, camarada, antes de que los soldados te hagan picadillo..."),LinkRandPhrase("¿Qué necesitas, granuja? ¡La guardia de la ciudad ya está tras de ti. No llegarás lejos, pirata!","¡Asesino sucio, sal de mi casa! ¡Guardias!","¡No te tengo miedo, perro! La soga te llama, no llegarás lejos..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, no me preocupa la alarma...","No tienen ninguna oportunidad de atraparme."),RandPhraseSimple("Cierra la boca, "+GetWorkTypeOfMan(npchar,"")+", o te cortaré la maldita lengua.","Heh, "+GetWorkTypeOfMan(npchar,"")+", ¿tú también quieres cazar a un pirata? Escucha, camarada, mantén la calma y podrías vivir..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+". Bienvenido, "+GetAddress_Form(NPChar)+" a la taberna de la mina Los-Teques. ¡Comida, bebidas y chicas, todo a precios asequibles! Mi nombre es "+GetFullName(npchar)+" y siempre estoy a su servicio.";
				Link.l1 = "Ya veremos... Soy "+GetFullName(pchar)+". Encantado de conocerte, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "¡Ajá, es mi viejo conocido, capitán "+GetFullName(pchar)+". Me alegra verte, viejo. ¿Algo de beber?";
				if (makeint(pchar.money) >= 5)
				{
					link.l1 = "Sírveme un poco de ron, "+npchar.name+".";
					link.l1.go = "drink";
				}
				link.l2 = "Me gustaría echar una cabezada. ¿Tienes una habitación libre?";
				link.l2.go = "room";
				link.l3 = LinkRandPhrase("¿Tienes alguna noticia reciente?","¿Qué hay de nuevo por estos lares?","¿Cómo va la vida en tierra firme?");
				link.l3.go = "rumours_tavern";
				link.l4 = "No, no necesito nada, "+npchar.name+" . Solo pasé para saludarte.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "¡Oh, estoy tan feliz! Las caras nuevas son una rareza en nuestro asentamiento. ¿Qué tal si te sirvo un poco de ron y charlamos...?";
			link.l1 = "Esta es mi primera vez aquí, y me gustaría saber un poco más sobre este asentamiento.";
			link.l1.go = "info";
			if (makeint(pchar.money) >= 5)
			{
				link.l2 = "Sírveme algo de ron, "+npchar.name+".";
				link.l2.go = "drink";
			}
			link.l3 = "Me gustaría descansar un poco. ¿Tienes una habitación libre?";
			link.l3.go = "room";
		break;
		
		case "info":
			dialog.text = "Nada interesante que contar. El mismo negocio todos los días: aburrimiento, sol y polvo. Solo soldados, negros e indios viven aquí. También puedes encontrar algunos aventureros y bandidos hambrientos de oro.\nA veces caballeros, capitanes como tú, nos visitan para vender esclavos por lingotes y comprar metales preciosos. Nuestro comerciante es un hombre bastante interesante, no solo vende pepitas de oro y plata, sino también gemas semipreciosas.\n Afirma que las personas con conocimientos especiales pueden encontrar estas piedrecitas muy útiles. Así que revisa nuestra tienda. La mina en sí está ubicada más allá de la montaña. Puedes visitarla si lo deseas, pero te recomiendo evitar enfadar a la guardia.\nNo hables con los convictos, y que Dios te salve de robar. De todos modos, el mejor lugar en este asentamiento es mi taberna, ¡el mejor lugar para descansar de este infierno ardiente!";
			link.l1 = "¡Gracias por la información!";			
			link.l1.go = "exit";
		break;
		
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 3)
			{
				dialog.text = "Capitán, creo que sería mejor que te detuvieras. Dios no lo quiera, que causes un infierno mientras estás bajo la influencia del alcohol. Somos muy estrictos con eso aquí. Ni siquiera tu autoridad te ayudará.";
				link.l1 = "Mm... Supongo que tienes razón, ya he tenido suficiente. ¡Gracias por la preocupación!";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -5);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "De nada, capitán. ¡Solo cinco piezas de a ocho por una pinta de mi mejor ron negro jamaicano!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("¡Muy bien, a tu salud y a la prosperidad de tu establecimiento, camarada!","¡De acuerdo, a los del mar!","¡Muy bien, por el bienestar de tu pueblo!"),LinkRandPhrase("¡Muy bien, a los vientos de la producción, a una ráfaga de suerte, que todos vivamos más despreocupados y prósperos!","¡Muy bien, que el viento siempre sople a nuestras espaldas en todos los asuntos!","¡Bien, por la felicidad, la suerte, la alegría y las mozas!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
		break;
		
		case "room":
			if (CheckAttribute(pchar, "GenQuest.LosTequesSex"))
			{
				dialog.text = "Señor, has pagado por una habitación y una chica. Sube arriba, te ha estado esperando por un buen rato.";
				link.l1 = "Está bien.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Sí, tenemos. ¿Cuánto tiempo planeabas quedarte?";
			if(!isDay())
			{
				link.l1 = "Hasta la mañana.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Hasta la noche.";
				link.l1.go = "room_night";
				link.l2 = "Hasta la próxima mañana.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "Eso serán diez piezas de a ocho. ¿Te gustaría una chica para la habitación junto con eso? Sólo mil pesos por la moza.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "No, no necesito una chica. Aquí, toma esto por la habitación.";
				link.l1.go = "room_day_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Sí, tomaré la habitación y la chica. Aquí está el dinero.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "¡Ay, no puedo permitirme la habitación!";
			link.l3.go = "exit";
		break;

		case "room_day_next":
			dialog.text = "Serán diez piezas de a ocho. ¿Quieres una chica para la habitación también? Solo mil pesos por la moza.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "No, no necesito una chica. Aquí, toma esto por la habitación.";
				link.l1.go = "room_day_wait_next";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Bien. Tomemos la habitación y la chica. Aquí está el dinero.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "¡Ay, no puedo pagar la habitación!";
			link.l3.go = "exit";
		break;

		case "room_night":
			dialog.text = "Eso serán diez piezas de a ocho. ¿Quieres una chica para la habitación también? Solo mil pesos por la moza.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "No, no necesito una chica. Aquí, toma esto por la habitación.";
				link.l1.go = "room_night_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Está bien. Tomemos la habitación y a la chica. Aquí está el dinero.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_night";
				}
			}
			link.l3 = "¡Ay, no puedo permitirme la habitación!";
			link.l3.go = "exit";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -20);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "room_girl":
			AddMoneyToCharacter(pchar, -1010);
			dialog.text = "Sube arriba, señor. La chica te estará esperando. ¡Que tengas una buena estancia!";
			link.l1 = "Gracias, camarada...";
			link.l1.go = "room_girl_1";
		break;
		
		case "room_girl_1":
			DialogExit();
			pchar.GenQuest.CannotWait = true;
			pchar.GenQuest.LosTequesSex = "true";
			LocatorReloadEnterDisable("LosTeques_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("LosTeques_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			sld = GetCharacter(NPC_GenerateCharacter("MineFuckGirl" , "squaw_"+(rand(2)+1), "woman", "woman_B", 1, SPAIN, 1, true, "quest"));
			sld.dialog.FileName = "Tavern\LosTeques_Tavern.c";
			sld.dialog.currentnode = "MineFuckGirl";
			//sld.greeting = "";
			sld.name = GetIndianName(WOMAN);
			sld.lastname = "";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "LosTeques_tavern_upstairs", "goto", "goto1");
		break;
		
		case "MineFuckGirl":
			dialog.text = "Cómo, amo blanco. No mires a "+npchar.name+" así, "+npchar.name+" sabe cómo hacerlo todo incluso mejor que una india blanca del burdel. Ah, señor, usted es tan apuesto... Prometo que esta india le amará mucho tiempo.";
			link.l1 = "Eso suena bien, muéstrame tus mejores encantos indios. No necesitaré una danza de lluvia para hacerte mojar...";
			link.l1.go = "MineFuckGirl_sex";
		break;
		
		case "MineFuckGirl_sex":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¡Robo a plena luz del día! ¿Qué está pasando aquí? Espera, aguarda, camarada...","¡Oye, ¿qué estás haciendo ahí?! ¿Intentando robarme? Ahora estás jodido...","Espera, ¿qué demonios estás haciendo? ¡Resulta que eres un ladrón! Considera esto el final del camino, maldito...");
			link.l1 = LinkRandPhrase("¡Demonio!","¡Maldición!","Ah, mierda");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
