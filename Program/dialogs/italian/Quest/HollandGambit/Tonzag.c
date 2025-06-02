// Эркюль Тонзаг, он же Плешивый Гастон
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
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MainBegin")
			{
				dialog.text = "Ebbene, buongiorno, "+pchar.name+". Lieto di vederti ancora tra i vivi.";
				link.l1 = "Gaston! Sei proprio tu?";
				link.l1.go = "SJ_talk";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetTonzag")
			{
				dialog.text = "Salute, "+pchar.name+" So già tutto sulle tue faccende – John mi ha raccontato ogni cosa. Non so nemmeno cosa dire. Ti ammiro!";
				link.l1 = "Mi fa piacere sentire simili lodi da te, Hercule!";
				link.l1.go = "SJ_talk_11";
				break;
			}
			dialog.text = "Buon pomeriggio. Avete qualche faccenda per me?";
			link.l1 = "No. Ho sbagliato. Mi scuso. Addio. .";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "SJ_talk":
			dialog.text = "Mi conoscevi con quel nome. Ma il mio vero nome è Hercule. Hercule Tonzag.";
			link.l1 = "Santo cielo! Pure io son lieto di vederti... Non ti avevo riconosciuto nel mezzo della mischia. Sei arrivato giusto in tempo con il tuo aiuto.";
			link.l1.go = "SJ_talk_1";
		break;
		
		case "SJ_talk_1":
			dialog.text = "Subito dopo la tua partenza ho saputo che Fleetwood ha rafforzato la sorveglianza della sua residenza. Ho pensato potesse esserci una trappola in agguato. Sono salpato all’istante per Antigua sulla mia nave 'Crepuscolo' – e come vedi, non a torto.";
			link.l1 = "Vero. Ho appena avuto la meglio sulle guardie dentro la casa, ma ero troppo sfinito per continuare a combattere per strada...";
			link.l1.go = "SJ_talk_2";
		break;
		
		case "SJ_talk_2":
			dialog.text = "Dopo quella scaramuccia, Fleetwood ha messo una spia olandese sulla lista dei ricercati. Pensavano che fossi tu quella spia. Lui ha una faida antica con loro. Il peggio è stato che un soldato in casa è sopravvissuto e si ricordava la tua faccia. Ma ormai non importa più. Ho finito quello che avevi iniziato tu. Quel soldato non riconoscerà più nessuno, e nessuno riconoscerà lui...";
			link.l1 = "L’hai fatto fuori? Capisco...";
			link.l1.go = "SJ_talk_3";
		break;
		
		case "SJ_talk_3":
			dialog.text = "Sì. Mentre te ne stavi svenuto a casa di John, ho ferito Fleetwood, ma quel bastardo è riuscito a sopravvivere. L'ho accecato – gli ho buttato pepe negli occhi e poi l'ho colpito prima che potesse sguainare la spada. Ma il cane portava una cotta di maglia sotto la divisa – gli ha salvato la pelle. Furbo, maledizione. Ora se ne sta a letto a casa sua, con la guardia raddoppiata. Un vero peccato che sia rimasto vivo.";
			link.l1 = "Dunque, il tuo compito principale ad Antigua era far fuori Fleetwood?";
			link.l1.go = "SJ_talk_4";
		break;
		
		case "SJ_talk_4":
			dialog.text = "In genere sì. Ma adesso pare impossibile: la casa è sempre sprangata, una mezza dozzina di alabardieri scelti piantonano giorno и notte, e fanno entrare к нему только одного доверенного — старого канонира Charlie, detto il Knippel.";
			link.l1 = "Già è qualcosa...";
			link.l1.go = "SJ_talk_5";
		break;
		
		case "SJ_talk_5":
			dialog.text = "Aspetta un po'... Hai davvero intenzione d’impicciarti in questa faccenda?";
			link.l1 = "Perché no? Non hai forse bisogno d'aiuto? Mi hai salvato, ed io voglio ricambiare. Inoltre, il mio borsello è ancora troppo leggero.";
			link.l1.go = "SJ_talk_6";
			// belamour legendary edition -->
			link.l2 = "Perché no? Siete gente seria. E la gente seria paga bene. Cerco solo un ingaggio.";
			link.l2.go = "SJ_talk_6a";
		break;
		
		case "SJ_talk_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			dialog.text = "Credimi, amico, non ci riuscirai mai. Sei in gamba, un vero talento, e quel registro che hai recuperato mi ha aiutato a pianificare un attentato contro Fleetwood, hai fatto un lavoro pulito con le guardie – ma ora raggiungere Fleetwood ti è impossibile. Neanch'io ho la minima idea di come si possa fare.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Ci rifletterò su. Ho ancora un po’ di tempo. Peccato che la mia nave sia stata sequestrata e che io sia senza equipaggio.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Ci penserò su. Ho tempo e una nave.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_6":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Credimi, amico, non ci riuscirai. Sei un tipo in gamba, davvero dotato, e il giornale di bordo che hai recuperato mi ha aiutato a pianificare un attentato contro Fleetwood, hai fatto un ottimo lavoro con quei cani da guardia – ma ora non riuscirai mai ad arrivare a Fleetwood. Persino io non ho la minima idea di come si possa fare.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Ci rifletterò su. Ho ancora tempo. Peccato che la mia nave sia stata sequestrata, e che io sia rimasto senza ciurma.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Ci penserò su. Ho il tempo e una nave.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_7":
			dialog.text = "Non ti crucciare per questo. Quando la tua vecchia bagnarola è stata messa sotto sequestro, ho preso tutti i tuoi ufficiali e parte dell’equipaggio a bordo della mia ‘Twilight’. Sanno che sei vivo e hanno accettato di restare al servizio. E in ricompensa per il diario, ti cedo la mia nave ‘Twilight’.";
			link.l1 = "Grazie! Me ne ricorderò, puoi contarci!";
			link.l1.go = "SJ_talk_9";
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 46)
			{
				pchar.Ship.Type = GenerateShipHand(pchar, SHIP_CAREERLUGGER, 12, 580, 30, 800, 20000, 16.5, 65.5, 1.6);
			}
			else
			{
				pchar.Ship.Type = GenerateShipHand(pchar, SHIP_SCHOONER, 16, 1900, 50, 1350, 25000, 13.5, 55.0, 1.10);
			}
			pchar.Ship.name = "Twilight";
			SetBaseShipData(pchar);
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 46) pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
			else pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 80;
			pchar.Ship.Crew.Exp.Sailors = 90;
			pchar.Ship.Crew.Exp.Cannoners = 70;
			pchar.Ship.Crew.Exp.Soldiers = 70;
			SetCharacterGoods(pchar, GOOD_BALLS, 100);
			SetCharacterGoods(pchar, GOOD_GRAPES, 100);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			SetCharacterGoods(pchar, GOOD_BOMBS, 100);
			SetCharacterGoods(pchar, GOOD_FOOD, 100);
			SetCharacterGoods(pchar, GOOD_POWDER, 300);
			SetCharacterGoods(pchar, GOOD_WEAPON, 60);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 60);
		break;
		
		case "SJ_talk_8":
			AddMoneyToCharacter(pchar, 15000);
			dialog.text = "Sì, vorrei pagarti per il diario. 15000 pesos – purtroppo non ne ho di più al momento. Regoleremo tutto entro domani.";
			link.l1 = "Non serve. Questo basta. Se tu non fossi arrivato in tempo, non mi sarebbe servito alcun denaro, comunque.";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_9":
			dialog.text = "D'accordo, "+pchar.name+", devo andare. Non torno ancora a Bridgetown. Se mai avrai bisogno di me – chiedi a John. Buona fortuna!";
			link.l1 = "Buona fortuna, Hercule!";
			link.l1.go = "SJ_talk_10";
		break;
		
		case "SJ_talk_10":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-13");
			pchar.questTemp.HWIC.Self = "HuntFleetwood";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "SJ_talk_11":
			dialog.text = "Vorrei offrirti quest’armatura per aver fatto fuori Fleetwood. Ti proteggerà nelle prossime battaglie. Andiamo ora da John. Vuole parlarti e proporti... un affare interessante.";
			link.l1 = "Grazie per il dono. Bene, andiamo...";
			link.l1.go = "SJ_talk_12";
		break;
		
		case "SJ_talk_12":
			DialogExit();
			GiveItem2Character(pchar, "cirass7");//дать вещь
			sld = characterFromId("Merdok");
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetOwnerType(sld);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddQuestRecord("Holl_Gambit", "3-35");
		break;
		
		case "Tonzag_hired":
			dialog.text = "Anch’io vorrei scambiare due parole con voi, capitano. Pensavo d’insegnarvi il mio mestiere, ma adesso vedo che son io a dover imparare da voi. Prendetemi come ufficiale sulla vostra nave — non ve ne pentirete.";
			link.l1 = "Con piacere, Hercule! Benvenuto a bordo!";
			link.l1.go = "Tonzag_hired_1";
			link.l2 = "Hercule, non riesco proprio a vedermi come tuo superiore. Ti ringrazio per la proposta, ma non posso immaginarti come mio sottoposto.";
			link.l2.go = "Tonzag_exit";
		break;
		
		case "Tonzag_hired_1"://Тонзага - в офицеры
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			npchar.greeting = "tonzag_hire";
			NextDiag.CurrentNode = "tonzag_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			LAi_SetImmortal(npchar, false);
			SetCharacterPerk(npchar, "ShipEscape");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;
		
		case "Tonzag_exit":
			dialog.text = "Come desideri, "+pchar.name+"Ci vediamo. Chissà, forse ci incroceremo ancora. È stato un vero piacere collaborare con voi.";
			link.l1 = "Buona fortuna, compare!";
			link.l1.go = "Tonzag_exit_1";
		break;
		
		case "Tonzag_exit_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DialogExit();
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "tonzag_officer":
			dialog.text = "Ascolto, capitano. Che t’hai da dirmi?";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Hercule, sto per dirigermi verso l’antica città indiana di Tayasal e, cosa ancor più bizzarra, il mio cammino passa per una statua di teletrasporto. Vuoi venire con me?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Hercule, dammi il rapporto completo della nave.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Voglio che tu acquisti certe merci ogni volta che attracchiamo.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Sono giunto su vostro ordine, capitano.";
				Link.l2 = "Devo impartirti diversi ordini.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "tonzag_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Ascoltate il mio ordine!";
            Link.l1.go = "stay_follow";
			link.l2 = "Niente per ora. A riposo!";
			link.l2.go = "exit";
			NextDiag.TempNode = "tonzag_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Capitano, perdoni, ma io non m’intendo di numeri e conti. Chieda a van Merden – quello sì che ha il cervello per simili faccende, anche se dubito che lascerebbe mai il suo nido.";
			Link.l1 = "Hai ragione, Hercule. Bah, devo trovarmi un quartiermastro...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Capitano, quand'ero un oste a Barbados compravo solo rum e provviste. E per provviste intendo cibo vero, non delle gallette e carne salata. Mi dispiace, ma non è affar mio.";
			link.l1 = "Forse dovremmo trasformare la mia nave in una taverna... Scherzo, Hercule. Vabbè, ci penso io.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Ti sto ascoltando.";
			Link.l1 = "Si parla di un arrembaggio.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Si tratta della tua nave.";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Niente finora.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "Allora, qual è il tuo desiderio.";
			Link.l1 = "Non abbordare le navi nemiche. Pensa a te stesso e all’equipaggio.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Voglio che abbordi le navi nemiche.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "Dunque, qual è il tuo desiderio.";
			Link.l1 = "Vorrei che tu non scambiassi la tua nave con un'altra dopo l’abbordaggio. Vale troppo.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Quando abbordi le navi nemiche, puoi prendertele per te, se valgono la pena.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Ai vostri ordini.";
			Link.l1 = "A riposo.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Sarà fatto.";
			Link.l1 = "A riposo.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Ai vostri ordini.";
			Link.l1 = "Sarà fatto.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Sarà fatto.";
			Link.l1 = "Rilassati.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		
		case "stay_follow":
            dialog.Text = "Quali sono i tuoi ordini? ";
            Link.l1 = "Resta qui!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Seguimi e non restare indietro!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Cambia il tipo di munizioni.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Scelta del tipo di munizioni:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
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
            dialog.Text = "Ahoy!";
            Link.l1 = "A riposo.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Aye!";
            Link.l1 = "A riposo.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Sei proprio un figlio di buona donna fortunato, capitano. Sono contento d’essermi unito a te quand’eravamo io, tu e John tutti nella stessa barca. Che mi divorino i pescecani, se non ti do manforte in questa faccenda!";
			link.l1 = "Grazie, Hercule! Son lieto che non mi sia sbagliato su di te.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Allora, quand’è che molliamo gli ormeggi?";
			link.l1 = "Un po' più tardi. Ora dobbiamo prepararci per il viaggio.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "23");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Praticamente niente, Capitano. Se fosse affar nostro, ci avrebbero già messi sulla graticola.\nDal momento che non ci hanno portato subito a interrogarci, la faccenda non pare urgente.\nO una trappola, o un ricatto.\nCi lasceranno a bollire qui per qualche giorno senza spiegazioni. Poi verranno con una proposta, e noi la accetteremo.";
			link.l1 = "Esperienza personale?";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "E allora, c’è un modo per farli venire subito con una simile offerta?";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-14.82, 0.92, 2.74, true, -60.00, -5.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Certo. Gruoh una volta fu pagata dai parenti di un morto per risparmiargli le carezze d’addio del boia di Trinidad.\nHa pagato il comandante per il permesso di passeggiare tra le celle. È uso comune—molti soldi vanno ai soldati per poter tormentare chi non può difendersi, senza occhi indiscreti.\nL’uomo è morto in silenzio, senza soffrire. Un lavoro pulito e onorevole.";
			link.l1 = "Gruoh? Chi diavolo sarebbe costui?";
			link.l1.go = "tonzag_jailed_1_1";
		break;
		
		case "tonzag_jailed_1_1":
			dialog.text = "Scusa, capitano. Posto e momento sbagliati.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Possiamo tentare. Aspettiamo l’ora del rancio, e scambierò due parole col guardiacarcere. Vedi, ancora non hanno imparato a perquisire come si deve. Eh...";
			link.l1 = "Che succede?";
			link.l1.go = "tonzag_jailed_2_1";
		break;
		
		case "tonzag_jailed_2_1":
			dialog.text = "Strana sensazione, Capitano. La chiamerei quasi una premonizione. Perdonami, ne parleremo più tardi.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_killed_hunters":
			dialog.text = "Mi sono perso qualcosa, Capitano?";
			link.l1 = "Oh, niente di speciale, solo un altro giorno in mare. Guarda un po’, vecchio pirata! Hai combinato proprio un bel casino qui per me.";
			link.l1.go = "tonzag_killed_hunters_1";
		break;
		
		case "tonzag_killed_hunters_1":
			dialog.text = "Il sangue si lava via con l’acqua fredda, Capitano. Dobbiamo parlare.";
			link.l1 = "Pensi? Non sarebbe male sopravvivere almeno a questa giornata, per cominciare.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_Victory");
		break;
		
		case "tonzag_after_victory_helena":
			dialog.text = "Anche io son lieto di vederti, Rumba. Capitano, non intendo disturbarti, parleremo più tardi.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog1");
		break;
		
		case "tonzag_after_victory_mary":
			dialog.text = "Ehi, Carota. Capitano, non voglio importunare, ne parliamo dopo.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog1");
		break;
		
		case "tonzag_after_victory_alonso":
			dialog.text = "Capitano, non vi disturbo ora, parleremo più tardi.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_drink":
			dialog.text = "Pronto ad ascoltarmi, Capitano?";
			link.l1 = "Era giunta l’ora di scambiare due parole, Hercule. Mi rendo conto solo ora che di te non so praticamente nulla.";
			link.l1.go = "tonzag_drink_1";
		break;
		
		case "tonzag_drink_1":
			dialog.text = "Dunque, è tempo di far conoscenza. Sorvoliamo sulla giovinezza, tanto non c’è nulla da raccontare – un soldato vincente, uno sconfitto, un disertore, un saccheggiatore... sai bene come vanno queste faccende.";
			link.l1 = "A dire il vero, no, ma finora mi sembra tutto piuttosto ordinario.";
			link.l1.go = "tonzag_drink_2";
		break;
		
		case "tonzag_drink_2":
			dialog.text = "Le prospettive dopo una vita così militare erano poche per uno come me: bandito, impiccato, oppure sbirro al servizio della Compagnia Olandese delle Indie Occidentali. Ho scelto l’ultima, come puoi ben capire.";
			link.l1 = "Anche da lì sei scappato, eh?";
			link.l1.go = "tonzag_drink_3";
		break;
		
		case "tonzag_drink_3":
			dialog.text = "Al contrario, lì ho fatto carriera. Ho ricevuto un'offerta per unirmi al reparto d’assalto dei servizi segreti della Compagnia, dove ho conosciuto la mia futura sposa.";
			link.l1 = "D'accordo, finora la storia fila liscia come l'olio... almeno se non ti metti a rimuginare troppo sui modi spicci dei dannati olandesi.";
			link.l1.go = "tonzag_drink_4";
		break;
		
		case "tonzag_drink_4":
			dialog.text = "Non ti arricchirai mai facendo il galantuomo, e la concorrenza si può gestire in mille maniere. Eh già, lavoravamo anche noi con certi... metodi particolari...";
			link.l1 = "Credo di capire dove vuoi arrivare...";
			link.l1.go = "tonzag_drink_5";
		break;
		
		case "tonzag_drink_5":
			dialog.text = "Sì, poteva essere qualsiasi cosa: dalla pirateria all’incendiare magazzini pieni di merci. Alla fine la faccenda venne a galla, e ci sciolsero... almeno sulla carta. Così nacque la Lega, conosciuta e guidata solo dai pochi eletti tra i capi della Compagnia. Per un canaglia delle Antille che valesse qualcosa, restavano due sentieri: la pirateria o la Lega. E la Lega pagava di solito meglio.\nPer lo più la Lega continuava a servire gli olandesi, ma non disdegnava di prendere lavoretti da altri...";
			link.l1 = "Le cose cominciano a schiarirsi...";
			link.l1.go = "tonzag_drink_6";
		break;
		
		case "tonzag_drink_6":
			dialog.text = "La Lega era dietro quella farsa a Tortuga. E poi quell’abbordaggio...";
			link.l1 = "Me lo immaginavo. Ma perché, diavolo?";
			link.l1.go = "tonzag_drink_7";
		break;
		
		case "tonzag_drink_7":
			dialog.text = "Perché nessuno lascia la Lega vivo, e non te la cavi liscia dopo quello che abbiamo combinato laggiù, Capitano. Volevo appendere la sciabola al chiodo, ci ho provato comunque. Come vedi, non è andata troppo bene.";
			link.l1 = "Vuoi dirmi che i tuoi ex compari hanno speso un patrimonio, sacrificato quasi un centinaio di uomini, dato fuoco a una brulotta e messo a rischio una nave da guerra... solo per far fuori te, per aver disertato?";
			link.l1.go = "tonzag_drink_8";
		break;
		
		case "tonzag_drink_8":
			dialog.text = "Ero più di un semplice scarto nella Lega, Capitano. So troppe cose su di loro. Non possono semplicemente lasciarmi andare, e vogliono che sia chiaro, così che nessun altro si azzardi a pensare di mollare il mestiere... Hanno già provato a eliminarmi, tanto tempo fa... Hanno ammazzato mia moglie e mi hanno sfigurato, anche se gli è costato caro. Non c’è lieto fine in questa storia, Capitano. Datemi solo un ordine, e scenderò dalla nave per affrontarli una volta per tutte.";
			link.l1 = "Non dire sciocchezze, Hercule... E che parte ha avuto Lucas Rodenburg in tutto questo? Di certo c’era dentro fino al collo! La tua, o meglio la sua, ‘organizzazione’, la Lega...";
			link.l1.go = "tonzag_drink_9";
		break;
		
		case "tonzag_drink_9":
			dialog.text = "Agenzie diverse, Capitano. È vero, spesso obbedivano alla stessa mano e lavoravano fianco a fianco. Ma gli agenti scelti di Rodenburg colpivano con precisione, mentre la Lega agiva in massa. E ora che fine ha fatto la Lega? Come vedi, non esiste più: io sono qui con te, John Murdock se n’è andato, Longway è scappato, Van Berg riposa in fondo al mare, Rodenburg è stato giustiziato... Eppure dovevo un favore a quel furfante defunto. Mi notò nella Lega e, quando tentai di andarmene, mi tirò fuori da un brutto guaio e mi fece suo vice. Certo, agli altri non piaceva, ma nessuno osava contraddirlo... E poi, per le note vicende, decise di sbarazzarsi di Murdock e di me, ma tu sei intervenuto e mi hai arruolato al tuo servizio. \nCosì ho pensato: 'Ecco la mia seconda occasione per lasciarmi il passato alle spalle...' Hai battuto Rodenburg, la Lega ha perso il suo protettore, il pericolo era passato... Ma, ovviamente, mi sbagliavo... Vecchio scemo... Ma basta così, Capitano. Pensiamo piuttosto a cosa fare ora, se davvero non hai intenzione di sbarcarmi al primo porto.";
			link.l1 = "Non proprio. Suppongo che tu abbia qualche diavoleria in mente?";
			link.l1.go = "tonzag_drink_10";
		break;
		
		case "tonzag_drink_10":
			dialog.text = "Niente di speciale, in verità. Non li stermineremo mai tutti, ma possiamo fargli perdere talmente tanto che non gli convenga più venire a darci la caccia... a me, a noi.";
			link.l1 = "E come facciamo, allora? Hanno un accampamento?";
			link.l1.go = "tonzag_drink_11";
		break;
		
		case "tonzag_drink_11":
			dialog.text = "Una grande fortezza? Difficile. Sarebbe troppo vistosa e rischiosa per la Lega. E quando parlo di perdite, non intendo gente morta – di quella se ne infischiano, ma perdere oro non piace a nessuno. I soldi della Compagnia ormai non gli arrivano più, giusto? Dubito che la Lega si sia trovata un nuovo protettore, quindi devono spremere dobloni da qualche altra parte.";
			link.l1 = "E quale posto sarebbe, di grazia?";
			link.l1.go = "tonzag_drink_12";
		break;
		
		case "tonzag_drink_12":
			dialog.text = "Non saprei, Capitano.";
			link.l1 = "Hercule, ma hai appena detto che ti danno la caccia proprio perché sai troppo!";
			link.l1.go = "tonzag_drink_13";
		break;
		
		case "tonzag_drink_13":
			dialog.text = "Lascia che ci pensi... Forse la Lega sta tramando qualcosa contro gli spagnoli in questo momento. Sono sempre i primi da spennare per bene. A proposito, Rodenburg è sempre andato d’accordo coi grassoni castigliani. A volte mandava i suoi della Lega a lavorare per loro, e proibiva tassativamente di fargli anche solo un graffio, cosa che – tra noi – ai nostri ragazzi non andava proprio giù...";
			link.l1 = "Rapporti amichevoli, dici? E di quel tale Hidalgo e il suo dito, che m’hai fatto trascinare fino alla tua taverna, che ne facciamo?";
			link.l1.go = "tonzag_drink_14";
		break;
		
		case "tonzag_drink_14":
			dialog.text = "Quella era una faccenda a parte, un lavoretto extra. Se hai i sensi di colpa, Capitano, stai tranquillo: quel Don ha avuto ciò che si meritava... Ma io parlo d’altro: dopo la scomparsa del loro padrone, gli uomini della Lega potevano benissimo lasciarsi andare ai propri appetiti e tentare di afferrare una bella fetta della torta spagnola. Grazie agli affari coi castigliani sotto Rodenburg, sanno bene dove e cosa colpire.";
			link.l1 = "Hm... potresti aver ragione. Ma per quanto ne so, nessuno si mette davvero a svaligiare banche spagnole, chi attacca gli spagnoli in mare si affida solo alla Dea Fortuna... Forse dovremmo cercare qualche impresa spagnola? Una fabbrica, magari?";
			link.l1.go = "tonzag_drink_15";
		break;
		
		case "tonzag_drink_15":
			dialog.text = "Supposizione sensata, Capitano... Abbiamo qualche altra pista?";
			link.l1 = "Hm... la nave che ci ha assaltato oggi è andata verso sud...";
			link.l1.go = "tonzag_drink_16";
		break;
		
		case "tonzag_drink_16":
			dialog.text = "È improbabile che il suo capitano ci dia ancora fastidio, ma avrà certo avvertito gli altri che le cose non sono andate secondo i loro piani, e magari trasportato la ciurma altrove. Altro da aggiungere?";
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.KnowMain")) {
				link.l1 = "Sì, ho avuto una chiacchierata amichevole col comandante della prigione di Tortuga... Ha accennato a qualcosa riguardo la terraferma.";
				link.l1.go = "tonzag_drink_know";
			} else {
				link.l1 = "No, nient'altro.";
				link.l1.go = "tonzag_drink_notknow";
			}
		break;
		
		case "tonzag_drink_know":
			dialog.text = "Eccellente, Capitano! Sud, terraferma, spagnoli – vuol dire che li troveremo in fretta. Si salpa? E grazie per aver dato orecchio alla mia storia.";
			link.l1 = "Eh già, abbiamo proprio fatto una bella chiacchierata tu ed io... Alziamo le ancore!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_drink_notknow":
			dialog.text = "Non è molto, ma per gente come noi basta e avanza. Che ne dici, scendiamo a sud? Vediamo se becchiamo qualche impresa commerciale spagnola? E grazie per aver ascoltato la mia storia.";
			link.l1 = "Eh già, ci siamo proprio aperti l’un l’altro… Allora, issiamo le vele!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_dead":
			dialog.text = "Guarda, Capitano. Così fanno i loro sporchi giochi.";
			link.l1 = "E anche tu sgobbavi in quel modo?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Andiamo, vediamo cosa c'è dentro.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_AfterDead");
		break;
		
		case "tonzag_afterminefight":
			dialog.text = "Una faccenda lurida, Capitano. Abbiamo ripulito questa tana, ma di certo non sarà l’ultima...";
			link.l1 = "E la miniera, Hercule?! Tutta quella gente là fuori?! Pure loro sono stati 'sgomberati'! E che diavolo voleva dire quel furfante?";
			link.l1.go = "tonzag_afterminefight_1";
		break;
		
		case "tonzag_afterminefight_1":
			dialog.text = "Let's discuss this later, Captain. Their commander survived; we need to interrogate him.";
			link.l1 = "E se non ne sapesse un accidente?";
			link.l1.go = "tonzag_afterminefight_2";
		break;
		
		case "tonzag_afterminefight_2":
			dialog.text = "He knows something. Think about it - they were waiting for us, carried out all the gold, and eliminated witnesses. That means they had a plan. I want to take a look around here, and later I'll bring the scoundrel to the ship myself. You should also keep an eye out; perhaps they were too hasty and missed something.";
			link.l1 = "Va bene, ma appena torniamo sulla nave dobbiamo far due chiacchiere serie!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			locations[FindLocation("LosTeques_town")].locators_radius.reload.gate_back = 1.0;
			DeleteAttribute(&locations[FindLocation("LosTeques_town")], "locators_radius.reload.reload1_back");
			AddDialogExitQuestFunction("Tonzag_PrepareJournal");
		break;
		
		case "tonzag_in_hold":
			dialog.text = "Buone notizie, Capitano.";
			link.l1 = "Non vedo nulla di buono nella nostra situazione, Hercule. Andiamo, dobbiamo parlare in privato.";
			link.l1.go = "tonzag_in_hold_1";
		break;
		
		case "tonzag_in_hold_1":
			dialog.text = "Ah, così stanno le cose, eh? Sissignore, Capitano.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_EnterAlonso");
		break;
		
		case "tonzag_drink_again":
			dialog.text = "Vedo che ci aspetta una conversazione seria, Capitano.";
			link.l1 = "Sì, e sarò io a parlare. Prima di tutto, non pensi che si stia creando una certa tendenza? Una scia di cadaveri ci segue ovunque andiamo! Prima ti becchi una scarica di mitraglia nella pancia, e il giorno dopo più di cento persone, buone o cattive che siano, crepano in... non posso nemmeno chiamarla battaglia navale! Un villaggio è stato raso al suolo appena qualche giorno fa, e oggi ci abbiamo messo del nostro facendo a pezzi un branco di poveracci nelle miniere.";
			link.l1.go = "tonzag_drink_again_1_1";
		break;
		
		case "tonzag_drink_again_1_1":
			dialog.text = "";
			link.l1 = "Naturalmente, m'inquieta il pensiero che il mucchio si trasformi in una montagna domani, ma ciò che davvero mi fa tremare è che tutto questo sangue scorra per colpa d’un solo uomo. E quell’uomo occupa un posto importante nella mia ciurma!";
			link.l1.go = "tonzag_drink_again_1";
		break;
		
		case "tonzag_drink_again_1":
			dialog.text = "";
			link.l1 = "In secondo luogo, mi hai mentito, Hercule. Nessun disertore vale tutta la fatica che i tuoi ex compari stanno facendo per farti fuori. Che cosa urlava il nostro prigioniero nelle miniere? Traditore? Porto Bello? Gruoh? Hai combinato qualcosa, Hercule, e stavolta voglio la verità.";
			link.l1.go = "tonzag_drink_again_2";
		break;
		
		case "tonzag_drink_again_2":
			dialog.text = "Truth? The truth is, Captain, that I did desert, along with my wife Gruoh. Madame Tonzag didn't want to leave the League; she loved that life, but she loved me even more. We were supposed to take care of a Spanish hidalgo, but he made a better offer. It was our chance, and we both agreed to go into his service. Of course, the League thought we perished on a mission and sent a second group to Porto Bello to finish the job and seek revenge.";
			link.l1 = "E li hai fatti fuori tutti quanti?";
			link.l1.go = "tonzag_drink_again_3";
		break;
		
		case "tonzag_drink_again_3":
			dialog.text = "Prima hanno fatto fuori Gruoh e mi hanno sfigurato. L'hidalgo non voleva più saperne di me e mi ha sbattuto fuori. Fu allora che Rodenburg mi trovò...";
			link.l1 = "E come dovrei fidarmi di te adesso? Hai disertato l’esercito, tradito la Lega, e ammazzato i tuoi stessi compagni! Quando verrà il momento giusto, tradirai anche me?";
			link.l1.go = "tonzag_drink_again_4";
		break;
		
		case "tonzag_drink_again_4":
			dialog.text = "Sì, ho disertato, ho spezzato il contratto, ho mandato all’altro mondo una ventina di compari della Lega. Ma la lezione l’ho imparata, Capitano. E poi, un morto non può tradire nessuno, e io sono morto da un pezzo, fin da Porto Bello. Forse è per questo che ammazzarmi adesso è un’impresa maledettamente ardua.";
			link.l1 = "Basta così per oggi. Mi pare che tu non mi stia dicendo proprio tutto.";
			link.l1.go = "tonzag_drink_again_5";
		break;
		
		case "tonzag_drink_again_5":
			dialog.text = "Mi occupo io del prigioniero, oppure vuoi metterci becco anche tu?";
			link.l1 = "Andiamo. Lo interrogherò io stesso.";
			link.l1.go = "tonzag_drink_again_hold";
			link.l2 = "No, queste faccende non fanno per me. Vediamoci nella mia cabina fra mezz’ora!";
			link.l2.go = "tonzag_drink_again_cabin";
		break;
		
		case "tonzag_drink_again_hold":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToHold");
		break;
		
		case "tonzag_drink_again_cabin":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin");
		break;
		
		case "tonzag_hold":
			dialog.text = "Chi comanda adesso? Arno?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog1");
		break;
		
		case "tonzag_hold_1":
			dialog.text = "Quella feccia è salita al potere? Non ci hai messo molto a ridurti a una banda qualsiasi di mascalzoni...";
			link.l1 = "Chi è Austin?";
			link.l1.go = "tonzag_hold_2";
		break;
		
		case "tonzag_hold_2":
			dialog.text = "La banda di Austin era famosa per attirare capitani indipendenti nei boschi, farli a pezzi e ripulirne i cadaveri da ogni moneta o gingillo. Un affare redditizio, e di avventurieri qui non manca — nessuno si lamentava. Ma si sono imbattuti in un capitano tosto, così dovettero rifugiarsi sotto l’ala della Compagnia. Da allora lo teniamo al guinzaglio, e lo lasciamo libero solo quando serve risolvere le faccende in modo rapido e senza troppe storie.";
			link.l1 = "Dubito di poter strappare un accordo con un tipo simile.";
			link.l1.go = "tonzag_hold_3";
		break;
		
		case "tonzag_hold_3":
			dialog.text = "Questo è certo. Se lui e la sua marmaglia comandano adesso, presto la Lega diventerà solo un’altra banda di mascalzoni.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog3");
		break;
		
		case "tonzag_after_hold":
			dialog.text = "Abbiamo avuto una conversazione interessante.";
			link.l1 = "Vorrei proprio sapere quanto di tutto ciò sia vero... E il massacro di Porto Bello? Se non mentiva, significa che l’ultima volta che abbiamo parlato tu, ancora una volta, hai tralasciato qualche dettaglio importante nella tua illustre biografia.";
			link.l1.go = "tonzag_after_hold_1";
		break;
		
		case "tonzag_after_hold_1":
			dialog.text = "Faceva un caldo infernale a Porto Bello, Capitano. Ho lottato per la mia pelle, per quella del mio padrone e per quella della mia donna. Non avevo il tempo di contare i caduti né di piangere ogni poveraccio che finiva in mezzo alla strada al momento sbagliato.";
			link.l1 = "In quest’ordine di importanza?";
			link.l1.go = "tonzag_after_hold_2";
		break;
		
		case "tonzag_after_hold_2":
			dialog.text = "No, certo che no. Prima la sua. Sempre.";
			link.l1 = "Che ne dici? Ce ne andiamo a Caracas?";
			link.l1.go = "tonzag_after_hold_3";
		break;
		
		case "tonzag_after_hold_3":
			dialog.text = "Io, personalmente, non lo farei, Capitano. E ti consiglierei di lasciar perdere anche tu. Per la Lega non sei più un nemico, e io a loro non interesso, finché resto al tuo servizio. Inoltre, ho una brutta sensazione che mi rode dentro... Se ci andiamo, finirà male. Malissimo. Questa storia non avrà un lieto fine. Ma io resterò al tuo fianco fino all’ultimo, Capitano.";
			link.l1 = "Ci penserò su.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_hold_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_hold_4":
			dialog.text = "";
			link.l1 = "A proposito, avevi ragione – non sono riusciti a ripulire per bene la miniera. Guarda.";
			link.l1.go = "tonzag_after_hold_5";
		break;
		
		case "tonzag_after_hold_5":
			dialog.text = "Il diario di un ufficiale... cifrato, ma è un vecchio codice, lo conosco\nNulla di interessante, pare. Era il diario del nostro prigioniero. Ora è chiaro perché fosse così loquace. Guarda qui – indizi su un tesoro nascosto! Quel furfante progettava chiaramente di ritirarsi e filarsela in qualsiasi momento!";
			link.l1 = "E dove si trova questo covo nascosto?";
			link.l1.go = "tonzag_after_hold_6";
		break;
		
		case "tonzag_after_hold_6":
			dialog.text = "Sai bene quell’isola, Capitano. Fu nelle sue acque che hai mandato Van Berd a dormire coi pesci.";
			link.l1 = "D'accordo, non è troppo lontano, dunque andiamo a dare un'occhiata. Quanto a Caracas, non ho ancora deciso, ma credo che abbiamo un mese di tempo.";
			link.l1.go = "tonzag_after_hold_7";
		break;
		
		case "tonzag_after_hold_7":
			dialog.text = "Come volete, Capitano. Resto al vostro fianco fino alla fine.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_after_drink":
			dialog.text = "It's done, Captain. Austin is currently in Caracas; I think we have a month.";
			link.l1 = "Prima di tutto, che ha detto il prigioniero? Chi diavolo è questo Austin? E perché dovremmo andare a Caracas?";
			link.l1.go = "tonzag_after_drink_1";
		break;
		
		case "tonzag_after_drink_1":
			dialog.text = "La banda di Austin era rinomata per attirare i capitani liberi nei boschi, farli a pezzi e ripulire i loro cadaveri da ogni moneta o gingillo. Un affare redditizio, e di avventurieri qui non manca mai, quindi nessuno si lamentava. Ma una volta hanno sbagliato с капитаном, così dovette rifugiarsi sotto l’ala della Compagnia. Lo tenevamo al guinzaglio e lo lasciavamo libero solo quando serviva risolvere qualche faccenda in fretta e senza troppi complimenti.";
			link.l1 = "Dubito di poter concludere un accordo con un tipo del genere.";
			link.l1.go = "tonzag_after_drink_2";
		break;
		
		case "tonzag_after_drink_2":
			dialog.text = "Questo è poco ma sicuro. Se lui e la sua marmaglia ora comandano, presto la Lega non sarà altro che una banda di marmittoni. Ma io non metterei piede a Caracas, Capitano.";
			link.l1 = "Davvero? Hai il cuore in gola?";
			link.l1.go = "tonzag_after_drink_3";
		break;
		
		case "tonzag_after_drink_3":
			dialog.text = "Non è così, Capitano. Prima di tirare le cuoia, il prigioniero ha svelato che non siete più nemico della Lega, e io non gli interesso, almeno finché resto al vostro servizio. Pare che la Lega abbia trovato un nuovo potente protettore che ha ordinato di lasciarci in pace.\nE Caracas... sento un brutto presentimento in fondo alle viscere... Se ci andiamo, finirà male. Molto male. Questa storia non avrà un lieto fine. Ma io vi seguirò fino all’ultimo, Capitano.";
			link.l1 = "Ci penserò su. Certo, mi piacerebbe mettere la parola fine a questa storia, ma forse hai ragione tu. Dubito che dopo gli avvenimenti della scorsa settimana avranno il coraggio di rifarsi vivi con noi.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_drink_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_drink_4":
			dialog.text = "";
			link.l1 = "A proposito, avevi ragione – non sono riusciti a ripulire la miniera a dovere. Guarda.";
			link.l1.go = "tonzag_after_drink_5";
		break;
		
		case "tonzag_after_drink_5":
			dialog.text = "Il diario d’un ufficiale... cifrato, ma è un vecchio codice, lo riconosco\nNulla di interessante, sembra. Era il diario del nostro prigioniero. Guarda qui – indizi su un tesoro nascosto! Quel furfante si preparava a ritirarsi e a svignarsela in qualsiasi momento!";
			link.l1 = "E dove si trova questo covo nascosto?";
			link.l1.go = "tonzag_after_drink_6";
		break;
		
		case "tonzag_after_drink_6":
			dialog.text = "Conosci quell’isola, Capitano. In quelle acque hai mandato Van Berd a dormire con i pesci.";
			link.l1 = "D'accordo, non è troppo lontano, quindi andiamo a dare un'occhiata. Quanto a Caracas, non ho ancora deciso, ma credo che abbiamo un mese.";
			link.l1.go = "tonzag_after_drink_7";
		break;
		
		case "tonzag_after_drink_7":
			dialog.text = "Come desideri, Capitano.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_church":
			dialog.text = "Frena un po', Capitano. Ci vado da solo.";
			link.l1 = "And why is that? Feeling heroic now? It's too late; you've made this mess, but we have to clean it together.";
			link.l1.go = "tonzag_church_1";
		break;
		
		case "tonzag_church_1":
			dialog.text = "Non devi pagare per i miei peccati, Capitano. Avevi ragione tu: ovunque metta piede, scorre sangue innocente e la morte mi segue. Se varchiamo insieme la soglia di quella chiesa, sarà un altro Porto Bello — e io non voglio portare ancora quella dannazione.";
			link.l1 = "Che diavolo è successo laggiù?";
			link.l1.go = "tonzag_church_2";
		break;
		
		case "tonzag_church_2":
			dialog.text = "Un massacro. Volevo ritirarmi, Capitano. Prendere l’oro, mia moglie e tornare a Carcassonne. Sapevo che la Lega avrebbe mandato altra feccia a finire il mio lavoro, così ho preso un bell’anticipo dal nuovo padrone. Restava solo mettere la ronda cittadina contro i miei vecchi compari e il nuovo mandante. Nel trambusto, sarei sparito col malloppo e, se il tempo lo permetteva, magari avrei alleggerito pure qualche grasso signore di Porto Bello.";
			link.l1 = "Bel piano, anche se io l’avrei fatto a modo mio. Troppa roba che può andare a ramengo.";
			link.l1.go = "tonzag_church_2a";
			link.l2 = "Non sono certo un santo, ma il tuo modo di fare fa rabbrividire persino me. Mi stupisce che tu non mi abbia ancora pugnalato alle spalle, come hai fatto con la Lega, con l'Hidalgo e persino con tua moglie.";
			link.l2.go = "tonzag_church_2a";
		break;
		
		case "tonzag_church_2a":
			dialog.text = "Everything that could go wrong, did go wrong. Shooting a three-pounder towards the governor's palace was a mistake. It barely scratched the governor himself, but his beautiful daughter, as I hear, had to have both her legs amputated below the knees to save her life. The response was horrific - a blood bath; great many people perished, Captain. Now you're looking at the last living witness to those events, and not long ago, you cut down another one yourself.";
			link.l1 = "Spiegati.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_2b":
			dialog.text = "Se Madame Tonzag fosse ancora tra i vivi, ti avrei venduto senza batter ciglio, Capitano. Sono un morto che cammina, ti seguo solo perché non ho più dove andare in questo mondo. Ora davanti a te c’è l’ultimo testimone rimasto di quegli eventi, e poco tempo fa sei stato tu stesso a far fuori un altro.";
			link.l1 = "Spiegati.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_3":
			dialog.text = "Perdonami, Capitano, se non ti ho detto tutto fin dall’inizio. Quando ci siamo incontrati, ti ho preso per un altro furfante come me. E sai la prima cosa che ho fatto? Ti ho mandato a ripulire i miei casini – ad ammazzare quel Don spagnolo che all’inizio non volevo uccidere, ma poi ho deciso di tradire. Quel Hidalgo, Rodriguez...";
			link.l1 = "E per quale diavolo motivo ti serviva il suo dito?";
			link.l1.go = "tonzag_church_4";
		break;
		
		case "tonzag_church_4":
			dialog.text = "Niente trucchi, Capitano. Era solo una prova. Ogni anno arruoliamo dozzine di giovani filibustieri come te. Solo pochi superano il primo controllo d’onestà, e pure quelli crepano alle prime missioni. Non dovevi uscire vivo dall’affare col diario di Fleetwood. Avevo intenzione di entrare nella casa, finire i superstiti e prendermi il registro.";
			link.l1 = "Se la memoria non m’inganna, la storia prese una piega un tantinello diversa.";
			link.l1.go = "tonzag_church_5";
		break;
		
		case "tonzag_church_5":
			dialog.text = "Così è stato, Capitano. Non so cosa mi abbia spinto ad aiutarti, ma hai affrontato le Volpi con una tale sete di vita che persino io mi sono lasciato trascinare, seppur per un attimo. Alla fine, senza volerlo, mi hai salvato tu. Non mi devi nulla, Capitano. E non ti lascerò entrare laggiù. Questa è la mia faccenda, la mia redenzione.";
			link.l1 = "Come vuoi, Hercule. Fa male perdere un uomo di spada simile, ma tu ti sei perso molto tempo fa, e non vali più nemmeno una goccia di sangue versato. Anche tu non mi devi nulla, e spero che tu trovi redenzione in quella tua chiesetta.";
			link.l1.go = "tonzag_church_bad";
			link.l2 = "Bel discorso, Hercule. Vai all'inferno! Se non l’hai capito, i tuoi guai ormai sono anche miei. Sei il mio ufficiale, e solo io deciderò se meriti il perdono o no. Quindi ti tocca restare ancora con noi e guadagnarti la redenzione col valore, facendo parte della mia ciurma!";
			link.l2.go = "tonzag_church_good";
		break;
		
		case "tonzag_church_bad":
			dialog.text = "Grazie di tutto, Capitano. Addio!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchBad");
		break;
		
		case "tonzag_church_good":
			dialog.text = "Aye aye, Capitano!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchGood");
		break;
		
		case "tonzag_afterchurchfight":
			dialog.text = "Ne ho visti di mascalzoni nella mia vita, Capitano, ma è la prima volta che qualcosa mi ha gelato il sangue. Dimmi un po': se un mostro piccolo ne uccide uno più grande, questo lo redime in qualche modo?";
			link.l1 = "Allungano il rum con acqua? Dimmi quando lo scopri. Andiamo, qui abbiamo finito.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ResetTonzag");
		break;

	}
}