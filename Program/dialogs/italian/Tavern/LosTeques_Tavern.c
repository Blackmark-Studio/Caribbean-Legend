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
	
	bool block = (CheckAttribute(pchar, "GenQuest.BrothelLock")) && (GetCharacterIndex("Mary") != -1);
	bool block1 = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) && (IsOfficer(characterFromId("Helena")));

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("C'è stato un allarme in città. Tutti ti stanno cercando! Non aspetterei qui troppo a lungo se fossi in te.","Tutta la guardia sta setacciando la città cercando di trovarti. Non sono un idiota e non sto per parlare con te!","Corsa, compagno, prima che i soldati ti facciano a pezzi..."),LinkRandPhrase("Cosa vuoi, mascalzone?! La guardia cittadina è già sulle tue tracce. Non andrai lontano, pirata!","Sporco assassino, esci dalla mia casa! Guardie!!","Non ho paura di te, cane! La forca ti chiama, non andrai lontano..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Eh, non mi preoccupo dell'allarme...","Non hanno alcuna possibilità di prendermi."),RandPhraseSimple("Chiudi la bocca, "+GetWorkTypeOfMan(npchar,"")+", o ti taglierò quella maledetta lingua.","Ehi, "+GetWorkTypeOfMan(npchar,"")+", anche tu vuoi cacciare un pirata? Ascolta, amico, mantieni la calma e potresti vivere..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"! Benvenuto, "+GetAddress_Form(NPChar)+" alla taverna della miniera di Los-Teques. Cibo, bevande e ragazze, tutto a prezzi accessibili! Mi chiamo "+GetFullName(npchar)+" e sono sempre al tuo servizio.";
				Link.l1 = "Vediamo... Io sono "+GetFullName(pchar)+". Piacere di conoscerti, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Aha, è il mio vecchio conoscente, capitano "+GetFullName(pchar)+"! Felice di vederti, vecchio! Rum, ragazze?";
				if (makeint(pchar.money) >= 5)
				{
					link.l1 = "Versami un po' di rum, "+npchar.name+".";
					link.l1.go = "drink";
				}
				link.l2 = "Vorrei fare un pisolino. Avete una stanza libera?";
				link.l2.go = "room";
				link.l3 = LinkRandPhrase("Avete delle notizie recenti?","Cosa c'è di nuovo da queste parti?","Come va la vita sulla terraferma?");
				link.l3.go = "rumours_tavern";
				link.l4 = "No, non ho bisogno di nulla, "+npchar.name+". Sono solo passato per salutarti.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Oh, sono così felice! Nuovi volti sono una rarità nella nostra città. Che ne dici se ti verso un po' di rum e facciamo due chiacchiere...";
			link.l1 = "È la mia prima volta qui e mi piacerebbe scoprire un po' di più su questo insediamento.";
			link.l1.go = "info";
			if (makeint(pchar.money) >= 5)
			{
				link.l2 = "Versami un po' di rum, "+npchar.name+".";
				link.l2.go = "drink";
			}
			link.l3 = "Vorrei fare un pisolino. Avete una stanza libera?";
			link.l3.go = "room";
		break;
		
		case "info":
			dialog.text = "Nulla di interessante da raccontare. Sempre lo stesso affare ogni giorno: noia, sole e polvere. Qui vivono solo soldati, negri e indiani. Potresti anche trovare qualche avventura e banditi affamati d'oro\nA volte gentiluomini, capitani come te, ci visitano per vendere schiavi in cambio di lingotti e comprare metalli preziosi. Il nostro mercante è un uomo piuttosto interessante, vende non solo pepite d'oro e d'argento, ma anche gemme semipreziose\n Sostiene che persone con conoscenze speciali possano trovare queste pietruzze molto utili. Quindi dai un'occhiata al nostro negozio. La miniera stessa si trova più in fondo alla montagna. Puoi visitarla se lo desideri, ma ti consiglio di evitare di far arrabbiare la guardia\nNon parlare con i detenuti e Dio ti salvi dal furto. Ad ogni modo, il posto migliore in questo insediamento è la mia taverna, il posto migliore per riposarsi da questo inferno ardente!";
			link.l1 = "Grazie per l'informazione!";			
			link.l1.go = "exit";
		break;
		
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 3)
			{
				dialog.text = "Capitano, penso che sarebbe meglio se la smettessi. Dio non voglia che tu faccia casino mentre sei sotto l'effetto dell'alcool. Qui siamo molto rigidi su questo. Nemmeno la tua autorità ti aiuterebbe.";
				link.l1 = "Mh... Suppongo che tu abbia ragione - ne ho già abbastanza. Grazie per la preoccupazione!";			
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
				
				dialog.text = "Siete i benvenuti, capitano. Solo cinque pezzi di otto per una pinta del mio miglior rum giamaicano nero!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("Bene, alla tua salute e alla prosperità del tuo locale, compagno!","Bene, a quelli in mare!","Bene, alla salute della vostra città!"),LinkRandPhrase("Bene, ai venti della produzione, a una folata di fortuna, che tutti noi viviamo più spensierati e ricchi!","Bene, al vento che soffia sempre nelle nostre spalle in tutti gli affari!","Bene, alla felicità, fortuna, gioia e ragazze!"));		
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
				dialog.text = "Signore, hai pagato per una stanza e una ragazza. Vai su, ti sta aspettando da un po'.";
				link.l1 = "Va bene.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Certo. Quanto tempo pensavi di restare?";
			if(!isDay())
			{
				link.l1 = "Fino al mattino.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Fino alla notte.";
				link.l1.go = "room_night";
				link.l2 = "Fino alla prossima mattina.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "Saranno dieci pezzi di otto. Vorresti una ragazza per la stanza insieme a questo? Solo mille pesos per la sgualdrina.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "No, non ho bisogno di una ragazza. Ecco, prendi questo per la stanza.";
				link.l1.go = "room_day_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !block || !block1)
				{
					link.l2 = "Certo, prenderò la stanza e la ragazza. Ecco i soldi.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Purtroppo, non posso permettermi la stanza.";
			link.l3.go = "exit";
		break;

		case "room_day_next":
			dialog.text = "Saranno dieci pezzi da otto. Vorresti una ragazza per la stanza insieme? Solo mille pesos per la sgualdrina.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "No, non ho bisogno di una ragazza. Ecco, prendi questo per la stanza.";
				link.l1.go = "room_day_wait_next";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !block || !block1)
				{
					link.l2 = "Bene. Prendiamo la stanza e la ragazza. Ecco i soldi.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Ahimè, non posso permettermi la stanza.";
			link.l3.go = "exit";
		break;

		case "room_night":
			dialog.text = "Saranno dieci pezzi da otto. Vorresti una ragazza per la stanza insieme a questo? Solo mille pesos per la sgualdrina.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "No, non ho bisogno di una ragazza. Ecco, prendi questo per la stanza.";
				link.l1.go = "room_night_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !block || !block1)
				{
					link.l2 = "Bene. Prendiamo la stanza e la ragazza. Ecco i soldi.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_night";
				}
			}
			link.l3 = "Ahimè, non posso permettermi la stanza.";
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
			dialog.text = "Prosegui al piano di sopra, signore. La ragazza ti starà aspettando. Buona permanenza!";
			link.l1 = "Grazie, amico...";
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
			dialog.text = "Come, padrone bianco. Non guardare "+npchar.name+" così, "+npchar.name+" sa come fare tutto ancora meglio della squaw bianca del bordello. Ah, signore sei così bello... Prometto, questa squaw ti amerà a lungo.";
			link.l1 = "Sembra interessante, mostrami i tuoi migliori amuleti indiani. Non avrò bisogno di una danza della pioggia per bagnarti...";
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
			dialog.text = LinkRandPhrase("Rapina in pieno giorno!!! Che cosa succede qui?! Aspetta, fermati, amico...","Ehi, cosa stai facendo lì?! Stai cercando di derubarmi? Ora sei nei guai...","Aspetta, che diavolo stai facendo? Si scopre che sei un ladro! Considera questa la fine della linea, stronzo...");
			link.l1 = LinkRandPhrase("Dannazione!","Cazzo!","Ah, merda");
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
