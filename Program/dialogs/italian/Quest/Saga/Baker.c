// Раймонд Бейкер - палач Сент-Джонса и возможный офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Vuoi qualcosa?";
			link.l1 = "No, non è nulla.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "baker":
			dialog.text = "Grazie, Capitano! Non oso pensare a che fine avrei fatto senza di voi...";
			link.l1 = "Me lo posso immaginare. Saresti crepato di fame o finito nello stomaco di qualche selvaggio di Dominica. Ma adesso hai l’occasione di sdebitarti con me.";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "In che modo posso esserle utile, Capitano?";
			link.l1 = "Vorrei sapere di più su un uomo. Diciamo che è un nostro amico comune. Anzi, un tuo amico molto stretto. Parlo del capitano Butcher. Sì, proprio quello che hai impiccato vent’anni fa. Santo cielo, perché sei diventato così pallido? Vuoi un goccio di rum?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "Sei... sei stato mandato da lui?";
			link.l1 = "Bagianate! Come potrei essere 'mandato da lui' se quello è morto! A me interessano di più le cose che ha lasciato piuttosto che il Macellaio in persona. Lettere, scritti, roba simile. Forse hai trovato qualcosa nelle sue tasche... Aspetta! Non ci arrivo. Davvero pensi che il Macellaio sia vivo? Sei stato proprio tu a mandarlo all'altro mondo!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			dialog.text = "Merda! Non capisci un accidente. Questo vuol dire che non ti ha mandato il Macellaio come pensavo...";
			link.l1 = "Ebbene, ebbene. La faccenda si fa sempre più intrigante. Pare che Henry avesse tutte le ragioni per temere il Macellaio, ed è per questo che il poveretto è morto d’infarto... Il Macellaio è ancora in vita?";
			link.l1.go = "baker_4";
		break;
		
		case "baker_4":
			dialog.text = "Lo è, Capitano... E stanno dando la caccia a me.";
			link.l1 = "Raymond, mi hanno detto che non sei uno sciocco. Non cercare di imbrogliarmi. Qui non ti minaccia nessuno, sei al sicuro. Dimmi tutto ciò che sai e vedrò di aiutarti. Magari abbiamo dei nemici in comune. Cominciamo dal Macellaio.";
			link.l1.go = "baker_5";
		break;
		
		case "baker_5":
			dialog.text = "È vivo, ma ora porta un altro nome! I suoi uomini mi fecero visita la notte dell'esecuzione. Jackman e un altro con un soprannome curioso. Se ben ricordo, lo chiamavano 'l’Annegato'.";
			link.l1 = "Il Boia. Henry il Boia.";
			link.l1.go = "baker_6";
		break;
		
		case "baker_6":
			dialog.text = "Giusto! Mi hanno offerto un affare semplice: crepare tra le più atroci sofferenze, oppure salvare il loro capitano. Così mi toccò inscenare l’esecuzione usando un marchingegno speciale che avevo ideato nei miei momenti d’ozio. Vedi, una simile costruzione di cinghie e staffe può distribuire il peso del corpo.\nTutto quel che serviva era agganciarla a un gancio segreto nella forca. Il ‘cadavere’ doveva recitare la parte alla perfezione, però. Devo ammettere che Lawrence fu davvero credibile, fece tutto come si deve, tranne che si rifiutò di pisciarsi addosso, per via di...";
			link.l1 = "Hai appena chiamato il Macellaio 'Lawrence'?";
			link.l1.go = "baker_7";
		break;
		
		case "baker_7":
			dialog.text = "Quello è il suo vero nome. Ti ho detto che si fa chiamare Lawrence Beltrope. Da quando è tornato nei Caraibi un anno fa, non ho più pace. E quando ho scoperto che certa gentaglia mi sta cercando...\nHo persino scritto una confessione per le autorità, nel caso. La porto sempre con me, troppo spaventato per consegnarla. Potrebbero pensare che fossi complice volontario. Ti supplico, lasciami restare con il tuo equipaggio. Ti giuro, sono un medico eccellente e potrei esserti davvero utile.";
			link.l1 = "Va bene. E che mi dici degli effetti personali del Macellaio... ehm, di Beltrope? È forse imparentato con quel Thomas Beltrope?";
			link.l1.go = "baker_8";
		break;
		
		case "baker_8":
			dialog.text = "Nessuna idea. Non mi è rimasto nulla di particolare da Beltrope in persona. Ma ti darò tutto quello che ho, sei libero di farne ciò che vuoi. Tutti i documenti sull’argomento sono nella mia borsa. Ho conservato ogni cosa per sicurezza e li tengo sempre con me. \nEcco, guarda... questa è la leggenda del capitano Butcher, questa è la mia confessione... Queste sono cose appartenute a Joshua Leadbeater...";
			link.l1 = "Fermo! Leadbeater? Chi diavolo sarebbe?";
			link.l1.go = "baker_9";
		break;
		
		case "baker_9":
			dialog.text = "Oh! Era davvero un uomo fuori dal comune. Fu lui a dare la caccia al Macellaio in persona. La gente lo ricordava come 'l’uomo mascherato'. Lo hanno ammazzato subito dopo l’esecuzione del Macellaio. Qualcuno gli ha sgozzato la gola con un dente di squalo! Un solo colpo, ed è finita lì. Da vivo, dev’essere stato un supplizio.\nSe avessi visto la sua faccia sotto la maschera, non era altro che carne viva! Aveva questa pagina di diario in tasca quando l’hanno trovato. Dev’essere roba scritta da Jessica Rose. Una storia da far drizzare i capelli! Leggila, così tutto ti sarà più chiaro.\nE questo è proprio il dente. Vedi le lettere? S.D.... Qualunque diavoleria significhi. Ci sono ancora tracce di sangue.";
			link.l1 = "Basta! Devo leggere tutto con calma e rifletterci su. E tu, Raymond, sarai il mio passeggero oppure il medico di bordo finché non avrò sistemato questa faccenda. Ora puoi tirare un respiro di sollievo, Raymond, sulla mia nave sei al sicuro.";
			link.l1.go = "baker_10";
		break;
		
		case "baker_10":
			DialogExit();
			sld = characterFromId("Baker_Cap");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
			//sld.ship.hp = 0;
			//sld.SinkTenPercent = true;
			bQuestDisableMapEnter = false;
			GiveItem2Character(pchar, "shark_teeth");
			GiveItem2Character(pchar, "letter_jess");
			GiveItem2Character(pchar, "letter_baker"); // показания бейкера
			ChangeItemDescribe("letter_baker", "itmdescr_letter_baker"); // Addon-2016 Jason
			AddQuestRecordInfo("Legend_CapBucher", "1");
			AddQuestRecordInfo("Letter_jess", "1");
			AddQuestRecord("Shadows", "5");
			pchar.questTemp.Saga.Shadows = "islatesoro";
			// в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Baker_officer";
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddCharacterExpToSkill(pchar, "Sailing", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Baker_officer":
			dialog.text = "Sì, capitano?";
			Link.l1 = "Ascoltate il mio comando!";
            Link.l1.go = "stay_follow";
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Raymond, fammi un rapporto completo della nave.";
			    Link.l11.go = "QMASTER_1";

			    // Warship. Автозакупка товара
				Link.l12 = "Voglio che tu acquisti certe merci ogni volta che siamo in porto.";
				Link.l12.go = "QMASTER_2";
			}
			
			link.l2 = "Non è nulla. Sciogliete le vele!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Baker_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
        case "QMASTER_1":
			dialog.Text = "Andiamo, Capitano, sono un medico, non un contabile di bordo. Anche se, un tempo, mi occupavo d'altro... lasciamo perdere. I libri contabili non fanno per me, mi spiace.";
			Link.l1 = "Va bene, sia così. Sei il mio cerusico, come pattuito quando sei salito a bordo della mia ciurma.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Capitano, a dire il vero, non ho mai avuto molta esperienza con il commercio. Mai trattato, mai controllato i prezzi. E poi... preferirei restare a bordo, se non vi dispiace. Qualcuno di quei mercanti potrebbe riconoscermi e, prima che ve ne accorgiate, arrivano uomini mascherati a cercar rogne.";
			link.l1 = "Dunque, continuerai a vivere nel terrore del tuo passato... Va bene, rilassati, ci penserò io.";
			Link.l1.go = "exit";
        break;
		
		case "stay_follow":
            dialog.Text = "Ordini?";
            Link.l1 = "Fermati qui!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Seguimi e non rimanere indietro!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Cambia il tipo di munizione per la tua arma da fuoco.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Scegliendo il tipo di munizioni:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Vento di cambiamento in vista!";
            Link.l1 = "Congedato.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Vi è mutamento d’animo!";
            Link.l1 = "Congedato.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
