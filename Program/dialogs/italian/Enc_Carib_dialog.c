void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, iMush, qty;
	string sGroup, sLink, sText;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "First time":
			dialog.text = "Congratulazioni! Questo è un bug. Contatta Jason e digli come e dove hai trovato questo. Pace!";
			link.l1 = "Lo farò immediatamente!";
			link.l1.go = "exit";
			Diag.TempNode = "First time";
		break;

		case "exit_fight":
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_peace":
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}	
			ChangeIndianRelation(1.00);
		break;
		
		// военные индеи - карибы
		case "war_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				dialog.text = LinkRandPhrase("Salve a te, figlio del mare! Ho sentito parlare di te. Puoi camminare tranquillo sulla nostra terra.",""+npchar.name+" ti saluta, fratello dal volto pallido. Siamo lieti di vederti come nostro ospite.","Ti saluto, coraggioso guerriero dal volto pallido!"+npchar.name+" è lieto di incontrare un amico degli Indiani. Vai in pace!");
				link.l1 = RandPhraseSimple("E saluti a te, fratello dalla pelle rossa! Buona caccia a te!","Saluti, valoroso guerriero! Che gli dei benedicano te e la tua famiglia!");
				link.l1.go = "exit_peace";
				if (CheckCaribGuns())
				{
					npchar.quest.count = 0;
					link.l2 = RandPhraseSimple("Ho qualcosa che potrebbe interessarti, fratello dalla pelle rossa. Vuoi fare un affare?","Posso offrirti di comprare qualcosa di interessante, valoroso guerriero. Vuoi fare un affare?");
					link.l2.go = "war_indian_trade";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Fermati, viso pallido! Con quale diritto cammini sulla mia terra?","Fermati, uomo bianco! Tu sei sulla terra dei miei antenati e della mia terra!","Fermati, viso pallido! Non appartieni alla mia terra");
				link.l1 = RandPhraseSimple("La tua terra? Sparisci, sporcizia dalla faccia rossa!","Guardalo - una scimmia parlante! Sparisci, ora!");
				link.l1.go = "war_indian_1";
				link.l2 = RandPhraseSimple("Sono venuto in pace, guerriero dalla pelle rossa. Non dovremmo combattere per niente.","Non sono un nemico per te e la tua terra, guerriero. Sono venuto in pace.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/3)) > hrand(80)) link.l2.go = "war_indian_2_1";
				else link.l2.go = "war_indian_2_2";
				link.l3 = RandPhraseSimple("Sono venuto per commerciare con te, non per combattere.","Non combatto con gli indiani. Faccio commercio con loro.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/6)+makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE)/6)) > hrand(90)) link.l3.go = "war_indian_3_1";
				else link.l3.go = "war_indian_3_2";
			}
		break;
		
		case "war_indian_1":
			dialog.text = RandPhraseSimple("Ti penti di essere nato, cane dal viso pallido... Ti strappo il cuore e lo friggo sul fuoco!","Ti farò mangiare pietre, cane dalla faccia pallida! Ridiamo vedendoti implorare la morte in ginocchio, vile bianco!");
			link.l1 = RandPhraseSimple("Non riesci ancora a chiudere la tua bocca puzzolente, spaventapasseri dipinto? Ti riporterò nella giungla da cui sei venuto!","Osate minacciarmi, feccia?! Bene, ora salirai sull'albero da cui sei appena sceso!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_2_1":
			dialog.text = RandPhraseSimple("Sento che la tua voce parla vero. Non scoccheremo le nostre asce contro di te oggi. Vai in pace, viso pallido.","Viso pallido raramente porta pace, ma vedo nei tuoi occhi che dici la verità. Vai ora.");
			link.l1 = RandPhraseSimple("Una decisione saggia, guerriero. Buona fortuna a te.","Sono contento che siamo arrivati a un accordo, guerriero.");
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_2_2":
			dialog.text = RandPhraseSimple("Menti, vile viso pallido! Sei venuto qui per uccidere gli indiani! Pronto per la battaglia, viso pallido?!","Uccidi gli indiani. La lingua bianca è una lingua bugiarda. La taglio e la friggo sul fuoco!");
			link.l1 = RandPhraseSimple("Ebbene, compagno, non incolparmi allora. Dio sa, ho cercato di evitarlo...","Ebbene, l'hai chiesto tu, guerriero.");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_3_1":
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				dialog.text = "Commercio? Abbiamo bisogno dell'arma degli uomini bianchi. Un'arma di fuoco dell'uomo dal volto pallido! Per essa scambiamo le nostre merci! Hai un'arma di fuoco da scambiare?";
				link.l1 = "Mmm. Lo faccio. E cosa mi darai in cambio?";
				link.l1.go = "war_indian_trade";
				link.l2 = "Brigante! E poi sparare ai coloni con le mie pistole? No, non succederà! Per quanto riguarda voi, sciacalli, vi farò a pezzi ora...";
				link.l2.go = "exit_fight";
			}
			else
			{
				dialog.text = "Non hai quello che vogliamo, viso pallido... Sarai il nostro trofeo di guerra!";
				link.l1 = "Prova se osi, spaventapasseri...";
				link.l1.go = "exit_fight";
			}
		break;
		
		case "war_indian_3_2":
			dialog.text = RandPhraseSimple("Non commerciamo con i cani dai visi pallidi. Uccidiamo e prendiamo!","Non siamo sporchi miskito o arawak, non commerciamo con visi pallidi! Li uccidiamo e otteniamo trofei di guerra!");
			link.l1 = RandPhraseSimple("Allora, prova a derubarmi, mascalzone!","Prima, dovrai strapparmi di mano il mio sciabola, sporcaccione!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_trade":
			iGun = 1;
			dialog.text = "Mostra quello che hai, e noi diremo cosa diamo in cambio.";
			for (i=6; i>=1; i--)
			{
				if (GetCharacterFreeItem(pchar, "pistol"+i) > 0)
				{
					sLink = "l"+iGun;
					link.(sLink) = "Offer "+XI_ConvertString("pistol"+i)+".";
					link.(sLink).go = "gun_"+i;
					iGun++;				
				}
			}
		break;
		
		case "gun_1":
			npchar.quest.gun = "pistol1";
			if (hrand(1) == 0)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(1)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(9)+14);
				iTotalTemp = hrand(2)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "Ehi-oh! Ti diamo per questo "+sText+".";
			link.l1 = "Affare fatto!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. Assolutamente no.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_2":
			npchar.quest.gun = "pistol2";
			if (hrand(3) < 2)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(3)+1);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "Ehi-oh! Astuta arma... Te la diamo in cambio "+sText+".";
			link.l1 = "Affare fatto!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. Assolutamente no.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_3":
			npchar.quest.gun = "pistol3";
			if (hrand(5) < 3)
			{
				qty = rand(1)+2;
				npchar.quest.item = "jewelry5"+qty;
				iTotalTemp = hrand(6)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful pearl";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(2)+2);
				iTotalTemp = hrand(2)+5;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  this beautiful stone";
			}
			dialog.text = "Ehi-oh! Arma possente! Uccide molti-molti nemici! Te la diamo in cambio "+sText+".";
			link.l1 = "Affare fatto!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. Assolutamente no.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_4":
			npchar.quest.gun = "pistol4";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(10)+qty*30;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "obereg_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Ehi-oh! Arma temibile... Te la diamo in cambio "+sText+".";
			link.l1 = "Affare fatto!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. Impossibile.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_5":
			npchar.quest.gun = "pistol5";
			if (hrand(7) < 7)
			{
				if (hrand(10) < 8)
				{
					npchar.quest.item = "jewelry7";
					iTotalTemp = 2+hrand(1);
				}
				else
				{
					npchar.quest.item = "jewelry8";
					iTotalTemp = hrand(4)+10;
				}
				qty = hrand(1)+1;
				npchar.quest.item = "jewelry"+(qty+6);
				if (qty == 1) iTotalTemp = 2;
				else iTotalTemp = hrand(5)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful and precious petrified tar";
			}
			else
			{
				npchar.quest.item = "indian_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Ehi-oh! Bella e potente arma! Uccide molti-molti nemici! Te la diamo per questo "+sText+".";
			link.l1 = "Affare fatto!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. Assolutamente no.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_6":
			npchar.quest.gun = "pistol6";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(8)+qty*20;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "amulet_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Ehi-oh! Un'arma utile... Te la diamo in cambio "+sText+".";
			link.l1 = "Affare fatto!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. Assolutamente no.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "war_indian_trade_agree":
			ChangeIndianRelation(1.00);
			npchar.quest.count = sti(npchar.quest.count)+1;
			TakeNItems(pchar, npchar.quest.item, iTotalTemp);
			RemoveItems(pchar, npchar.quest.gun, 1);
			Log_Info("You have given "+XI_ConvertString(npchar.quest.gun)+"");
			Log_Info("You have received "+XI_ConvertString(npchar.quest.item)+" in amount of "+FindRussianQtyString(iTotalTemp)+"");
			PlaySound("interface\important_item.wav");
			if (sti(npchar.quest.count) > 3+hrand(2));
			{
				dialog.text = "Bene. Ecco la tua merce. Non commerciamo più. Torna più tardi. Daremo di più per una migliore arma infuocata. Ora vai!";
				link.l1 = "Addio, guerriero dalla pelle rossa.";
				link.l1.go = "exit_peace";
			}
			else
			{
				dialog.text = "Bene. Ecco la tua merce. Hai altre armi infuocate da scambiare?";
				if (CheckCaribGuns())
				{
					link.l1 = "Ho. Comprerai?";
					link.l1.go = "war_indian_trade";
				}
				link.l2 = "No. La prossima volta porterò di più.";
				link.l2.go = "war_indian_trade_exit";
			}
		break;
		
		case "war_indian_trade_exit":
			dialog.text = "Porta. Più migliore è l'arma infuocata, più ti daremo in cambio. Ora vai!";
			link.l1 = "Arrivederci, guerriero...";
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_trade_bad":
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				DialogExit();
				sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
				for(i = 0; i < iTemp; i++)
				{
					sld = CharacterFromID(sTemp + i);
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sGroup);
					LAi_SetImmortal(sld, false);
					LAi_CharacterDisableDialog(sld);
				}	
			}
			else
			{
				dialog.text = "Allora prendiamo tutto gratuitamente, viso pallido!";
				link.l1 = "Potresti provare...";
				link.l1.go = "exit_fight";
			}
		break;
		
		// мирные индеи - мискито
		case "peace_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase("Salve, uomo bianco. Di cosa hai bisogno nella nostra giungla?","La nostra giungla è molto pericolosa. Cosa fai qui?","Cosa ti porta qui, audace viso pallido?");
			link.l1 = RandPhraseSimple("Stavo solo passando, amico dalla pelle rossa. Credo ci sia abbastanza spazio su questo sentiero per entrambi, no?","Saluti, figlio della giungla! Sono qui per affari, e non combatto contro gli Indiani.");
			link.l1.go = "peace_indian_1";
			link.l2 = RandPhraseSimple("E perché devi saperlo? Vai per la tua strada e stai lontano dai guai!","Vai per la tua strada, pelle rossa. Non ho tempo di parlare con te.");
			link.l2.go = "peace_indian_2";
		break;
		
		case "peace_indian_1":
			dialog.text = RandPhraseSimple("Noi gente pacifica. Non siamo nemici degli uomini bianchi. Vai, ma fai attenzione sulla nostra terra!","Sono lieto di incontrare l'amico pallido degli indiani. Vai in pace, figlio del mare!");
			link.l1 = RandPhraseSimple("Buona fortuna anche a te, figlio della selva...","Addio, amico dalla pelle rossa.");
			link.l1.go = "exit_peace";
		break;
		
		case "peace_indian_2":
			dialog.text = RandPhraseSimple("Siamo cacciatori pacifici. Ma non tolleriamo quando un viso pallido parla così sulla nostra terra!","Non combattiamo con gli uomini bianchi, ma se gli uomini bianchi ci offendono, rispondiamo come i nostri antenati ci hanno insegnato!");
			link.l1 = RandPhraseSimple("Non riesci ancora a chiudere quella bocca puzzolente, spaventapasseri dipinto? Ti rimanderò nella giungla da cui sei venuto!","Osate minacciarmi, feccia?! Ora risalirai sull'albero da cui sei appena sceso!");
			link.l1.go = "exit_fight";
		break;
	}
}
