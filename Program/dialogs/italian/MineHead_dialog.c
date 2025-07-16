// диалог начальника шахты
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		location = &Locations[FindLocation(pchar.location)];
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Osi mostrare la tua faccia qui?! Non so se sei coraggioso o stupido...","Come hanno fatto questi fannulloni a lasciare che un nemico irrompesse nella mia residenza? Questo mi supera...","Certo, le mie guardie non valgono un soldo, se questi bastardi, girano da queste parti..."),LinkRandPhrase("Di cosa hai bisogno,"+GetSexPhrase("farabutto","puzzolente")+"?! I miei soldati sono già sulle tue tracce, "+GetSexPhrase(", sporco pirata","")+"!","Sporco assassino, lascia subito la mia residenza! Guardie!","Non ho paura di te, "+GetSexPhrase("ratto","sgualdrina")+"! Presto sarai impiccato nel nostro forte, e non andrai lontano dopo..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Questi soldati non valgono un solo peso...","Non mi prenderanno mai."),RandPhraseSimple("Chiudi il tuo becco, "+GetWorkTypeOfMan(npchar,"")+", o strapperò quella tua lingua infame!","Ti suggerirei di stare tranquillo, e forse, ne uscirai vivo..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Nemico nella miniera! Allarme!";
				link.l1 = "Aaah, diavolo!";
				link.l1.go = "fight"; 
				break;
			}	
			dialog.text = LinkRandPhrase(""+TimeGreeting()+", signore. Io sono "+GetFullName(npchar)+", l'ingegnere minerario della miniera di Los-Teques. Cosa ti serve qui?","Ciao, signore. Cosa desiderava?","Hmm... desiderava qualcosa da me, signore? Sto ascoltando.");
			if (!CheckAttribute(location, "quest.info"))
			{
				link.l9 = "Sono nuovo qui, e vorrei saperne di più su questa miniera...";
				link.l9.go = "info";
			}
			if (GetSquadronGoods(pchar, GOOD_SLAVES) > 4)
			{
				link.l2 = "Ho un carico nella mia stiva che potrebbe interessarti. Schiavi per la tua miniera, per l'esattezza. Vuoi contrattare?";
				if (!CheckAttribute(location, "quest.slaves")) link.l2.go = "slaves_0";
				else link.l2.go = "slaves";
			}
			link.l1 = "Sono appena entrato per salutare, e sto già andando via.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "La miniera di Los-Teques estrae oro per la Corona Spagnola. Tutto ciò che estraiamo appartiene alla Spagna. Qui troviamo non solo oro, ma anche pepite d'argento e preziose gemme di valore. Non vendiamo oro qui, tutto ciò che estraiamo viene consegnato al Vecchio Mondo sotto un convoglio rinforzato\nMa abbiamo due eccezioni per le pepite d'oro e d'argento. Prima, puoi comprare una certa quantità di loro nel nostro negozio locale da un quartiermastro. A volte, lo stipendio non arriva in tempo, quindi dobbiamo mantenere qui delle riserve di monete per tali casi, ecco perché il commercio locale è permesso\nSecondo, abbiamo costantemente bisogno di manodopera, quindi scambiamo pepite per schiavi. Quindi, parla con me se hai qualcosa da offrire, faremo affari\nCredo che le regole di condotta della miniera siano ovvie: non rubare, non distrarre i detenuti e non disturbare i soldati altrimenti non ti piaceranno le conseguenze.";
			link.l1 = "Bene, grazie!";			
			link.l1.go = "exit";
			location.quest.info = "true";
		break;
		
		// генератор купли-продажи рабов
		case "slaves_0":
			location.quest.slaves.qty = 200; // стартовая потребность
			dialog.text = "Certo, signore! Quanti ne hai?";
			link.l1 = "Ho "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves":
			location.quest.slaves.qty = sti(location.quest.slaves.qty)+GetNpcQuestPastDayParam(location, "slave_date"); // каждый день даёт +1 потребности
			if (sti(location.quest.slaves.qty) > 350) location.quest.slaves.qty = 350; // максимум потребности
			if (sti(location.quest.slaves.qty) < 5)
			{
				dialog.text = "Signore, purtroppo, al momento non abbiamo bisogno di più schiavi. Ma la situazione può cambiare in qualsiasi momento, quindi torna a controllare tra qualche settimana o in un altro momento.";
				link.l1 = "Va bene, signore, capisco. Non ne hai bisogno ora, ma potresti averne bisogno tra un po'.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Certo, signore! Quantos ne avete?";
				link.l1 = "Ho "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
				link.l1.go = "slaves_1";
			}
		break;
		
		case "slaves_1":
			dialog.text = "Per ogni schiavo, sono disposto a pagarti un lingotto d'oro o due lingotti d'argento. Cosa scegli?";
			link.l1 = "Lingotti d'oro.";
			link.l1.go = "slaves_g";
			link.l2 = " Lingotti d'argento.";
			link.l2.go = "slaves_s";
			link.l3 = "Mi dispiace, signore, ma ho appena cambiato idea. Un'altra volta.";
			link.l3.go = "slaves_exit";
		break;
		
		case "slaves_g":
			location.quest.slaves.type = "gold";
			dialog.text = "Bene. Quanti schiavi stai per vendermi?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_s":
			location.quest.slaves.type = "silver";
			dialog.text = "Bene. Quanti schiavi stai per vendermi?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_trade":
			iTotalTemp = sti(dialogEditStrings[6]);
			if (iTotalTemp < 1)
			{
				dialog.text = "Signore, non ho tempo per stupide battute. Se sei in vena di scherzi, vai alla taverna!";
				link.l1 = "Uhm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > GetSquadronGoods(pchar, GOOD_SLAVES))
			{
				dialog.text = "Signore, penso che abbiate bisogno di riposarvi. Forse siete molto stanchi o avete preso un colpo di calore. Andate alla taverna, riposatevi bene, e poi possiamo continuare il nostro mercanteggiare.";
				link.l1 = "Mmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > sti(location.quest.slaves.qty))
			{
				dialog.text = "Sfortunatamente, signore, al momento non abbiamo bisogno di così tanti schiavi. La miniera attualmente richiede "+FindRussianQtyString(sti(location.quest.slaves.qty))+". Hai intenzione di vendere così tanto?";
				link.l1 = "Sì, certo!";
				link.l1.go = "slaves_max";
				link.l2 = "Mmm... Credo di no.";
				link.l2.go = "slaves_exit";
				break;
			}
			dialog.text = ""+FindRussianQtyString(iTotalTemp)+"? Eccellente. Per favore, ordina di portarli alle porte della città. Manderò i miei uomini a prenderli.";
			link.l1 = "Non preoccuparti, signore. I tuoi schiavi ti saranno consegnati in tempo. Emetterò immediatamente tutti gli ordini pertinenti.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_max":
			iTotalTemp = sti(location.quest.slaves.qty);
			dialog.text = "Eccellente. Ordina di portarli alle porte della città. Mandarò i miei uomini a prenderli.";
			link.l1 = "Non preoccuparti, signore. I tuoi schiavi ti saranno consegnati in tempo. Emetterò tutti gli ordini pertinenti immediatamente.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_calk":
			DialogExit();
			Log_Info("Exchange of slaves for ingots has been completed");
			PlaySound("interface\important_item.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,5,10);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, iTotalTemp);
			if (location.quest.slaves.type == "gold") TakeNItems(pchar, "jewelry5", iTotalTemp);
			else TakeNItems(pchar, "jewelry6", iTotalTemp*2);
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
			location.quest.slaves.qty = sti(location.quest.slaves.qty)-iTotalTemp;
		break;
		
		case "slaves_exit":
			DialogExit();
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		    LAi_group_Attack(NPChar, Pchar);
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
