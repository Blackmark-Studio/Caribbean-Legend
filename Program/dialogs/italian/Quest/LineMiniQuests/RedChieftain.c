void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Questo è un maledetto errore. Fate sapere ai diavoli dello sviluppo.";
			link.l1 = "Lo farò!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "RedChieftain":
			dialog.text = "Ehi, faccia pallida. Vedo che tu sei capitano di grande canoa. Io sono Kanauri. Io capo di Cayman – possente tribù Arawak. Voglio parlare con te.";
			link.l1 = "Ascolto, capitano. Quali grane ti hanno spinto da me?";
			link.l1.go = "RedChieftain_0";
			link.l2 = "Cosa vuoi da me, scimmione dalla pelle rossa? Torna nelle tue giungle e non scocciarmi con le tue richieste.";
			link.l2.go = "RedChieftain_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
		break;
		
		case "RedChieftain_exit":
			dialog.text = "U-u! Il capitano bianco non ha imparato le buone maniere? Ho fatto un’offerta. Potevi guadagnare un mucchio di conchiglie, ma adesso me ne vado. Addio, faccia pallida.";
			link.l1 = "Va', sparisci...";
			link.l1.go = "RedChieftain_exit_1";
		break;
		
		case "RedChieftain_exit_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.RedChieftain");
			chrDisableReloadToLocation = false;
			ChangeIndianRelation(-3.0);
		break;
		
		case "RedChieftain_0":
			dialog.text = "Fratello bianco saggio come gufo, furbo come serpe. Guai capitano all’indiano. Gran barcone d’uomini bianchi arriva al mio villaggio. Hanno preso tanti Cayman, la mia gente, li hanno messi sul loro barcone e portati via verso la Madre di Tutte le Acque...";
			link.l1 = "Aspetta... stai dicendo che la tua gente è stata ridotta in schiavitù da uomini bianchi arrivati su una nave?";
			if (sti(pchar.Basenation) == SPAIN) link.l1.go = "RedChieftain_2";
			else link.l1.go = "RedChieftain_1";
		break;
		
		case "RedChieftain_1":
			dialog.text = "Parli bene, fratello bianco. So che quei visi pallidi non sono tuoi amici. Quegli uomini bianchi crudeli della tribù spagnola. Prendono la mia gente. Ma io li trovo. Gli spagnoli fanno lavorare l’indiano dall’alba al tramonto, a tuffarsi nelle braccia della Madre delle Acque, a cercar conchiglie colme delle lacrime degli dèi.";
			link.l1 = "Pesca di perle... È un mestiere da cani.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Spa = "true";
			pchar.questTemp.RedChieftain.AttackNation = SPAIN;
		break;
		
		case "RedChieftain_2":
			dialog.text = "Parli giusto, fratello bianco. So che quella gente non ti è amica. Sono della tribù inglese. Prendono la mia gente. Ma li troverò. Gli inglesi fanno lavorar gli indiani dall’alba al tramonto, li mandano a tuffarsi nella Madre delle Acque, a cercar conchiglie piene delle lacrime degli dèi.";
			link.l1 = "Pesca delle perle... È un mestiere duro, questo.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Eng = "true";
			pchar.questTemp.RedChieftain.AttackNation = ENGLAND;
		break;
		
		case "RedChieftain_3":
			dialog.text = "Indiani ammalati e muoiono per la schiavitù. L’uomo bianco non ha pietà per l’indiano. Frusta e pistola sono legge del bianco per gli indiani. Io sono vecchio. Non ho uomini per combattere. Gli Arawak di Cayman sono gente pacifica, noi abbiamo inventato la pipa della pace. Ti chiedo, fratello bianco, di sguainare frusta e pistola contro il bianco malvagio, salva l’Arawak.";
			link.l1 = "Mi stai chiedendo di dichiarare guerra? Devi capire, capitano, le mie risorse sono scarse.";
			link.l1.go = "RedChieftain_4";
		break;
		
		case "RedChieftain_4":
			dialog.text = "Niente guerra. Indiano libero. Mio popolo. Ti diamo tutte le lacrime degli dèi che abbiamo sulle canoe. Uccidi il malvagio bianco, aiuta l’indiano, prendi le lacrime degli dèi, vendile per un sacco di wampum. Montagne di wampum.";
			link.l1 = "Ah, ora capisco. No, Canauri, non posso aiutarti. Non posso farlo adesso – la mia nave ha bisogno di riparazioni, e non ho più provviste...";
			link.l1.go = "RedChieftain_wait";
			link.l2 = "In tal caso, sarebbe un piacere per me. Discutiamo i dettagli. Dove si trovano i tuoi uomini? Hai detto di averli già trovati...";
			link.l2.go = "RedChieftain_5";
		break;
		
		case "RedChieftain_wait":
			dialog.text = "Gu-u! Posso aspettare, fratello bianco... Resterò in questo porto ancora una luna, cercando il protettore della mia gente. Mi troverai qui quando sarai pronto.";
			link.l1 = "...";
			link.l1.go = "RedChieftain_wait_1";
		break;
		
		case "RedChieftain_wait_1":
			DialogExit();
			//LAi_ActorGoToLocator(npchar, "quest", "quest1", "RedChieftainStay", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			SetFunctionTimerCondition("RedChieftainDelete", 0, 0, 30, false);
			
			sld = CharacterFromID("RedChieftain");
            //LAi_SetStayType(sld);
			sld.dialog.currentnode = "RedChieftain_wait_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity, false);
		break;
		
		case "RedChieftain_wait_2":
			dialog.text = "Sei tornato, fratello bianco? Mi aiuterai a punire gli uomini malvagi e salvare l’indio?";
			link.l1 = "Pronto come non mai.";
			link.l1.go = "RedChieftain_wait_4";
			link.l2 = "Devo ancora prepararmi.";
			link.l2.go = "RedChieftain_wait_3";
		break;
		
		case "RedChieftain_wait_3":
			dialog.text = "Sarò qui, fratello bianco.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.Tempnode = "RedChieftain_wait_2";
		break;
		
		case "RedChieftain_wait_4":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
			dialog.text = "Sono davvero lieto che tu abbia accettato, fratello bianco!";
			link.l1 = "Parliamo dei dettagli, Canauri. Dove sono i tuoi uomini? Dicevi d'averli già trovati...";
			link.l1.go = "RedChieftain_5";
			pchar.quest.RedChieftainDelete.over = "yes"; //снять таймер
		break;
		
		case "RedChieftain_5":
			if (CheckAttribute(pchar, "questTemp.RedChieftain.Spa"))
			{
				AddMapQuestMarkShore("Shore19", true);
				pchar.questTemp.RedChieftain.Island = "Cumana";
				pchar.questTemp.RedChieftain.Shore = "Shore19";
				pchar.questTemp.RedChieftain.Add1 = "Spanish";
				pchar.questTemp.RedChieftain.Add2 = "Carupano Cove, not far from Cumana";
				dialog.text = "Sono accampati alla Baia di Carupano, vicino a un campo spagnolo chiamato Cumana. Ogni giorno salpano con le barche in mare, si tuffano nell'acqua, giù giù in profondità...";
				link.l1 = "Capisco. E gli spagnoli li tengono d’occhio mentre si tuffano?";
				link.l1.go = "RedChieftain_6";
			}
			else
			{
				AddMapQuestMarkShore("Shore54", true);
				pchar.questTemp.RedChieftain.Island = "SantaCatalina";
				pchar.questTemp.RedChieftain.Shore = "Shore54";
				pchar.questTemp.RedChieftain.Add1 = "English";
				pchar.questTemp.RedChieftain.Add2 = "Cape Perlas, not far from Blueweld";
				dialog.text = "Si accampano a Capo Perlas vicino a un accampamento inglese chiamato Blueweld. Ogni giorno salpano con le barche in mare, si tuffano nell’acqua, giù, sempre più a fondo...";
				link.l1 = "Capisco. E naturalmente, gli inglesi li tengono d’occhio, vero?";
				link.l1.go = "RedChieftain_6";
			}
		break;
		
		case "RedChieftain_6":
			dialog.text = "Sì, due grandi canoe di visi pallidi con bastoni di fuoco e coltelli enormi. Il campo sulla riva è ben sorvegliato – un indiano non può sfuggire.";
			link.l1 = "Che razza di navi? Sai descriverle? Quanto sono grandi? Che vele portano?";
			link.l1.go = "RedChieftain_7";
		break;
		
		case "RedChieftain_7":
			dialog.text = "Questa canoa è grande, ma Canauri ne ha viste di più grosse. La vela davanti è molto, molto inclinata, fa tre lati così. (Disegna tre vele latine e una vela trapezoidale nella sabbia) In cima è stretta, in fondo è larga.";
			link.l1 = "Sembra proprio una goletta...";
			link.l1.go = "RedChieftain_8";
		break;
		
		case "RedChieftain_8":
			dialog.text = "Canauri non conosce quella parola. Faccia pallida stia bene attento se vede un’altra canoa – loro sbarcano indiani e aspettano che l’altra canoa se ne vada.";
			link.l1 = "Figli di puttana guardinghi... come diavolo mi avvicino a loro?";
			link.l1.go = "RedChieftain_9";
		break;
		
		case "RedChieftain_9":
			dialog.text = "Se il fratello dalla pelle chiara prende una piccola canoa, allora può avvicinarsi di soppiatto alla riva. Io mostro la via. Ma porta solo una piccola canoa, altrimenti il cane del viso pallido vedrà e scaccerà l’indiano dalla barca nella giungla...";
			link.l1 = "Capito. Mi servirà una lancia o una goletta per quest’operazione. Perfetto. Una sloop contro due schooner... Dio mio... e pensare che credevo sarebbe stata una passeggiata!";
			link.l1.go = "RedChieftain_10";
		break;
		
		case "RedChieftain_10":
			dialog.text = "Andiamo, fratello bianco? Ci resta meno d’una luna.";
			link.l1 = "Sì. Sali sulla mia nave, capitano. Non perdiamo tempo!";
			link.l1.go = "RedChieftain_11";
		break;
		
		case "RedChieftain_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.Red_Chieftain_2.win_condition.l1 = "location";
			pchar.quest.Red_Chieftain_2.win_condition.l1.location = pchar.questTemp.RedChieftain.Island;
			pchar.quest.Red_Chieftain_2.function = "RedChieftain_CreateShooner";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("RedChieftainOver", 0, 0, 30, false);
			AddQuestRecord("RedChieftain", "1");
			AddQuestUserData("RedChieftain", "sText1", pchar.questTemp.RedChieftain.Add1);
			AddQuestUserData("RedChieftain", "sText2", pchar.questTemp.RedChieftain.Add2);
		break;
		
		case "RedChieftain_pearl":
			dialog.text = "Grazie, fratello bianco! Hai salvato la tribù Arawak di Cayman! Ti dobbiamo un gran debito. Il sentiero è libero dai cani dalla pelle chiara e l’indiano può correre libero nella giungla. Ti doniamo tutte le lacrime degli dèi rimaste sulle barche.";
			link.l1 = "Vediamo un po' che mercanzia porti...";
			link.l1.go = "RedChieftain_pearl_1";
		break;
		
		case "RedChieftain_pearl_1":
			DialogExit();
			pchar.questTemp.RedChieftain.Ind = 1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_pearl_give":
			int iSmallPearl = rand(200)+rand(250)+rand(200)+250;
			int iBigPearl = rand(100)+rand(100)+rand(50)+150;
			TakeNItems(pchar, "jewelry52", iBigPearl);
			TakeNItems(pchar, "jewelry53", iSmallPearl);
			PlaySound("interface\important_item.wav");
			Log_SetStringToLog("The Chief has given you "+iSmallPearl+" small and "+iBigPearl+" big pearls.");
			dialog.text = LinkRandPhrase("Sono lieto che le lacrime degli dèi siano tue, fratello degli Arawak!","Indiano ti ringrazia, coraggioso viso pallido!","Prendi il nostro bottino, fratello bianco!");
			link.l1 = LinkRandPhrase("Felice di darti una mano!","Grazie, fratello dalla pelle rossa!","Grandioso!");
			link.l1.go = "exit";
			pchar.questTemp.RedChieftain.Ind = sti(pchar.questTemp.RedChieftain.Ind)+1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_final":
			chrDisableReloadToLocation = false;//открыть локацию
		// belamour legendary edition -->
			if(sti(pchar.questTemp.RedChieftain.Tartane) > 5)
			{
				dialog.text = "Canauri ti ringrazia ancora, fratello dalla faccia pallida! Hai salvato tutte le canoe con l’indiano! Per Canauri è cosa assai importante salvare ogni canoa, perché così hai pure liberato il nipote di Canauri, che quei cani bianchi avevano strappato via in catene. Da fanciullo, il mio nipote amava nuotare più di ogni cosa, e Canauri gli diede quest’amuleto incantato perché non affogasse mai. Ora il ragazzo non vuole più saperne dell’acqua e mi ha restituito l’amuleto, così che io possa donarlo a te, fratello pallido. Spero che le lacrime degli dèi e questo dono bastino come ricompensa per la vita di un Arawak. E ora ci congediamo – è tempo per noi di far ritorno al nostro villaggio nativo.";
				link.l1 = "Buona fortuna, Cunauri! Felice che tuo nipote sia sopravvissuto! Che questa maledizione non ti colpisca mai più, te lo giuro su tutti i santi!";
				link.l1.go = "RedChieftain_final_1Obereg";
			}
			else
			{
				dialog.text = "Canauri ti ringrazia ancora, fratello dalla pelle chiara! Spero che le lacrime degli dèi basteranno a ricompensare la vita degli indiani. Ora addio, torniamo al villaggio natio.";
				link.l1 = "Buona fortuna, Cunauri! Che tu non sia mai più fatto schiavo!";
				link.l1.go = "RedChieftain_final_1";
			}
			if(SandBoxMode)
			{
				//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
				//{
					//if(makeint(pchar.questTemp.SanBoxTarget) == 2 ||  makeint(pchar.questTemp.SanBoxTarget) == 5)
					//{
						pchar.questTemp.SanBoxTarget.RedChieftain = true;
						ChangeCharacterComplexReputation(pchar, "fame", 25);
					//}
				//}
			}
		break;
		
		case "RedChieftain_final_1Obereg":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n1 = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n1; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			TakeNItems(pchar, "talisman10", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received Seeker's obereg");
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "9");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		// <-- legendary edition
		
		case "RedChieftain_final_1":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "8");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
