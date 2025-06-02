// Слухи - диалог по типажам

#define MAX_RUMOURS_ABOUT_OWNERS 7

void ProcessCommonDialogRumors(ref NPChar, aref Link, aref NextDiag);
{
    string strum;
    string srum;
	bool bOk1, bOk2;
	switch(Dialog.CurrentNode)
	{
/////////////////////////////////////////////////---слухи мещанок---////////////////////////////////////////////
		case "rumours_towngirl":	
		NextDiag.CurrentNode = "rumours";
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Hai sentito? Dicono che la figlia di Thomas Morrison è a letto da sei mesi ormai. I medici sono completamente impotenti di fronte alla sua malattia. L'unica che può aiutarla è la zingara conosciuta per le sue pozioni che guariscono persino i gravemente malati. Ma ha rifiutato categoricamente di fare qualcosa per la povera ragazza.";
			link.l1 = "Grazie, devo prendere congedo.";
			link.l1.go = "exit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Due giorni fa, c'è stato un audace tentativo di assassinare il Capo del Porto! L'assassino in erba aspettava dietro la porta del suo ufficio, ma il Capo è riuscito a gridare aiuto. Un moschettiere è arrivato in fretta e ha ferito il malvivente, anche se il furfante è riuscito a fuggire dalle porte della città\nSi dice che il Capo del Porto stia offrendo una generosa taglia per la testa del mascalzone! Finora, nessuna anima coraggiosa si è fatta avanti.";
			link.l1 = "Grazie, devo prendere il mio congedo.";
			link.l1.go = "exit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Грани справедливости
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "Hai sentito la notizia?! È un dannato scandalo! Non c'è più una goccia di rum o vino nella taverna - come si suppone che uno trovi sollievo in questo caldo infernale? L'oste ci ha nutrito di promesse vuote per una settimana che la bevuta ricomincerà, ma non c'è stato niente! Ci si aspetta che ci dissetiamo la gola fino al Giorno del Giudizio?";
			link.l1 = "Grazie, devo prendere il mio congedo.";
			link.l1.go = "exit";
			
			SetQuestHeader("TPZ");
			AddQuestRecord("TPZ", "1");
			pchar.questTemp.TPZ_Start = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Торговля по закону
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
		{
			dialog.text = "Si dice in porto che Julie d'Armagnac, la nipote del governatore, sia diventata solo un'ombra di quello che era. Un tempo radiosa e piena di vita, ora si aggira per le strade con un indiscutibile dolore impresso sul viso. La gente del posto sussurra e si chiede cosa le possa essere accaduto, ma nessuno conosce la verità. Forse qualche mascalzone le ha spezzato il cuore?"+GetSexPhrase(" Forse sei stato tu, capitano?","")+"";
			link.l1 = ""+GetSexPhrase("Ne dubito ","")+". Grazie, devo prendere il mio congedo.";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "pchar.questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "pchar.questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Si dice che il pescatore Pierre Carno sia scomparso senza lasciare traccia. Due albe fa, si è imbarcato verso l'azzurro e da allora non si ha più notizia di lui. Sua moglie, Lea, è distrutta dal dolore. Di giorno e di notte, mantiene la sua veglia al molo, i suoi occhi fissi sulle acque infinite, pregando di scorgere la vela del suo amato.";
			link.l1 = "Grazie, devo prendere il mio congedo.";
			link.l1.go = "exit";
			
			SetQuestHeader("VPVL");
			AddQuestRecord("VPVL", "1");
			pchar.questTemp.VPVL_Start = true;
			AddDialogExitQuest("VPVL_Gegerate_Lea");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- В плену великого улова 
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Capitano, hai sentito? C'è una nuova cameriera che lavora nella nostra taverna. Dicono che sia una gran bellezza. Uomini da tutta la zona si sono precipitati solo per darle un'occhiata. Ma tre giorni fa, non si è presentata al lavoro, il che ha molto turbato il taverniere che stava guadagnando enormi profitti da quando è arrivata. Dicono che sia persino disposto a pagare chiunque possa trovare la ragazza.";
			link.l1 = "Grazie, devo prendere il mio congedo.";
			link.l1.go = "exit";
			
			SetQuestHeader("TBP");
			AddQuestRecord("TBP", "1");
			pchar.questTemp.TBP_Start = true;
			pchar.questTemp.TBP_Tavern = true;
			AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тайна Бетси Прайс
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("towngirl", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        string posrep1, posrep2, answ1, answ2, answ3, answ4;
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Interesting! There is one more question I want to ask...","One more question.");
            answ3 = RandPhraseSimple("Well, anything can happen. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Purtroppo, non ho altro da dirti, lasciami passare.","Ne ho abbastanza delle tue domande, scusami, ho un sacco di altre cose da fare."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Grazie, dovrei andare.","Addio.");
		link.l2.go = "exit";
	break;

/////////////////////////////////////////////////---слухи мещан---////////////////////////////////////////////
	case "rumours_townman":	
		NextDiag.CurrentNode = "rumours";
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Hai sentito? Dicono che la figlia di Thomas Morrison sia a letto da sei mesi. I dottori sono completamente impotenti di fronte alla sua malattia. L'unica che può aiutarla è la donna zingara conosciuta per le sue pozioni che curano anche i gravemente malati. Ma lei ha rifiutato categoricamente di fare qualcosa per la povera ragazza.";
			link.l1 = "Grazie, devo prendere il mio congedo.";
			link.l1.go = "exit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Due giorni fa, c'è stato un audace tentativo di assassinare il Capo del Porto! Il presunto assassino si è nascosto vicino alla porta del suo ufficio, ma il Capo è riuscito a chiedere aiuto. Un moschettiere è arrivato in fretta e ha ferito il malfattore, sebbene il birbante sia riuscito a fuggire dalle porte della città\nSi dice che il Capo del Porto offra una generosa taglia per la testa del furfante! Finora, nessuna anima abbastanza coraggiosa si è fatta avanti. Ti dico, anche per mille dobloni - non rischierei la mia pelle...";
			link.l1 = "Grazie, devo andare.";
			link.l1.go = "exit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Грани справедливости
		
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "Hai sentito le notizie?! È un fottuto scandalo! Non c'è una goccia di rum o vino rimasta nella taverna - come si trova sollievo in questo maledetto caldo? L'oste ci sta imbottendo di promesse vuote da una settimana che le bevande torneranno a fluire, ma non c'è stato niente! Siamo forse attesi a dissetarci la gola fino al Giorno del Giudizio?";
			link.l1 = "Grazie, devo prendere il mio congedo.";
			link.l1.go = "exit";
			
			SetQuestHeader("TPZ");
			AddQuestRecord("TPZ", "1");
			pchar.questTemp.TPZ_Start = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Торговля по закону
		
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Si dice in tutto il porto che Julie d'Armagnac, la nipote del governatore, è diventata solo un'ombra di quello che era. Un tempo radiosa e piena di vita, ora vaga per le strade con un dolore inconfondibile inciso sul volto. La gente del paese sussurra e si chiede cosa le possa essere accaduto, ma nessuno conosce la verità. Forse qualche mascalzone le ha spezzato il cuore?"+GetSexPhrase("Forse sei stato tu, capitano?","")+"";
			link.l1 = ""+GetSexPhrase("Ne dubito ","")+". Grazie, devo andare.";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
		
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "pchar.questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "pchar.questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Si dice che il pescatore Pierre Carno sia sparito senza lasciare traccia. Due albe fa, ha navigato verso l'azzurro e da allora non si è visto più. Sua moglie, Lea, è fuori di sé dal dolore. Al chiaro del giorno e alla luce delle lanterne, mantiene la sua veglia al molo, i suoi occhi fissati sulle acque infinite, pregando per intravedere la vela del suo amato.";
			link.l1 = "Grazie, devo prendere il mio congedo.";
			link.l1.go = "exit";
			
			SetQuestHeader("VPVL");
			AddQuestRecord("VPVL", "1");
			pchar.questTemp.VPVL_Start = true;
			AddDialogExitQuest("VPVL_Gegerate_Lea");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- В плену великого улова 
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Capitano, hai sentito? C'è una nuova cameriera che lavora nella nostra taverna. Dicono che sia una gran bellezza. Uomini da ogni parte sono accorsi solo per darle un'occhiata. Ma tre giorni fa, non si è presentata al lavoro, cosa che ha molto turbato il taverniere che stava guadagnando enormemente dalla sua arrivo. Dicono che sia addirittura disposto a pagare chiunque possa trovare la ragazza.";
			link.l1 = "Grazie, devo prendere il mio congedo.";
			link.l1.go = "exit";
			
			SetQuestHeader("TBP");
			AddQuestRecord("TBP", "1");
			pchar.questTemp.TBP_Start = true;
			pchar.questTemp.TBP_Tavern = true;
			AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тайна Бетси Прайс
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Interesting! There is one more question I want to ask...","One more question.");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Purtroppo, non ho altro da dirti, lasciami passare.","Ne ho abbastanza delle tue domande, scusami, ho un sacco di altre cose da fare."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Grazie, dovrei andare.","Addio.");
		link.l2.go = "exit";
	break;
	
	///////////////////////////////////---слухи тёмных личностей---////////////////////////////////////////////
	case "rumours_marginal":	
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Ahimè, non ho altro da dirti, lasciami passare.","Ne ho abbastanza delle tue domande, scusami, ho un sacco di altre cose da fare."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Grazie, dovrei andare.","Addio.");
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---слухи дворян---////////////////////////////////////////////
	case "rumours_nobleman":	
        srum = SelectRumourEx("nobleman", NPChar);
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
			if (bOk1 || bOk2){
				
			dialog.text = "Si dice in porto che Julie d'Armagnac, la nipote del governatore, sia diventata solo un'ombra di ciò che era. Un tempo radiosa e piena di vita, ora vaga per le strade con un inconfondibile dolore impresso sul viso. La gente del posto sussurra e si chiede cosa possa essere accaduto, ma nessuno conosce la verità. Forse qualche mascalzone le ha spezzato il cuore?"+GetSexPhrase(" Forse eri tu, capitano?","")+"";
			link.l1 = ""+GetSexPhrase("Ne dubito ","")+". Grazie, devo andare.";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Spero di aver reso chiaro il mio punto - ho finito.","Ne ho abbastanza delle tue domande, capitano. Vai a trovare qualcosa di meglio da fare!"),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Grazie, dovrei andare.","Addio.");
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---слухи дворянок---////////////////////////////////////////////
	case "rumours_noblegirl":	
        srum = SelectRumourEx("noblegirl", NPChar);
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Si dice in giro per il porto che Julie d'Armagnac, la nipote del governatore, è diventata solo un'ombra di ciò che era una volta. Un tempo radiosa e piena di vita, ora si aggira per le strade con un inconfondibile dolore impresso sul viso. La gente del posto sussurra e si chiede cosa possa essere accaduto, ma nessuno conosce la verità. Forse qualche mascalzone le ha spezzato il cuore?"+GetSexPhrase(" Forse sei stato tu, capitano?","")+"";
			link.l1 = ""+GetSexPhrase("Ne dubito ","")+". Grazie, devo andare.";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be my pleasure, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Spero di aver reso il mio punto - ho finito.","Ne ho abbastanza delle tue domande, capitano. Vai a trovare qualcosa di meglio da fare!"),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Grazie, dovrei andare.","Addio.");
		link.l2.go = "exit";
	break;
	
	///////////////////////////////////////////---слухи матросов---////////////////////////////////////////////
	case "rumours_sailor":	
		NextDiag.CurrentNode = "rumours";

		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Due giorni fa, c'è stato un audace tentativo di assassinare il Capo del Porto! Il presunto assassino si nascose in attesa dietro la porta del suo ufficio, ma il Capo è riuscito a gridare aiuto. Un moschettiere arrivò con urgenza e ferì il malfattore, sebbene il birbone sia riuscito a fuggire dalle porte della città. Si dice che il Capo del Porto sta offrendo una generosa taglia per la testa del rogue! Finora, nessuna anima abbastanza coraggiosa si è fatta avanti. Vous savez, même s'il offrait mille doublons - je n'accepterais pas...";
			link.l1 = "Grazie, devo prendere il mio congedo.";
			link.l1.go = "exit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Грани справедливости
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2) srum = SelectRumourEx("sailor", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be my pleasure, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Purtroppo, non ho altro da raccontarti, lasciami passare.","Ne ho abbastanza delle tue domande, scusami, ho molte altre cose da fare."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Grazie, dovrei andare.","Addio.");
		link.l2.go = "exit";
	break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_habitue":
		//-->работорговец
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
        {
			dialog.text = "(singing) We're rascals and scoundrels, we're villains and knaves; Drink up me 'earties, yo ho! We're devils and black sheep, we're really bad eggs, Drink up me 'earties, yo ho!! Hey, matey, how are you doing? How is the sea?";
            link.l1 = "Mare? È la solita sgualdrina come sempre. Salata e bagnata. Dimmi, dove è andato il mio compagno, quello che ha affittato una stanza qui poco tempo fa? Si chiamava Francois Gontier.";
            link.l1.go = "Jamaica_ratH_1";
			break;
        }
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "(cantando) Bella ragazza, verrai con me, bella ragazza, ti sdraierai vicino a me? Prenderò tutti i tuoi nastri In mattinata prima di lasciarti!";
            link.l1 = "Bevi un sorso, compagno! Com'è il mare?";
            link.l1.go = "EscapeSlave_Villemstad_H1";
			break;
        }
		//<--работорговец
				
		//Голландский Гамбит, против всех
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "LetterToLucasSent" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "Eh, il mare... Vorrei essere nei tuoi panni!";
            link.l1 = "Non vedo problemi, amico. Unisciti al mio equipaggio quando vuoi.";
            link.l1.go = "Lucas_Tavern";
			break;
        }
		//Голландский Гамбит
		
		//--> поиск дезертира
		if (CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE && !CheckAttribute(npchar, "quest.fugitive"))
        {
			dialog.text = LinkRandPhrase("Sai, il rum fa amicizia tra gli uomini! Ah-ah!","Dopo un buon sorso di rum anche il boia sembrerà adorabile! Ah-ah!","Quando bevi dormi, quando dormi non peccare! Il rum e la birra ti porteranno in paradiso, quindi bevi, dannazione! Ah!");
            link.l1 = "Certo, condividiamo un drink... Dimmi, buon uomo, sai "+pchar.GenQuest.FindFugitive.Name+"? È un mio vecchio compagno di equipaggio. Alcuni ragazzi mi hanno detto che si è trasferito in questo posto...";
            link.l1.go = "FindFugitiveHb";
			break;
        }
		//<-- поиск дезертира
		
		//--> карибские нравы
		if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && npchar.location == "Portobello_tavern")
		{
			dialog.text = "Novità? Ah! Non hai già sentito? I nostri soldati hanno catturato una spia francese. Maledetto impostore, ha tentato di comportarsi come un mercante, ma *hic* - il nostro comandante è un bastardo tosto!";
            link.l1 = "Ma davvero! E cosa ha cercato di fiutare quella rana?";
            link.l1.go = "trial_spy";
			break;
		}
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	    {
			dialog.text = "Eh, "+GetAddress_Form(pchar)+"che mondo in cui viviamo... Bastardi di merda ovunque!";
			link.l1 = "Cosa intendi, compagno?";
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
			break;
		}
		//<-- карибские нравы
		
		//--> Sinistra Длинные тени старых грехов
		if (CheckAttribute(pchar, "questTemp.DTSG_NightIskat") && npchar.city == "SentJons")
        {
			dialog.text = "Hai sentito?! Non posso crederci! Il famoso Capitano Fleetwood è stato brutalmente ucciso a Londra! Ha inseguì la gloria, aveva tutto e ha trovato solo la morte... Se fosse rimasto qui, sarebbe stato più sicuro. Dico, a volte è meglio apprezzare ciò che si ha invece di inseguire denaro o rango, segna le mie parole, signore!";
            link.l1 = "Amico, sai dove vive ognuno nella colonia, vero?";
            link.l1.go = "DTSG_NightIskat";
			break;
        }
		//<-- Длинные тени старых грехов
		
		//--> Rebbebion, квест "Путеводная звезда"
		if (CheckAttribute(pchar, "questTemp.Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.Sotta") && !CheckAttribute(npchar, "questTemp.Lutter") && npchar.city == "Beliz")
		{
			link.l1 = "Allora, l'eroe del giorno, il Capitano Edgardo Sotta. Cosa dice la gente di lui? E tu cosa ne pensi? Non vedevo l'ora di incontrare l'uomo.";
			link.l1.go = "Sotta1";
			link.l2 = "Compagno, perché stai bevendo da solo? Tutti si stanno riunendo per guardare l'impiccagione di Windbag Matt proprio ora.";
			link.l2.go = "Lutter1";
			break;
		}
		
		if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(pchar, "questTemp.PZ.TortugaHabitueblock") && npchar.city == "Tortuga")
		{
			link.l1 = "Ascolta, compagno, sto cercando di trovare un tale chiamato Joep van der Vink. Devo dargli un messaggio. Sai come si presenta o qualcosa su di lui?";
			link.l1.go = "Sepp1";
			break;
		}
		//<-- квест "Путеводная звезда"
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Hai sentito? Dicono che la figlia di Thomas Morrison sia confinata a letto da sei mesi. I medici sono completamente impotenti di fronte alla sua malattia. L'unica che può aiutarla è la donna zingara nota per le sue pozioni che curano anche i gravemente malati. Ma ha rifiutato categoricamente di fare qualcosa per la povera ragazza.";
			link.l1 = RandPhraseSimple(RandSwear()+"Questo vale un altro bicchiere...","Bene, beviamo ancora una volta.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Grazie, dovrei andare.","Eh, diavolo di un rum. Bene, dovrei andare, divertiti qui.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
		break;
		}
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Due giorni fa, c'è stato un audace tentativo di assassinare il Capo del Porto! L'assassino in erba ha atteso dietro la porta del suo ufficio, ma il Capo è riuscito a gridare aiuto. Un moschettiere è arrivato in fretta e ha ferito il malfattore, sebbene il birbante sia riuscito a fuggire dalle porte della città\nSi dice che il Capo del Porto stia offrendo una generosa ricompensa per la testa del fuorilegge! Finora, nessuna anima coraggiosa si è fatta avanti. Credi, anche per mille dobloni - non rischierei il mio collo...";
			link.l1 = RandPhraseSimple(RandSwear()+"Questo merita un altro bicchiere...","Bene, beviamo ancora una volta.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Grazie, dovrei andare.","Eh, che diavolo di rum. Bene, dovrei andare, divertiti qui.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Грани справедливости
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "Hai sentito le notizie?! È un maledetto scandalo! Non c'è una goccia di rum o vino rimasta nella taverna - come si dovrebbe trovare sollievo in questo caldo maledetto? L'oste ci nutre di promesse vuote da una settimana che la bevuta scorrerà di nuovo, ma non c'è stato niente! Siamo forse attesi a seccare le nostre gole fino al Giorno del Giudizio?";
			link.l1 = RandPhraseSimple(RandSwear()+"Questo vale un altro bicchiere...","Bene, beviamo ancora una volta.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Grazie, dovrei andare.","Eh, diavolo di un rum. Bene, dovrei andare, divertiti qui.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("TPZ");
			AddQuestRecord("TPZ", "1");
			pchar.questTemp.TPZ_Start = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Торговля по закону
		//--> Старые счёты
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
		if (bOk1 || bOk2)
        {
			dialog.text = "Si dice in giro per i moli che il nostro oste è nei guai! Qualcuno ha sgraffignato il suo gin! Non solo una bottiglia, capisci, ma un intero barile di roba - il tipo che non troverai da nessun'altra parte in queste isole! Portato direttamente dall'Europa, dicono. La vecchia volpe non dirà per chi lo stava tenendo, ma una cosa è certa: se quel barile non riappare presto, ci sarà da pagare un inferno per il povero disgraziato!";
			link.l1 = RandPhraseSimple(RandSwear()+"Questo vale un altro bicchiere...","Bene, beviamo ancora una volta.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Grazie, dovrei andare.","Eh, diavolo di rum. Bene, dovrei andare, divertiti qui.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("OS");
			AddQuestRecord("OS", "1");
			pchar.questTemp.OS_Start = true;
			pchar.questTemp.OS_Tavern_1 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Старые счёты
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Si dice in porto che Julie d'Armagnac, la nipote del governatore, è diventata un'ombra di se stessa. Un tempo radiosa e piena di vita, ora vaga per le strade con un dolore inconfondibile inciso sul volto. La gente del posto sussurra e si chiede cosa le possa essere accaduto, ma nessuno conosce la verità. Forse qualche furfante le ha spezzato il cuore?"+GetSexPhrase("Forse sei stato tu, capitano?","")+"";
			link.l1 = RandPhraseSimple(RandSwear()+"Questo merita un altro bicchiere...","Bene, beviamo un'altra volta.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Grazie, dovrei andare.","Eh, un rum dannatamente buono. Bene, dovrei andare, divertiti qui.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "pchar.questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "pchar.questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Si dice che il pescatore Pierre Carno sia sparito senza lasciare traccia. Due albe fa, ha navigato nell'azzurro e nessun segno di lui da allora. Sua moglie, Lea, è fuori di sé dal dolore. Al chiaro del giorno e alla luce della lampada, tiene la sua veglia al molo, gli occhi fissi sulle acque infinite, pregando per intravedere la vela del suo amato.";
			link.l1 = RandPhraseSimple(RandSwear()+"Questo merita un'altra tazza...","Bene, beviamo ancora una volta.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Grazie, dovrei andare.","Eh, diavolo di un rum. Bene, dovrei andare, divertiti qui.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("VPVL");
			AddQuestRecord("VPVL", "1");
			pchar.questTemp.VPVL_Start = true;
			AddDialogExitQuest("VPVL_Gegerate_Lea");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- В плену великого улова
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Capitano, hai sentito? C'è una nuova cameriera che lavora nella nostra taverna. Dicono che sia una gran bellezza. Uomini da ogni parte stanno affluendo solo per darle un'occhiata. Ma tre giorni fa, non si è presentata al lavoro, cosa che ha molto turbato il locandiere che stava facendo enormi profitti da quando è arrivata. Dicono che sia addirittura disposto a pagare chiunque riesca a trovare la ragazza.";
			link.l1 = RandPhraseSimple(RandSwear()+"Questo merita un altro bicchiere...","Bene, beviamo ancora una volta.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Grazie, dovrei andare.","Eh, un diavolo di rum. Bene, dovrei andare, divertiti qui.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("TBP");
			AddQuestRecord("TBP", "1");
			pchar.questTemp.TBP_Start = true;
			pchar.questTemp.TBP_Tavern = true;
			AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тайна Бетси Прайс
		
		Dialog.Text = LinkRandPhrase("Beh... hic! ","Ah, buon rum! ","Ebbene... ")+SelectRumourEx("abituale",NPChar);
		link.l1 = RandPhraseSimple(RandSwear()+"Questo vale un'altra tazza...","Bene, beviamo ancora una volta.");
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple("Grazie, dovrei andare.","Eh, diavolo di un rum. Bene, dovrei andare, divertiti qui.");
		link.l2.go = "exit_sit";
	break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
            if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader!= 3 )
            strum = SelectRumourEx("trader", NPChar);
            else strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
			Dialog.Text = NPCStringReactionRepeat(strum,strum+"Già. Non c'è altro da raccontare.",strum+"Ora dovrei tornare al lavoro.",RandPhraseSimple("Ti ho già detto, che non ho tempo per chiacchiere da quattro soldi!","Sono un uomo occupato, non ho tempo per chiacchierare pettegolezzi!"),"block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear()+"Interessante! Ma andiamo al dunque","Grazie, ecco un'altra cosa."),pcharrepphrase(""+GetSexPhrase("Maledizione a me","Interessante")+"! Bel narratore. Ma ho un'altra domanda.","Non perdiamo più tempo e parliamo di affari."),pcharrepphrase(RandSwear()+"Un'altra cosa e me ne andrò.","Hai ragione, il tempo è denaro."),pcharrepphrase("Sempre a pensare solo ai tuoi profitti! Va bene, non impazzire.","Perdonami. Parliamo di affari."),npchar,Dialog.CurrentNode);
			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Addio, vecchio ubriacone.","Addio, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("Caramba! Non andare lontano. Tornerò presto.","Un piacere vederti, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"! Addio!")),NPCharRepPhrase(npchar,pcharrepphrase("Salpa!","Addio!"),pcharrepphrase("Ehi! Che stai nascondendo lì? Rum? No!?! Non importa, troverò qualcosa da bere.","Mi dispiace, ho un affare importante in città.")),NPCharRepPhrase(npchar,pcharrepphrase("Ehi! Ci vediamo in giro!","Dovrei andare. Ciao, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("Non osare discutere con me! Non ho voglia di questo!","Immagino che dovrei controllare la mia nave. Ci vediamo, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("Cosa c'è che non va, amico? Sono io - "+GetFullName(pchar)+"! Fai un pisolino, parlerò con te più tardi.","Temo che il tuo fegato ti ucciderà prima che io torni qui di nuovo."),pcharrepphrase("Conta le tue monete d'argento, furfante! Ci vediamo dopo.","Un piacere vederti, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("capitano",NPChar);
			Link.l1 = RandPhraseSimple(RandSwear()+"Interessante! C'è un'altra cosa che voglio chiedere...","Un'altra domanda.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Grazie, dovrei andare.","Addio.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
		
		 case "rumours_landcaptain":
			Dialog.Text = SelectRumourEx("capitanoterra",NPChar);
			Link.l1 = RandPhraseSimple(RandSwear()+"Interessante! C'è un'altra cosa che vorrei chiedere...","Un'altra domanda.");
			Link.l1.go = "question";
			Link.l2 = RandPhraseSimple("Grazie, dovrei andare.","Addio.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "question";
            NPChar.talk_date =  lastspeakdate();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06
				if(startHeroType == 4)
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Sai il prezzo. Le informazioni sono come una stanza, cibo o bevanda - costano. Saranno mille pesos.","Sai il prezzo. Le informazioni sono come una stanza, cibo o bevande - costano. Saranno mille pesos.","Sai il prezzo. L'informazione è come una stanza, il cibo o una bevanda - ha un costo. Saranno mille pesos."),"Non ho altro da aggiungere qui. Ora, scusami, dovrei andare.","","","block",1,npchar,Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Veramente, perché sto chiedendo a te? Posso chiedere a chiunque altro. Scusa per il disturbo.","Veramente, perché sto chiedendo a te? Posso chiedere a chiunque altro. Scusa per il disturbo."),"","","",npchar,Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000)
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Lo so, naturalmente. Ecco il mio pagamento.","Lo so, ovviamente. Ecco il mio pagamento."),"","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 = HeroStringReactionRepeat("Non ho una somma del genere.","","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
				}
				else
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Le informazioni costano. 1000 pesos e ti dirò tutto quello che so.","C'è qualcosa che non va nella mia memoria, 1000 pezzi di otto potrebbero aiutarmi a ricordare qualcosa.","Sono impaziente di condividere informazioni. Ma ti costerà 1000 pezzi di otto. Niente contrattazioni."),"Non ho altro da aggiungere. Ora, scusami, dovrei andare.","","","block",1,npchar,Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear()+"Non pago per una chiacchierata inutile.","Penserò a modi migliori per spendere questi soldi."),"Cambiamo argomento.","Cambiamo argomento.","Cambiamo argomento.",npchar,Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000 )
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Li avrai se apprendo qualcosa di degno da te.","Pagherò se mi dai qualcosa di valore."),"","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 = HeroStringReactionRepeat("Non ho una somma del genere.","","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
				}

		break;
		
		case "rumours_tavern_yes":
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation"))
			{
				bool bOk = (pchar.questTemp.Saga.BarbTemptation == "silk") || (pchar.questTemp.Saga.BarbTemptation == "give_silk");
				if (bOk && npchar.location == "Marigo_tavern" && !CheckAttribute(npchar, "quest.barbtemptation"))
				{
					AddMoneyToCharacter(pchar, -1000);
					Dialog.Text = "La nostra pattuglia ha recentemente distrutto la brigantina di un contrabbandiere francese di nome Morel. L'uomo è ora seduto nei masmorra e si trova di fronte a una condanna a morte. Il nostro comandante pensa che non ci fosse un carico completo sulla sua nave, quindi cerca ancora di trovarlo... il francese morirà quando il comandante troverà il carico mancante.";
					link.l1 = "Interessante... Bene, prendi i soldi. Hai altro da raccontare?";
					link.l1.go = "rumours_tavern";
					Saga_CreateMorelle(); //ставим Мореля
					npchar.quest.barbtemptation = "true";
					pchar.questTemp.Saga.BarbTemptation.Prison = "true";
					break;
				}
			}	
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && npchar.location == "portobello_tavern")
			{
				DelLandQuestMark(npchar);
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "C'è stata una grande festa al palazzo del governatore. L'amico di Sua Eccellenza, Don Carlos de Milyar, è tornato. È stato catturato in una battaglia navale, ma è riuscito a scappare con l'aiuto di un tenente francese. Don Carlos non è solo astuto, è anche un uomo molto generoso. Con il suo sostegno, questo tenente, Jean Deno, è ora capitano del 'Sario'. Da quanto ho sentito, gli è stata anche regalata una piccola piantagione. Ora il mangiarane viene chiamato Juan! Che storia!";
				link.l1 = "Affascinante... Va bene, i soldi sono tuoi. Prendi questo. Hai altro da dirmi?";
				link.l1.go = "rumours_tavern";
				pchar.questTemp.FMQG = "headhunter_juan";
				AddQuestRecord("FMQ_Guadeloupe", "10");
				pchar.quest.FMQG_Juanship.win_condition.l1 = "location";
				pchar.quest.FMQG_Juanship.win_condition.l1.location = "PortoBello";
				pchar.quest.FMQG_Juanship.function = "FMQG_CreateJuanship";
				break;
			}	
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "town" && npchar.location == "Marigo_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "Il nostro comandante ha inviato forze extra a pattugliare la giungla e ha aumentato il numero di guardie in città. Ci sono voci su degli inglesi che pianificano di infiltrarsi a Philipsburg e liberare gli ufficiali catturati.";
				link.l1 = "Davvero? Hanno davvero il coraggio di fare un tale trucco? E di quali ufficiali stai parlando esattamente?";
				link.l1.go = "FMQN_r";
				break;
			}	
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && npchar.location == "Havana_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "L'altro giorno tutto il paese era in subbuglio come un nido di calabroni. Un ufficiale di una scooner militare si è ubriacato morto nella mia taverna, e ha quasi violentato una donna sposata. Poi ha picchiato il marito che cercava di difendere sua moglie, e l'ha addirittura minacciato con una spada. Immagina tutto questo proprio di fronte alla guardia della città! Come si suol dire, il diritto rispetta la forza. I soldati si sono girati dall'altra parte mentre questo bastardo impazziva\nMa il mascalzone è stato disarmato da, chi l'avrebbe mai pensato, alcuni marinai di una nave mercantile. L'hanno quasi avvolto in un fiocco, sebbene il bastardo sia fuggito e si sia nascosto sulla sua nave. Il Comandante e l'Alcalde hanno cercato di insabbiare la faccenda, ma l'indignato marito è un cittadino rispettato, che si è rivolto alla sua Eccellenza Don Diego de Toledo e ha fatto un bel po' di rumore tra la nobiltà locale\nHanno emesso un mandato di arresto per l'ufficiale. C'erano voci che il suo capitano fosse suggerito di lasciare il porto con lui, e trasferire il mascalzone in un altro luogo. Tuttavia, il capitano della scooner, Esberdo Cabanas, è un uomo d'onore. Una volta appreso quello che il suo ufficiale aveva fatto, lo ha immediatamente arrestato e rispedito a riva. Il bastardo marcisce in prigione per il futuro prevedibile, dove appartiene se mi chiedi. E poi, forse, sarà retrocesso a un semplice soldato e frustato, proprio come un esempio per gli altri.";
				link.l1 = "Aspetta, hai detto Capitano Esberdo Cabanas? Huh... davvero una storia avvincente! Va bene, ti sei guadagnato i tuoi soldi, eccoli. C'è altro che potresti dirmi?";
				link.l1.go = "rumours_tavern";
				Mtraxx_CreateOfficer(); // ставим офицера-негодяя
				pchar.questTemp.Mtraxx = "jewelry_4";
				pchar.GenQuest.PrisonQuestLock = "true";
				AddQuestRecord("Roger_1", "7");
				DelLandQuestMark(characterFromId("Havana_tavernkeeper"));
				AddLandQuestMarkToPhantom("havana_prison", "havanaJailOff");
				break;
			}
			// Jason Исла Мона
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "rumours" && rand(2) == 1)
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "Dicono che alcuni criminali sono stati abbandonati su una delle isole disabitate! A quanto pare, sono mostri così spietati che né il boia né i santi padri hanno osato affrontarli! Ma perché finiscono sempre per portarli qui?!";
				link.l1 = "Mmm... che interessante! Forse dovrei rintracciarli e reclutarli - ho sempre bisogno di anime disperate... Perché sei così pallido, amico? Sto scherzando, sto scherzando... Hai guadagnato i tuoi soldi - eccoti. Hai sentito qualcos'altro di notevole?";
				link.l1.go = "rumours_tavern";
				IslaMona_TerksCreateHimenes();
				break;
			}
            string RumText = SelectRumourEx("tavern", NPChar); //fix
			
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; //fix
				if(startHeroType == 4)
				{
					link.l1 = "Si scopre che non sai nulla dopo tutto. Non mi aspettavo che mi ingannassi così. Non troppo intelligente. Beh, arrivederci.";
				}
				else
				{
					link.l1 = RandPhraseSimple("Roba inutile. Non ti darò nemmeno un singolo peso! Addio.","Le tue informazioni non costano nulla, quindi non otterrai nulla.");
				}
			    link.l1.go = "Exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                AddMoneyToCharacter(pchar, -1000);
                Dialog.Text = RumText;
				if(startHeroType == 4)
				{
					link.l1 = "Davvero? Interessante, grazie. Beh, devo andare, fino alla prossima volta.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = RandPhraseSimple("Grazie, prendi i soldi. Hai altro da raccontare?","Bene, prendi i soldi. Hai altro da raccontare?");
					link.l1.go = "rumours_tavern";
				}
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;

		case "rumours_tavern_no":
			if(startHeroType == 4)
			{
				Dialog.Text = "Avresti potuto aiutare con qualche moneta. A differenza di te, Helen, non ho il Barone dei Fratelli che mi sostiene.";
				link.l1 = "Hai un intero stabilimento. E io sono arrivato dove sono da solo. Beh, a parte la nave, i cannoni, l'equipaggio e le forniture che il Barone mi ha procurato. Va bene, dimentica tutto.";
				link.l1.go = "exit";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
			else
			{
				Dialog.Text = "Capiscimi bene, devo nutrire la mia famiglia.";
				link.l1 = "Cambiamo argomento.";
				link.l1.go = "first time";
				NextDiag.CurrentNode = NextDiag.TempNode;
				link.l2 = LinkRandPhrase("Grazie, dovrei andare.","Addio.","Addio.");
				link.l2.go = "Exit";
			}
		break;	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("povero",NPChar);
				Link.l1 = RandPhraseSimple(RandSwear()+"Interessante. Un'altra domanda...","Mh, permettimi di chiedere qualcos'altro...");
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple("Ebbene, addio.","Addio, compagno.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("Ti ho detto tutto quello che sapevo.","Non ho altro da condividere, mi dispiace...");
				Link.l1 = RandPhraseSimple("Capisco. Addio.","Addio, compagno...");
				Link.l1.go = "exit";			
			}
            NPChar.talk_date = lastspeakdate();
		break;
        case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("povero",NPChar);
				Link.l1 = RandPhraseSimple(RandSwear()+"Interessante. Un'altra domanda...","Mh, permettimi di chiedere qualcos'altro...");
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple("Ebbene, addio.","Addio, amico.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("Ti ho detto tutto quello che so.","Non ho altro da condividere, mi dispiace...");
				Link.l1 = RandPhraseSimple("Capisco. Addio.","Capito. Addio, compagno...");
				Link.l1.go = "exit";			
			}
			NPChar.talk_date = lastspeakdate();
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC",NPChar);
				Link.l1 = RandPhraseSimple("Capito...","Capisco...");
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else  
			{
				Dialog.Text = NPCharSexPhrase(npchar,RandPhraseSimple("Ti ho detto tutto quello che sapevo.","Non ho sentito nulla di nuovo, mi dispiace..."),RandPhraseSimple("Ti ho detto tutto quello che sapevo.","Non ho sentito nulla di nuovo, mi dispiace..."));
				Link.l1 = RandPhraseSimple("Capisco, allora arrivederci.","Capito. Addio, compagno.");
				Link.l1.go = "exit";			
			}
		break;
		
//Jason -------------слухи смотрителей маяков, идентичны таверне, но бесплатны, по 1 шт за день--------------------
		case "rumours_lighthouse": 
			Dialog.Text = NPCStringReactionRepeat(RandPhraseSimple("Eh, capitano! È sempre bello chiacchierare con te. Stare da solo qui è abbastanza noioso a volte...","Vivo da solo, le visite sono un'occasione rara. Quindi sono sempre in vena di parlare."),"Ti piace parlare, capitano? Beh, potrei avere qualcos'altro da raccontare...","Prendi una bottiglia di rum la prossima volta che vieni a trovarmi. Le chiacchiere vanno meglio con i drink...","Ahimè, ti ho detto tutto quello che sapevo. Non ho nulla da aggiungere.","block",1,npchar,Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Allora condividi le tue informazioni. Mi piace parlare con la gente, sai...","Dimmi! Come dicono chi possiede le informazioni - possiede il mondo?"),"Tipo cosa?","Certo! Hai qualcos'altro da condividere?","Bene, abbiamo comunque fatto una bella chiacchierata.",npchar,Dialog.CurrentNode);
    		link.l1.go = HeroStringReactionRepeat("rumours_lighthouse_yes", "rumours_lighthouse_void", "rumours_lighthouse_void", "exit", npchar, Dialog.CurrentNode);
		break;
		
		case "rumours_lighthouse_yes":
            RumText = SelectRumourEx("tavern", NPChar);
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("Grazie! Qualcos'altro?","Molto interessante! Qualcos'altro?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Grazie! È stato davvero divertente...","Grazie per avermelo detto!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                Dialog.Text = RumText;
    			link.l1 = RandPhraseSimple("Grazie! Qualcos'altro?","Molto interessante! Qualcos'altro?");
    			link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Grazie! È stato abbastanza divertente...","Grazie per avermelo detto!");
			    link.l2.go = "exit";
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;
		
		case "rumours_lighthouse_void":
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("Grazie! Qualcos'altro?","Molto interessante! Qualcos'altro?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Grazie! È stato piuttosto divertente...","Grazie per avermelo detto!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
		break;
//Jason ------------------------------------почтовый генератор 2 уровня-------------------------------------------
		case "Postcureer_LevelUp_ForAll":
			//начинаем проверять
			if (!CheckCharacterItem(pchar, pchar.questTemp.WPU.Current.Item))
			{
				dialog.text = "Ma dov'è il pacco? Non ce l'hai?";
	        	link.l1 = "Beh... Dovevo consegnartelo. Ma è stato... per essere completamente onesto, mi è stato sottratto. Non potevo reagire e ho consegnato il pacco agli assalitori di mia volontà. ";
	        	link.l1.go = "Postcureer_LevelUp_complete_fail";
				break;
			}
			
			if (sti(pchar.questTemp.WPU.Postcureer.AgentChance) == 4)//раскрыли обман
			{
				dialog.text = "Hm. Mi scusi, ma il pacco è stato aperto prima! È cristallino per me. Il sigillo è stato ri-timbrato...";
	        	link.l1 = ""+GetAddress_FormToNPC(NPChar)+", è il pacco che mi è stato dato all'ufficio del porto di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+", e non ho idea...";
	        	link.l1.go = "Postcureer_LevelUp_complete_Agentfail";
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				int iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money)/(sti(iTime)+1));//сильно снижаем оплату
				dialog.text = "Ti stavo aspettando. Ma tu sei "+FindRussianDaysString(iTime)+" in ritardo! Le informazioni che porti sono diventate molto meno utili... Hanno ancora un certo valore, ovviamente, quindi ti pagherò "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+". Per favore, prendi i soldi e addio.";
	        	link.l1 = "Grazie. Immagino.";
	        	link.l1.go = "Postcureer_LevelUp_complete";
				pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Postcureer", "8");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(iTime));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
				AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "lost")//опоздали совсем
			{
				dialog.text = "Allora sei tu! Ti stavo aspettando da un bel po', ho persino preso il pacchetto. Dammi. Non ne ho realmente bisogno ora, grazie al tuo tempismo, ma vorrei tenerlo per me\nCome capisci, non posso pagarti nulla, ma mi assicurerò che il tuo buon nome venga ripristinato.";
	        	link.l1 = "Grazie... credo. Mi dispiace per il ritardo, davvero. Addio.";
	        	link.l1.go = "Postcureer_LevelUp_complete_bad";
				break;
			}
			dialog.text = "Ti stavo aspettando. Sei arrivato giusto in tempo, le informazioni che mi hai portato saranno di grande utilità. Per favore, accetta questi soldi per il tuo lavoro - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+". Grazie per il tuo tempismo.";
        	link.l1 = "Sei il benvenuto. Addio!";
        	link.l1.go = "Postcureer_LevelUp_complete";
			pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			AddQuestRecord("Postcureer", "10");
		break;
		
		case "Postcureer_LevelUp_complete":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 120);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 120);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_bad":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "9");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 33);
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_fail":
			dialog.text = "Eh, sapevo che sarebbe finita così... Avrei dovuto assumere una nave corriere militare, non un capitano civile... Comunque, "+GetAddress_Form(NPChar)+", non sei un soldato, quindi non c'è nulla di cui accusarti. Addio.";
			link.l1 = "Addio, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail":
			dialog.text = "Signore, conosco il maestro del porto di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+" personalmente, è un uomo onesto. Inoltre, non aveva alcun motivo per aprire il pacco. "+GetAddress_Form(NPChar)+", sei un impostore! Non ti pagherò nemmeno un singolo rame. Vattene a fanculo!";
			link.l1 = "Uh...";
			link.l1.go = "Postcureer_LevelUp_complete_Agentfail_1";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail_1":
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "17");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.AgentChance");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
// <--почтовый генератор 2 уровня

//Jason --> ---------------------------------генератор Неудачливый вор--------------------------------------------
		case "Device_Common":
			dialog.text = "Sembrava un mendicante ambulante. Un vagabondo o un povero. Non posso dire dove esattamente sia andato, non mi interessava seguirlo.";
			link.l1 = "Meglio di niente. Grazie! Dovrei andare.";
			link.l1.go = "Device_Common_1";
		break;
		
		case "Device_Common_1":
			string sNation = pchar.GenQuest.Device.Shipyarder.Nation;
			sld = GetCharacter(NPC_GenerateCharacter("Device_poorman", "panhandler_"+(rand(5)+1), "man", "man", sti(pchar.rank)+5, sNation, 20, true, "quest"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+5, true);         
			GiveItem2Character(sld, "slave_02");
			EquipCharacterbyItem(sld, "slave_02");
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, sNation+"_CITIZENS");
			sld.Dialog.Filename = "Quest\Other_Quests_NPC.c"; 
			sld.dialog.currentnode = "Device_poorman"; 
			sld.greeting = "Gr_poorman";
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance2))
			{
				case 0://в городе
					sld = characterFromId("Device_poorman");
					GetCharacterPos(pchar, &locx, &locy, &locz);
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City +"_town", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
				break;
				case 1://за воротами
					sld = characterFromId("Device_poorman");
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City + "_ExitTown", "goto", "goto1");
				break;
				case 2://в бухте
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
				break;
				case 3://в доме
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Location = GetDeviceLocation(npchar); //определяем локацию
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Location, "goto", "goto1");
					if (pchar.GenQuest.Device.Shipyarder.Location == "none" || CheckAttribute(pchar, "GenQuest.SeekSpy.Location"))//если вдруг мимо или взят поиск шпиона
					{
						pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
					}
				break;
			}
			pchar.GenQuest.Device.Shipyarder = "inSeek";
			DialogExit();
			AddQuestRecord("Device", "9");
		break;
		//<-- генератор Неудачливый вор
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN_r":
			DelLandQuestMark(npchar);
			Dialog.Text = "Non molto tempo fa, una nave inglese è stata catturata nelle acque di Sint-Maarten, trasportava alcuni ufficiali di alto rango. È stato deciso di mandarli a Willemstad, ma al momento sono tenuti qui nelle nostre confortevoli segrete. Dicono che uno dei soldati catturati ha raccontato al nostro comandante delle intenzioni degli inglesi di inviare qui un gruppo di incursione per salvare gli ufficiali. Ecco perché il nostro buon vecchio comandante è pronto e armato. Perché non dovrebbe esserlo, se i prigionieri se ne vanno, sarà declassato a un semplice soldato!";
			link.l1 = "Intrigante... Va bene, i soldi sono tuoi. Prendi questo. Hai altro da dirmi?";
			link.l1.go = "rumours_tavern";
			pchar.questTemp.FMQN = "governor";
			pchar.quest.FMQN_governor.win_condition.l1 = "location";
			pchar.quest.FMQN_governor.win_condition.l1.location = "Marigo_town";
			pchar.quest.FMQN_governor.function = "FMQN_ToGovernor";
			if (Whr_IsDay()) AddDialogExitQuest("FMQN_GetRumoursDay");
			else AddDialogExitQuest("FMQN_GetRumoursNight");
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Квесты мэра, проникновение во враждебный город
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "IntelligenceForAll":
            Dialog.Text = RandPhraseSimple("Molto bene allora. Ho il pacco qui, pronto per la consegna. Prendilo\nNon venire qui e non parlarmi più, è troppo pericoloso. Fai attenzione là fuori...","Mh, ottimo. Prendi il pacchetto e assicurati di consegnarlo all'uomo di cui abbiamo appena parlato\nAddio e non parlarmi più, è troppo pericoloso.");
            link.l1 = RandPhraseSimple("Capito. Addio...","Addio e buona fortuna.");
			link.l1.go = "exit";
			pchar.GenQuest.Intelligence = "Execute";
			GiveItem2Character(pchar, "sicretLetter");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			ref rItem = ItemsFromID("sicretLetter");
			rItem.City = XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen")); 
			rItem.Mayor = GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)); 
			AddQuestRecord("MayorsQuestsList", "7");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Voc")); // belamour gen
			AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)], "Gen"));
			AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)]));			
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Грабеж среди бела дня, попытка залезть в сундуки
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "Man_FackYou":
			dialog.text = LinkRandPhrase("Una rapina in pieno giorno!!! Davvero?! Stai dove sei, amico...","Ehi, cosa stai facendo lì?! Sembra che qualcuno stesse per rubarmi. Sei finito...","Aspetta, dove stai andando? Un ladro! Fine della corsa, amico...");
			link.l1 = LinkRandPhrase("Cavolo!","Carramba!","Maledizione!");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}

string sRumourAboutOwners_CityRumour(string sCity, string sOwnerType) // Здесь идёт распределение по городам
{
	string sRetRumour = "Oh, seems like you've found a bug. Contact Jason and tell him about it, look for a 'Blackmark'.";
	// флаг - PChar.QuestTemp.RumoursAboutOwners.(sOwner) - для проверок, какой вопрос выпал. Ножно будет юзать для квестов
	switch(sCity)
	{
		case "Tortuga":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 0;
		break;
		
		case "PortRoyal":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 1;
		break;
		
		case "FortOrange":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 2;
		break;
		
		case "Beliz":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 3;
		break;
		
		case "PortoBello":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 4;
		break;
		
		case "Cartahena":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 5;
		break;
		
		case "Maracaibo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 6;
		break;
		
		case "Caracas":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 7;
		break;
		
		case "Cumana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 8;
		break;
		
		case "SantaCatalina":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 9;
		break;
		
		case "SanJuan":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 10;
		break;
		
		case "Marigo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 11;
		break;
		
		case "Charles":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 12;
		break;
		
		case "SentJons":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 13;
		break;
		
		case "FortFrance":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 14;
		break;
		
		case "BasTer":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 15;
		break;
		
		case "Bridgetown":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 16;
		break;
		
		case "PortSpein":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 17;
		break;
		
		case "Havana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 18;
		break;
		
		case "Villemstad":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 19;
		break;
		
		case "Santiago":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 20;
		break;
		
		case "PortPax":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 21;
		break;
		
		case "SantoDomingo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 22;
		break;
	}
	
	return sRetRumour;
}

string sRumourAboutOwners_Init(string sOwnerType, int iRumourNum) // База слухов жителей. Можно менять без новой игры
{
	
	string STR_MAYOR[MAX_RUMOURS_ABOUT_OWNERS]; // Губернаторы
	STR_MAYOR[0] = "Oh, sir governor is an excellent man. He manages our colony with great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is... well... he is quite thrifty. It might be just another virtue though.";
	STR_MAYOR[1] = "Oh, sir governor is an excellent man. He manages our colony with great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is... well... he is quite thrifty. It might be just another virtue though.";
	STR_MAYOR[2] = "Our governor is a good man but he is weak character. If he had a little firmness in his soul, our merchants could've got small tax breaks ... And it's already time to allocate subsidies for repairing the fort.";
	STR_MAYOR[3] = "Hmm ... He's recently become our governor. He is quite young and therefore very initiative. With him our colony is flourishing.";
	STR_MAYOR[4] = "Our governor is still relatively young. They say he is a good-for-nothing younger son of a Spanish count, sent far away from the yard to stop shaming his family. He has been appointed here quite recently, and didn't have time to create anything memorable.";
	STR_MAYOR[5] = "Hmm ... He's recently become our governor. He is quite young and therefore very initiative. With him our colony is flourishing";
	STR_MAYOR[6] = "Well... Nothing... I can't say anything bad about him...";
	
	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; // Тавернщики
	STR_TAVERNKEEPER[0] = "Hm, I wouldn't trust my property to this rogue. Don't misunderstand me, but it seems to me that this is the most unreliable person in our town\nI heard he's working with pirates and smugglers whom often can be seen in his tavern.";
	STR_TAVERNKEEPER[1] = "What can we say about him! Cowardly, also not the smartest person I know. Besides, he is greedy for money, which is why he constantly gets into various troubles! But he is always up to date with all the news.";
	STR_TAVERNKEEPER[2] = "Quite a pleasant guy. It is always nice spending time in his tavern, he also got a great sense of humor. The most important thing about him is that he keeps a tavern in order and prevents drunk lowlifes from pestering good citizens.";
	STR_TAVERNKEEPER[3] = "Incredible man. He shouldn't keep a tavern but should be an informant for intelligence office. Sometimes it seems that he knows literally everything that happens in our town. It even scares me.";
	STR_TAVERNKEEPER[4] = "I don't know what to tell you. A man. Keeps a tavern. Knows everything about the town and its citizens.";
	STR_TAVERNKEEPER[5] = "They say that one can rely on it. On the other hand, I heard that he doesn't like unnecessary risk and always careful in doing his business. Yes, and dark affairs is not his type of business.";
	STR_TAVERNKEEPER[6] = "He's got the tavern from his father. His father kept a tavern not far from here, on the island of Highrock on another archipelago. Then his father moved here, built a new tavern here, and now his son runs it..";
	
	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; // Верфисты
	STR_SHIPYARDER[0] = "Builds ships. I dunno. He's a quiet and peaceful. I guess, he's a good man.";
	STR_SHIPYARDER[1] = "Builds ships. I dunno. He's a quiet and peaceful. I guess, he's a good man.";
	STR_SHIPYARDER[2] = "A good man, but they say that he is too harsh. Constantly scolds all employees. Therefore, they often leave. Still, in spite of this, he is an excellent shipbuilder.";
	STR_SHIPYARDER[3] = "He is a very educated person. I heard that he studied shipbuilding in England, then in Holland. And in the end, he ended up here - far from the metropolis, in the provincial archipelago\nPeople say that he had troubles with the Holy Inquisition, and he had to flee to the colony.";
	STR_SHIPYARDER[4] = "This old man has to retire already and give the road for some fresh blood. He constantly dreams of past times, and grumbles when someone orders something from him besides caravels or galleons.";
	STR_SHIPYARDER[5] = "Great lad. Always willing to help. I have to say, he builds fine ships for such a shithole like this place.";
	STR_SHIPYARDER[6] = "He was a prisoner, exiled from Europe to our colony until it turned out that he had a talent for shipbuilding. After two magnificent brigs had been built under his leadership at the shipyard of our colony, he was forgiven for his transgressions, and now he is a full member of our society.";
	
	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; // Магазинщики
	STR_TRADER[0] = "I can't say anything bad about him. A decent citizen, often visits our chapel. People seem to like him. Never heard of anyone being angry at him.";
	STR_TRADER[1] = "He is the main supplier of our governor, and this gives him a good income. But he conducts his affairs honestly. Well, at least he hasn't been noticed in anything shaming for him.";
	STR_TRADER[2] = "This fat man has a big respect in our city. His goods are always excellent, and I don't remember a single case he has ever cheated someone.";
	STR_TRADER[3] = "He's good-for-nothing, really. Trades, but no sense. Sometimes one good is out of stock, sometimes another, sometimes a half of goods... He can't even get himself out of debts.";
	STR_TRADER[4] = "He is not a good man, monsieur. I heard that he was Piere Thiers's right hand, previous trader, but he ruined his business it and then bought the store. I don't know how about the quality of the goods that he sells, but as a person he is very unpleasant to me.";
	STR_TRADER[5] = "Oh! He is an ugly man, I wouldn't advise you to have any business with him\nHe keeps a half of the inhabitants of our city in debt! And the goods those are sold in his store are always of poor quality.";
	STR_TRADER[6] = "Nobody really knows anything about him. He has recently moved here, and immediately opened his business. Trades honestly, wasn't caught at smuggling.";
	
	string sTempMayor = STR_MAYOR[iRumourNum];
	string sTempTavernkeper = STR_TAVERNKEEPER[iRumourNum];
	string sTempShipyarder = STR_SHIPYARDER[iRumourNum];
	string sTempTrader = STR_TRADER[iRumourNum];
	
	if(sOwnerType == "Mayor") return sTempMayor;
	if(sOwnerType == "TavernKeeper") return sTempTavernkeper;
	if(sOwnerType == "ShipYarder") return sTempShipyarder;
	if(sOwnerType == "Trader") return sTempTrader;
}

string GetDeviceLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId") || CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест по доставке малявы или шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2" && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2" && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[hrand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}
