
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
// ГРИФФОНДОР -->
		case "FireBrigade_fra":
			dialog.text = GetSexPhrase("", "Una donna... e capitano! Ora ho visto tutto. Mademoiselle, siete incantevole. Peccato che la vostra bellezza abbia portato tanta sventura alla Corona di Francia\n") + "Così finiscono tutti gli ordini di Poincy. Uno in prigione. L’altro—o si unisce a lui, o cadrà oggi in battaglia.";
			link.l1 = "È chiaro che non è il tuo posto. Perché mandare un ufficiale così brillante e una nave così bella a fare il lavoro sporco di un cacciatore di taglie?";
			link.l1.go = "FraOff_1";
		break;

        case "FraOff_1":
			dialog.text = "Gli ordini non si discutono, si eseguono. Se ogni capitano scegliesse quali ordini valgono la pena—non avremmo una marina.";
			link.l1 = "Dillo ai tuoi uomini.";
			link.l1.go = "FraOff_2";
        break;

        case "FraOff_2":
			dialog.text = "Mi hai messo all’angolo e cerchi di spezzare la mia lealtà e il mio giuramento. È un colpo basso, date le circostanze. Finiamola con le spade, non con le parole!";
			link.l1 = "(Carisma) C’è una terza via. Smetti di fare il lavoro sporco che non è degno di un ufficiale. Unisciti a me—ti mostrerò un altro mondo.";
			link.l1.go = "FraOff_HireCheck";
            link.l2 = "Allora, alle armi!";
			link.l2.go = "FraOff_ExitFight";
        break;

        case "FraOff_HireCheck":
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 80)
            {
                notification("Abilità insufficiente (80)", SKILL_LEADERSHIP);
                dialog.text = "I traditori vengono trattati allo stesso modo ovunque. E io non lo diventerò.";
                link.l1 = "Hai avuto la tua occasione, e l’hai persa. In guardia!";
                link.l1.go = "FraOff_ExitFight";
                break;
            }
            notification("Controllo superato", SKILL_LEADERSHIP);
            dialog.text = "Ho giurato fedeltà alla corona, non a burocrati pomposi che ci mandano a morire per coprire i loro errori. Ma tu—sei il nemico del mio re, e non posso ignorarlo.";
			link.l1 = "Potrei espiare i miei peccati contro il tuo paese anche domani—basta pagare l’intermediario giusto. Questo dice più dei tuoi superiori che di me.";
			link.l1.go = "FraOff_Sucess";
        break;

        case "FraOff_Sucess":
			dialog.text = "È vero. E sono stanco di sopportarlo. Sono pronto a servire sotto il tuo comando, se prometti di lasciare in pace i francesi.";
			link.l1 = "Non so chi incontreremo, e non posso promettere nulla. Ma prometto di essere ragionevole. Benvenuto nell’equipaggio, ufficiale " + NPChar.name + "!"; // своего имени он вообще-то не называл
			link.l1.go = "FraOff_Hired";
        break;

        case "FraOff_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
        break;

        case "FraOff_Hired":
            AddBrigadierOfficer(sld, NPChar);
            DialogExit();
        break;

// ЭЛЬ КАСАДОР -->
		case "FireBrigade_spa":
            // to_do: чек нуля?
			dialog.text = "Ecco il nemico pubblico. Spero che tu sia orgoglioso di questo titolo, pirata. Te lo sei guadagnato con fatica\nSecondo la Casa de Contratación, hai affondato " + (Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0)) + " navi sotto la bandiera della Corona spagnola. E oggi la mia splendida nave si aggiungerà a questa lista" + GetSexPhrase(".","\nGuai alla flotta spagnola! Abbiamo sopportato malattie, favoritismi, tradimenti... Ma essere sconfitti da una donna?");
			link.l1 = "Sei rimasto solo, il tuo equipaggio è morto. E anche tu, solo che non te ne sei ancora reso conto.";
			link.l1.go = "Alonso_1";
			if(Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0) < 1)
			{
				Achievment_Set("ach_CL_159")
			}
		break;

		case "Alonso_1":
			dialog.text = "Peccato che non sia stato de Alba a ricevere questo incarico. Avrebbe fatto meglio. Ma proverò comunque a finire il lavoro.";
			link.l1 = "Sei un vero figlio della tua patria. Preparati a incontrare i suoi eroi, señor.";
			link.l1.go = "Alonso_2";
			link.l2 = "Il cacciatore è diventato preda. Tutti i tuoi discorsi non sono serviti a nulla—vecchi come il mondo.";
			link.l2.go = "Alonso_3";
		break;

		case "Alonso_2":
            ChangeCharacterComplexReputation(PChar, "nobility", 5);
			dialog.text = "Grazie per questa pausa, ma ora parlerà la mia spada.";
			link.l1 = "Alle armi!";
			link.l1.go = "Alonso_ExitFight";
		break;

        case "Alonso_3":
            ChangeCharacterComplexReputation(PChar, "nobility", -5);
			dialog.text = "Grazie per questa pausa, ma ora parlerà la mia spada.";
			link.l1 = "Preparati a morire!";
			link.l1.go = "Alonso_ExitFight";
		break;

        case "Alonso_ExitFight":
        	SetCharacterPerk(NPChar, "Rush");
            ActivateCharacterPerk(NPChar, "Rush");
            PlaySound("Ambient\Tavern\glotok_001.wav");
            PlaySound("Types\" + LanguageGetLanguage() + "\warrior03.wav");
            SendMessage(NPChar, "lfffsfff", MSG_CHARACTER_VIEWSTRPOS, 0.0, 0.0, 0.1, XI_ConvertString("Rampage"), 255.0, 30.0, 30.0);
            NPChar.Unpushable = "";
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

// ХИМЕРА -->
        case "FireBrigade_eng":
            // to_do: ты-вы у элен
            dialog.text = GetSexPhrase(PChar.Name + "! Il tuo nome compare così spesso nei rapporti che sembra che ci conosciamo da sempre", "Signorina McArthur! Il suo protettore sa cosa sta facendo? Ah, non importa. Sono sicuro che sarà il mio prossimo incarico") + "\nSei fortunato: ai miei capi piace mandare ordini urgenti che contraddicono i precedenti. Se non fossi impegnato a sistemare la vecchia squadra di Antigua... Basta. Mi stai distraendo dal vero lavoro.";
			link.l1 = "Anche tu mi distrai.";
			link.l1.go = "Cortny_ExitFight";
		break;

        case "Cortny_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("KnippelAppearance");
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
		break;

        case "Kneepel":
            dialog.text = "Palla incatenata a poppa, quasi me la perdevo! Se le mie vecchie ossa fossero state un po’ più svelte, avrei mandato quel bastardo all’inferno da solo. Grazie, capitano. E anche dal mio defunto protettore—grazie!";
			link.l1 = "Chi sei? Un prigioniero? È stata la mia ciurma a liberarti?";
			link.l1.go = "Kneepel_1";	
		break;

        case "Kneepel_1":
            dialog.text = "Charlie Knippel in persona. Il miglior cannoniere della marina inglese!";
			link.l1 = "Courtney ha detto che ci ha messo tanto a trovarti. Che è successo?";
			link.l1.go = "Kneepel_2";	
		break;

        case "Kneepel_2":
            dialog.text = "Per molti anni ho servito un coraggioso capitano inglese di nome Richard Fleetwood. Abbiamo combattuto molte battaglie insieme, per vera passione verso la marina inglese. Ma un giorno tutto è cambiato\nI capi di Londra ci hanno usati come pedine. Abbiamo attaccato i nostri. Abbiamo sporcato le nostre uniformi ripulendo i guai degli altri. E ora tocca a noi...";
			link.l1 = "Non ti giudico. La vita è complicata, soprattutto se non sei padrone del tuo destino.";
			link.l1.go = "Kneepel_2_good";
            link.l2 = "Diresti che le ombre dei vecchi peccati ti hanno finalmente raggiunto?";
			link.l2.go = "Kneepel_2_bad";
		break;

        case "Kneepel_2_good":
            dialog.text = "Non mi pento di aver servito il mio paese. Solo... fa male, capitano. Soprattutto per il mio protettore e la sua povera moglie.";
			link.l1 = "E adesso?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_2_bad":
            TEV.NoKneepel = "";
            dialog.text = "Risparmiami le frecciatine... Abbiamo già pagato abbastanza per i nostri peccati!";
			link.l1 = "E adesso?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_3":
            dialog.text = "Ora sono un uomo senza nome e senza patria. Potrei andare ovunque, ma per ora non c’è dove andare. E nessuno con cui andare. I cannonieri servono ovunque, ma non tutte le navi hanno cannoni.";
			link.l1 = "Vieni con me. Non posso dire di avere il miglior rapporto con la marina inglese, ma rispetto i suoi migliori uomini.";
            if(!CheckAttribute(&TEV, "NoKneepel"))
                link.l1.go = "Kneepel_3_good";
            else
                link.l1.go = "Kneepel_3_bad";
            link.l2 = "Ho i cannoni. Se sei davvero così bravo, ci sarà sempre posto per un vero professionista nella mia ciurma.";
			link.l2.go = "Kneepel_3_bad";
		break;

        case "Kneepel_3_good":
            dialog.text = "A casa mi aspetta la forca, lo stesso dagli spagnoli e dagli olandesi, e i francesi non mi piacciono. Ma tu, a quanto pare, hai bisogno di un buon cannoniere. Ci sto, capitano. Andrò in cabina appena possibile. Passa a trovarmi un giorno, brinderemo con le palle incatenate.";
			link.l1 = "Benvenuto a bordo.";
			link.l1.go = "Kneepel_Hired";	
		break;

        case "Kneepel_3_bad":
            dialog.text = "No, grazie. Preferisco requisire una scialuppa e sparire nel buco più profondo dell’arcipelago. Grazie per avermi salvato, capitano, e addio.";
			link.l1 = "...";
			link.l1.go = "Kneepel_Escape";	
		break;

        case "Kneepel_Escape":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.lifeday = 0;
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

        case "Kneepel_Hired":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
            NPChar.Dialog.CurrentNode = "Knippel_officer";
            NPChar.quest.OfficerPrice = sti(PChar.rank)*200; // Артефакт
            npchar.quest.meeting = true;
            NPChar.OfficerImmortal = true;
            NPChar.Health.HP    = 60.0;
            NPChar.Health.maxHP = 60.0;
            NPChar.OfficerWantToGo.DontGo = true;
            NPChar.loyality = MAX_LOYALITY;
            NPChar.Payment = true;
            NPChar.DontClearDead = true; 
            SaveCurrentNpcQuestDateParam(NPChar, "HiredDate");
            AddPassenger(pchar, NPChar, false);
            SetCharacterRemovable(NPChar, true);
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

// МЕЙФЕНГ -->
        case "FireBrigade_hol":
			dialog.text = "Non sei tu quello che doveva arrivare qui. Meifeng è la zanna della Compagnia. Il mio squadrone è la lama che punisce. Li hai sconfitti. Da solo. Questo... non succede spesso.";
			link.l1 = "Ti hanno mandato a darmi la caccia come fossi una bestia. E ho combattuto—come una bestia in trappola. Quando si deve combattere o morire, la mente si fa chiara. Alla fine resta solo una domanda: Riuscirò ad arrivare alla cabina della leggendaria xebec—oppure no.";
			link.l1.go = "Longway_1";
		break;

		case "Longway_1":
			dialog.text = GetSexPhrase("", "Strano—vedere una donna in una battaglia così. Nell’Impero di Mezzo le donne non comandano flotte. Ma tu non sei da meno. Forse fai anche più paura\n") + "Sapevi chi comandava? Mi aspettavi?";
			link.l1 = "Sì. Meifeng è una nave con una storia. Quando ho incrociato la strada degli olandesi, sapevo che prima o poi ti avrebbero mandato sulle mie tracce. Sarebbe stata una fine onorevole... ma guarda come è andata a finire.";
			link.l1.go = "Longway_2";
		break;

		case "Longway_2":
			dialog.text = "Conoscere il nemico e se stessi è la chiave della vittoria. Hai fatto la tua scelta. Hai affrontato il mio squadrone alle tue condizioni. Eri pronto a morire. Ma hai vinto. Ora la mia vita è nelle tue mani. Perché non finisci il lavoro?";
			link.l1 = "(Carisma) Perché non vedo senso nell’affondare un capitano leggendario solo per le ambizioni della Compagnia. Sono stato al tuo posto—una pedina. Ho servito interessi altrui, eseguito ordini altrui. Ti offro quello che una volta ho scelto io: la libertà.";
            if (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP) >= 50)
                link.l1.go = "Longway_Success";
            else
                link.l1.go = "Longway_Failed";
            link.l2 = "Perché ogni capitano merita l’ultima parola. In guardia!";
			link.l2.go = "Longway_ExitFight";
		break;

		case "Longway_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

		case "Longway_Failed":
            notification("Abilità insufficiente (50)", SKILL_LEADERSHIP);
			dialog.text = "La libertà non è qualcosa che si riceve. È qualcosa che si prende. E non tutti quelli che parlano di scelta sanno offrirla davvero. Ci sono strade che non si possono evitare. Ci sono ordini che non si possono lasciare incompiuti. La mia strada è qui. Il mio ordine è resistere fino alla fine.";
			link.l1 = "Quindi scegli la morte?";
			link.l1.go = "Longway_Failed_over";
		break;

		case "Longway_Failed_over":
			dialog.text = "No. Scelgo di restare me stesso.";
			link.l1 = "In guardia!";
			link.l1.go = "Longway_ExitFight";
		break;

		case "Longway_Success":
            notification("Controllo superato", SKILL_LEADERSHIP);
			dialog.text = "Non sei come Rodenburg. Per lui ero solo uno strumento. Per te sono un pari. Sacrificarsi non è una virtù. Sono pronto ad ascoltare le tue condizioni.";
			link.l1 = "È semplice.  Sii il mio navigatore sulla mia nave ammiraglia. Oppure, se preferisci, avrai la tua nave e navigherai sotto la mia bandiera. Non dovrai più ripulire i guai della Compagnia né nascondere i loro scheletri nell’armadio. Sono libero—e ti offro di condividere questa libertà con me.";
			link.l1.go = "Longway_Success_over";
		break;

		case "Longway_Success_over":
			dialog.text = "Ho visto tanto: sangue, oro, tradimenti. La Compagnia paga—ma non rispetta. Ti dà una nave—ma ti tiene in catene. Tu... dai una scelta. Se manterrai la parola—Longwei non sarà più un cacciatore agli ordini altrui. Sarà un uomo. Un capitano. Oppure—al fianco di un capitano che sa dove andare.";
			link.l1 = "Benvenuto nell’equipaggio, navigatore Longwei.";
			link.l1.go = "Longway_Hired";
		break;

		case "Longway_Hired":
            sld = GetCharacter(NPC_GenerateCharacter("Longway_FP", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
			sld.name = StringFromKey("QuestsUtilite_42");
			sld.lastname = StringFromKey("QuestsUtilite_43");
			sld.greeting = "Longway";
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.currentnode = "Longway_officer";
			sld.rank = 20;
			sld.money = 5000;
			SetSelfSkill(sld, 45, 45, 45, 40, 50);
			SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
			SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
			LAi_SetHP(sld, 250, 250);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "SailingProfessional");
            sTemp = GetGeneratedItem("blade_41");
            GiveItem2Character(sld, sTemp);
            EquipCharacterbyItem(sld, sTemp);
            sTemp = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
            if(sTemp != "")
            {
                GiveItem2Character(sld,   sTemp);
                EquipCharacterbyItem(sld, sTemp);
                sTemp = LAi_GetCharacterBulletType(NPChar, GUN_ITEM_TYPE);
                LAi_SetCharacterBulletType(sld, sTemp);
                LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, sTemp);
                sTemp = LAi_GetCharacterGunpowderType(NPChar, GUN_ITEM_TYPE);
                if(sTemp != "") AddItems(sld, sTemp, 30 + rand(20));
            }
			TakeNItems(sld, "potion2", 1);
            sld.quest.meeting = true;
			sld.quest.OfficerPrice = sti(pchar.rank)*200; // Артефакт
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.OfficerImmortal = true;
			sld.Health.HP    = 60.0;
			sld.Health.maxHP = 60.0;
            sld.CanTakeMushket = true;
			SetCharacterPerk(sld, "ShipEscape");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

            NPChar.lifeday = 0;
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
            LAi_SetActorType(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);

            AddDialogExitQuest("pchar_back_to_player");
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;
	}
}

// TO_DO
void AddBrigadierOfficer(ref sld, ref NPChar)
{
    string sTemp = NationShortName(NPChar.nation);
    sld = GetCharacter(NPC_GenerateCharacter("FraBrigadier", NPChar.model, "man", NPChar.model.animation, 30, FRANCE, -1, false, "quest"));
    float num = 1.0;
    switch (MOD_SKILL_ENEMY_RATE)
	{
		case  1: num = 0.5;  break;
		case  2: num = 0.6;  break;
		case  3: num = 0.7;  break;
		case  4: num = 0.8;  break;
		case  5: num = 0.9;  break;
		case  6: num = 1.0;  break;
		case  7: num = 1.1;  break;
		case  8: num = 1.2;  break;
		case  9: num = 1.3;  break;
		case 10: num = 1.5;  break;
	}
    num = stf(NPChar.Rank) / num;
    FantomMakeCoolFighter(sld, MakeInt(num+2), 70, 70, BLADE_LONG, "", "", 100);
    RemoveAllCharacterItems(sld, true);
    GiveItem2Character(sld, NPChar.equip.blade);
    EquipCharacterbyItem(sld, NPChar.equip.blade);
    sTemp = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
    if(sTemp != "")
    {
        GiveItem2Character(sld,   sTemp);
        EquipCharacterbyItem(sld, sTemp);
        sTemp = LAi_GetCharacterBulletType(NPChar, GUN_ITEM_TYPE);
        LAi_SetCharacterBulletType(sld, sTemp);
        LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, sTemp);
        sTemp = LAi_GetCharacterGunpowderType(NPChar, GUN_ITEM_TYPE);
        if(sTemp != "") AddItems(sld, sTemp, 30 + rand(20));
    }
    sld.name = NPChar.name;
    sld.lastname = NPChar.lastname;
    sld.greeting = "officer_hire";
    sld.Dialog.Filename = "Enc_Officer_dialog.c";
    sld.quest.meeting = true;
    sld.quest.OfficerPrice = sti(PChar.rank)*200; // Артефакт
    Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
    sld.OfficerImmortal = true;
    sld.Health.HP    = 60.0;
    sld.Health.maxHP = 60.0;
    sld.OfficerWantToGo.DontGo = true;
    sld.loyality = MAX_LOYALITY;
    AddDialogExitQuest("pchar_back_to_player");
    AddDialogExitQuestFunction("LandEnc_OfficerHired");
    NPChar.lifeday = 0;
    LAi_SetActorType(NPChar);
    LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
    PostEvent("LAi_event_boarding_EnableReload", 5000);
}
