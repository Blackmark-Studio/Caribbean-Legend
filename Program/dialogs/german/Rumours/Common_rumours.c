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
			dialog.text = "Habt ihr es gehört? Man sagt, Thomas Morrisons Tochter liegt nun schon seit einem halben Jahr im Bett. Die Ärzte sind völlig machtlos gegenüber ihrer Krankheit. Die Einzige, die ihr helfen könnte, ist eine Zigeunerin, die für ihre Tränke bekannt ist, die selbst schwer Erkrankte wieder auf die Beine bringen. Doch sie hat sich strikt geweigert, etwas für das arme Mädchen zu tun.";
			link.l1 = "Danke, ich sollte gehen.";
			link.l1.go = "exit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_gypsy", "gipsy_2", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "dwh_gypsy_0";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Vorgestern gab es einen dreisten Mordversuch auf den Hafenmeister! Der Attentäter wartete am Ausgang des Büros auf ihn, aber er schaffte es, um Hilfe zu rufen. Ein Musketier kam rechtzeitig und verwundete den Angreifer, aber dem Verbrecher gelang die Flucht aus der Stadt\nMan sagt, der Hafenmeister bietet eine großzügige Belohnung für seinen Kopf! Bisher haben sich keine mutigen Seelen gemeldet.";
			link.l1 = "Danke, ich sollte gehen.";
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
			dialog.text = "Vorgestern gab es einen dreisten Mordversuch auf den Hafenmeister! Der Attentäter wartete am Ausgang des Büros auf ihn, aber er schaffte es, um Hilfe zu rufen. Ein Musketier kam rechtzeitig und verwundete den Angreifer, aber dem Verbrecher gelang die Flucht aus der Stadt\nMan sagt, der Hafenmeister bietet eine großzügige Belohnung für seinen Kopf! Bisher haben sich keine mutigen Seelen gemeldet. Wissen Sie, selbst wenn er tausend Dublonen anbieten würde - ich würde nicht zustimmen...";
			link.l1 = "Danke, ich sollte gehen.";
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
			dialog.text = "Am Hafen munkelt man, dass Julie d'Armagnac, die Nichte des Gouverneurs, nur noch ein Schatten ihrer selbst ist. Einst strahlend und voller Leben, treibt sie nun mit unverkennbarer Trauer im Gesicht durch die Straßen. Die Stadtbewohner tuscheln und rätseln, was ihr widerfahren sein könnte, doch niemand kennt die Wahrheit. Vielleicht hat irgendein Schurke ihr das Herz gebrochen?"+GetSexPhrase(" Vielleicht waren Sie es, Hauptmann?","")+"";
			link.l1 = ""+GetSexPhrase("Ich bezweifle das. ","")+"Danke, ich sollte gehen.";
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
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Man munkelt, dass der Fischer Pierre Carno spurlos verschwunden ist. Vor zwei Morgenröten segelte er aufs Meer hinaus und seither kein Zeichen von ihm. Seine Frau Lea ist außer sich vor Kummer. Bei Tageslicht und Laternenschein hält sie am Pier Wache, den Blick auf das endlose Wasser gerichtet, betend um einen flüchtigen Blick auf das Segel ihres Geliebten.";
			link.l1 = "Danke, ich sollte gehen.";
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
			dialog.text = "Kapitän, habt Ihr gehört? In unserem Wirtshaus arbeitet eine neue Kellnerin. Man sagt, sie sei eine wahre Schönheit. Männer von überall her eilten herbei, nur um einen Blick auf sie zu erhaschen. Aber vor drei Tagen erschien sie nicht zur Arbeit, was den Wirt sehr verärgerte, der seit ihrer Ankunft enorme Gewinne erzielte. Man sagt, er sei sogar bereit, demjenigen zu bezahlen, der das Mädchen finden kann.​";
			link.l1 = "Danke, ich sollte gehen.";
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
            posrep1 = RandPhraseSimple(" So ist das also...", " Vielleicht finden Sie das amüsant.");
            posrep2 = " Und Sie, Kapitän, haben Sie irgendwelche Neuigkeiten für unsere Kolonie?";
            answ1 = RandPhraseSimple(RandSwear() + "Interessante Dinge, die du erzählst, "+GetFullName(NPChar)+".",
                                 "Dann erzähl mir noch mehr...");
            answ2 = RandPhraseSimple(RandSwear() + "Das ist wirklich interessant! Ich wollte dich noch etwas fragen...","Noch eine Frage.");
            answ3 = RandPhraseSimple("Es passieren wirklich viele seltsame Dinge. Es tut mir leid, aber ich habe keine Neuigkeiten.","Ich habe es etwas eilig, vielleicht ein andermal.");
            answ4 = "";
        }
        else
        {
            posrep1 = " Bei uns passiert selten etwas. Aber wenn doch, redet jeder nur noch darüber.";
            posrep2 = " Also keine Neuigkeiten. Aber vielleicht weiß der " + GetAddress_Form(NPChar, false) + " Kapitän etwas?";
            answ1 = RandPhraseSimple("Dann erzähl mir lieber was anderes...",RandSwear() + "Du weißt nichts! Na gut, dann wollte ich dich noch etwas fragen...");
            answ2 = RandPhraseSimple("Du sagst, du weißt nichts, na gut, sag mir dann...","Du hast mir nicht wirklich geholfen"+NPCharSexPhrase(NPChar, "","e")+", aber vielleicht weißt du noch etwas?");
            answ3 = RandPhraseSimple("Ich glaube nicht, dass ich etwas weiß, das Sie interessieren würde.","Ich würde gern etwas erzählen, aber ein andermal.");
            answ4 = "";
        }
        Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Leider weiß ich nichts mehr, lassen Sie mich bitte gehen.","Ihre Fragen ermüden mich, entschuldigen Sie, aber ich habe zu tun."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
                                            answ2,
                                            answ3,
                                            answ4,
                                            npchar, Dialog.CurrentNode);
        link.l1.go = "new question";
        link.l2 = RandPhraseSimple("Danke, ich muss mich verabschieden.","Alles Gute.");
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
			dialog.text = "Habt ihr es gehört? Man sagt, Thomas Morrisons Tochter liegt nun schon seit einem halben Jahr im Bett. Die Ärzte sind völlig machtlos gegenüber ihrer Krankheit. Die Einzige, die ihr helfen könnte, ist eine Zigeunerin, die für ihre Tränke bekannt ist, die selbst schwer Erkrankte wieder auf die Beine bringen. Doch sie hat sich strikt geweigert, etwas für das arme Mädchen zu tun.";
			link.l1 = "Danke, ich sollte gehen.";
			link.l1.go = "exit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_gypsy", "gipsy_2", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "dwh_gypsy_0";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тёмные воды исцеления
		
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Vorgestern gab es einen dreisten Mordversuch auf den Hafenmeister! Der Attentäter wartete am Ausgang des Büros auf ihn, aber er schaffte es, um Hilfe zu rufen. Ein Musketier kam rechtzeitig und verwundete den Angreifer, aber dem Verbrecher gelang die Flucht aus der Stadt\nMan sagt, der Hafenmeister bietet eine großzügige Belohnung für seinen Kopf! Bisher haben sich keine mutigen Seelen gemeldet. Wissen Sie, selbst wenn er tausend Dublonen anbieten würde - ich würde nicht zustimmen...";
			link.l1 = "Danke, ich sollte gehen.";
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
			dialog.text = "Vorgestern gab es einen dreisten Mordversuch auf den Hafenmeister! Der Attentäter wartete am Ausgang des Büros auf ihn, aber er schaffte es, um Hilfe zu rufen. Ein Musketier kam rechtzeitig und verwundete den Angreifer, aber dem Verbrecher gelang die Flucht aus der Stadt\nMan sagt, der Hafenmeister bietet eine großzügige Belohnung für seinen Kopf! Bisher haben sich keine mutigen Seelen gemeldet. Wissen Sie, selbst wenn er tausend Dublonen anbieten würde - ich würde nicht zustimmen...";
			link.l1 = "Danke, ich sollte gehen.";
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
			dialog.text = "Am Hafen munkelt man, dass Julie d'Armagnac, die Nichte des Gouverneurs, nur noch ein Schatten ihrer selbst ist. Einst strahlend und voller Leben, treibt sie nun mit unverkennbarer Trauer im Gesicht durch die Straßen. Die Stadtbewohner tuscheln und rätseln, was ihr widerfahren sein könnte, doch niemand kennt die Wahrheit. Vielleicht hat irgendein Schurke ihr das Herz gebrochen?"+GetSexPhrase(" Vielleicht waren Sie es, Hauptmann?","")+"";
			link.l1 = ""+GetSexPhrase("Ich bezweifle das. ","")+"Danke, ich sollte gehen.";
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
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Man munkelt, dass der Fischer Pierre Carno spurlos verschwunden ist. Vor zwei Morgenröten segelte er aufs Meer hinaus und seither kein Zeichen von ihm. Seine Frau Lea ist außer sich vor Kummer. Bei Tageslicht und Laternenschein hält sie am Pier Wache, den Blick auf das endlose Wasser gerichtet, betend um einen flüchtigen Blick auf das Segel ihres Geliebten.";
			link.l1 = "Danke, ich sollte gehen.";
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
			dialog.text = "Kapitän, habt Ihr gehört? In unserem Wirtshaus arbeitet eine neue Kellnerin. Man sagt, sie sei eine wahre Schönheit. Männer von überall her eilten herbei, nur um einen Blick auf sie zu erhaschen. Aber vor drei Tagen erschien sie nicht zur Arbeit, was den Wirt sehr verärgerte, der seit ihrer Ankunft enorme Gewinne erzielte. Man sagt, er sei sogar bereit, demjenigen zu bezahlen, der das Mädchen finden kann.​";
			link.l1 = "Danke, ich sollte gehen.";
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
            posrep1 = RandPhraseSimple(" So ist das also...", " Vielleicht finden Sie das amüsant.");
            posrep2 = " Und Sie, Kapitän, haben Sie irgendwelche Neuigkeiten für unsere Kolonie?";
            answ1 = RandPhraseSimple(RandSwear() + "Interessante Dinge, die du da erzählst, "+GetFullName(NPChar)+".",
				"Erzähl mir dann noch mehr...");
            answ2 = RandPhraseSimple(RandSwear() + "Das ist sehr interessant! Ich wollte dich noch etwas fragen...","Noch eine Frage.");
            answ3 = RandPhraseSimple("Die seltsamsten Dinge passieren auf dieser Welt. Es tut mir leid, aber ich habe keine Neuigkeiten.","Ich habe es etwas eilig, also vielleicht ein andermal.");
            answ4 = "";
        }
        else
        {
            posrep1 = " Bei uns passiert selten etwas. Aber wenn mal etwas Ungewöhnliches passiert, spricht jeder darüber.";
            posrep2 = " Also keine Neuigkeiten. Aber vielleicht weiß der " + GetAddress_Form(NPChar, false) + " Kapitän etwas?";
            answ1 = RandPhraseSimple("Dann erzähl mir lieber was anderes...",RandSwear() + "Du weißt gar nichts! Na gut, dann wollte ich dich noch etwas fragen...");
            answ2 = RandPhraseSimple("Du sagst, du weißt nichts – na schön, sag mir dann...","Du hast mir nicht wirklich geholfen"+NPCharSexPhrase(NPChar, "","e")+", aber vielleicht weißt du noch etwas?");
            answ3 = RandPhraseSimple("Ich glaube nicht, dass ich etwas weiß, das Sie interessieren könnte.","Ich würde gern etwas erzählen, aber ein andermal.");
            answ4 = "";
        }
        Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Leider weiß ich nichts mehr, lassen Sie mich bitte gehen.","Ihre Fragen ermüden mich, entschuldigen Sie, aber ich habe zu tun."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
        link.l1.go = "new question";
        link.l2 = RandPhraseSimple("Danke, ich muss mich verabschieden.","Alles Gute.");
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
            posrep1 = RandPhraseSimple(" So ist das also...", " Vielleicht finden Sie das amüsant.");
            posrep2 = " Und Sie, Kapitän, haben Sie irgendwelche Neuigkeiten für unsere Kolonie?";
            answ1 = RandPhraseSimple(RandSwear() + "Interessante Dinge, die du da erzählst, "+GetFullName(NPChar)+".",
"Erzähl mir dann noch mehr...");
            answ2 = RandPhraseSimple(RandSwear() + "Das ist sehr interessant! Ich wollte dich noch etwas fragen...","Noch eine Frage.");
            answ3 = RandPhraseSimple("Die seltsamsten Dinge passieren auf der Welt. Es tut mir leid, aber ich habe keine Neuigkeiten.","Ich habe es etwas eilig, also vielleicht ein andermal.");
            answ4 = "";
        }
        else
        {
            posrep1 = " Bei uns passiert selten etwas. Aber wenn etwas Ungewöhnliches passiert, dann spricht jeder nur noch darüber.";
            posrep2 = " Also keine Neuigkeiten. Aber vielleicht weiß der " + GetAddress_Form(NPChar, false) + " Kapitän etwas?";
            answ1 = RandPhraseSimple("Dann erzähl mir lieber was anderes...",RandSwear() + "Du weißt nichts! Na gut, dann wollte ich dich noch etwas fragen...");
            answ2 = RandPhraseSimple("Du sagst, du weißt nichts – na schön, sag mir dann...","Du hast mir nicht wirklich geholfen"+NPCharSexPhrase(NPChar, "","e")+", aber vielleicht weißt du noch etwas?");
            answ3 = RandPhraseSimple("Ich glaube nicht, dass ich etwas weiß, das Sie interessieren würde.","Ich erzähle gern etwas, aber ein andermal.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Leider weiß ich nichts mehr, lassen Sie mich bitte gehen.","Ihre Fragen ermüden mich, entschuldigen Sie, aber ich habe zu tun."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Danke, ich muss mich verabschieden.","Alles Gute.");
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---слухи дворян---////////////////////////////////////////////
	case "rumours_nobleman":	
        srum = SelectRumourEx("nobleman", NPChar);
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			if (pchar.sex == "man")
			{
				dialog.text = "Am Hafen munkelt man, dass Julie d'Armagnac, die Nichte des Gouverneurs, nur noch ein Schatten ihrer selbst ist. Einst strahlend und voller Leben, treibt sie nun mit unverkennbarer Trauer im Gesicht durch die Straßen. Die Stadtbewohner tuscheln und rätseln, was ihr widerfahren sein könnte, doch niemand kennt die Wahrheit. Vielleicht hat irgendein Schurke ihr das Herz gebrochen? Vielleicht waren Sie es, Hauptmann?";
			}
			dialog.text = "Am Hafen munkelt man, dass Julie d'Armagnac, die Nichte des Gouverneurs, nur noch ein Schatten ihrer selbst ist. Einst strahlend und voller Leben, treibt sie nun mit unverkennbarer Trauer im Gesicht durch die Straßen. Die Stadtbewohner tuscheln und rätseln, was ihr widerfahren sein könnte, doch niemand kennt die Wahrheit. Vielleicht hat irgendein Schurke ihr das Herz gebrochen?"+GetSexPhrase(" Vielleicht waren Sie es, Hauptmann?","")+"";
			link.l1 = ""+GetSexPhrase("Ich bezweifle das. ","")+"Danke, ich sollte gehen.";
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
            posrep1 = RandPhraseSimple(" So ist das also...", " Also gut.");
            posrep2 = " Ja, das ist alles. Ich habe dem nichts mehr hinzuzufügen.";
            answ1 = RandPhraseSimple("Interessante Dinge erzählen Sie da, mein Herr! Aber darf ich noch etwas fragen...",
"Erlauben Sie mir noch eine Frage...");
            answ2 = RandPhraseSimple("Das ist sehr interessant! Ich wollte Sie noch etwas fragen...","Noch eine Frage, bitte.");
            answ3 = RandPhraseSimple("Die seltsamsten Dinge geschehen! Darf ich noch etwas fragen...","Ich danke Ihnen, mein Herr. Aber vielleicht wissen Sie noch etwas...");
            answ4 = "";
        }
        else
        {
            posrep1 = " Bei uns passiert selten etwas. Aber wenn mal etwas Ungewöhnliches geschieht, spricht jeder darüber.";
            posrep2 = " Also keine Neuigkeiten. Aber vielleicht weiß der " + GetAddress_Form(NPChar, false) + " Kapitän etwas?";
            answ1 = RandPhraseSimple("Dann erzähl mir lieber was anderes...",RandSwear() + "Du weißt nichts! Na gut, dann wollte ich dich noch etwas fragen...");
            answ2 = RandPhraseSimple("Du sagst, du weißt nichts – gut, dann sag mir...","Du hast mir nicht wirklich geholfen"+NPCharSexPhrase(NPChar, "","e")+", aber vielleicht weißt du noch etwas?");
            answ3 = RandPhraseSimple("Ich glaube nicht, dass ich etwas weiß, das Sie interessieren würde.","Ich würde gern etwas erzählen, aber ein andermal.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Ich glaube, ich habe mich klar ausgedrückt – das war alles.","Ihre Fragen ermüden mich, Kapitän. Gehen Sie bitte und kümmern Sie sich um Ihre Angelegenheiten!"),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Danke, ich muss mich verabschieden.","Alles Gute.");
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
			dialog.text = "Am Hafen munkelt man, dass Julie d'Armagnac, die Nichte des Gouverneurs, nur noch ein Schatten ihrer selbst ist. Einst strahlend und voller Leben, treibt sie nun mit unverkennbarer Trauer im Gesicht durch die Straßen. Die Stadtbewohner tuscheln und rätseln, was ihr widerfahren sein könnte, doch niemand kennt die Wahrheit. Vielleicht hat irgendein Schurke ihr das Herz gebrochen?"+GetSexPhrase(" Vielleicht waren Sie es, Hauptmann?","")+"";
			link.l1 = ""+GetSexPhrase("Ich bezweifle das. ","")+"Danke, ich sollte gehen.";
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
            posrep1 = RandPhraseSimple(" So ist das also...", " Vielleicht finden Sie das amüsant.");
            posrep2 = " Ja, das ist alles. Ich habe dem nichts mehr hinzuzufügen.";
            answ1 = RandPhraseSimple("Interessante Dinge erzählen Sie da, meine Dame! Aber darf ich noch etwas fragen...", "Erlauben Sie mir noch eine Frage...");
            answ2 = RandPhraseSimple("Das ist sehr interessant! Ich wollte Sie noch etwas fragen...","Noch eine Frage, bitte.");
            answ3 = RandPhraseSimple("Die seltsamsten Dinge geschehen auf der Welt! Darf ich noch etwas fragen...","Ich danke Ihnen, meine Dame. Aber vielleicht wissen Sie noch etwas...");
            answ4 = "";
        }
        else
        {
            posrep1 = " Bei uns passiert selten etwas. Aber wenn mal etwas Ungewöhnliches geschieht, spricht jeder darüber.";
            posrep2 = " Also keine Neuigkeiten. Aber vielleicht weiß der " + GetAddress_Form(NPChar, false) + " Kapitän etwas?";
            answ1 = RandPhraseSimple("Dann erzähl mir lieber was anderes...",RandSwear() + "Du weißt nichts! Na gut, dann wollte ich dich noch etwas fragen...");
            answ2 = RandPhraseSimple("Du sagst, du weißt nichts – na schön, sag mir dann...","Du hast mir nicht wirklich geholfen"+NPCharSexPhrase(NPChar, "","e")+", aber vielleicht weißt du noch etwas?");
            answ3 = RandPhraseSimple("Ich glaube nicht, dass ich etwas weiß, das Sie interessieren würde.","Ich erzähle gern etwas, aber ein andermal.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Ich glaube, ich habe mich klar ausgedrückt – das war alles.","Ihre Fragen ermüden mich, Kapitän. Gehen Sie bitte und kümmern Sie sich um Ihre Angelegenheiten!"),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Danke, ich muss mich verabschieden.","Alles Gute.");
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
			dialog.text = "Vorgestern gab es einen dreisten Mordversuch auf den Hafenmeister! Der Attentäter wartete am Ausgang des Büros auf ihn, aber er schaffte es, um Hilfe zu rufen. Ein Musketier kam rechtzeitig und verwundete den Angreifer, aber dem Verbrecher gelang die Flucht aus der Stadt\nMan sagt, der Hafenmeister bietet eine großzügige Belohnung für seinen Kopf! Bisher haben sich keine mutigen Seelen gemeldet. Wissen Sie, selbst wenn er tausend Dublonen anbieten würde - ich würde nicht zustimmen...";
			link.l1 = "Danke, ich sollte gehen.";
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
            posrep1 = RandPhraseSimple(" So ist es eben...", " Vielleicht finden Sie das interessant.");
            posrep2 = " Hey, Kapitän, haben Sie irgendwelche Neuigkeiten für unsere Kolonie?";
            answ1 = RandPhraseSimple(RandSwear() + "Das ist wirklich interessant, "+GetFullName(NPChar)+".",
                                 "Dann erzähl mir weiter...");
            answ2 = RandPhraseSimple(RandSwear() + "Wie auch immer, erzähl mir einfach etwas anderes...","Ja, du warst nicht sehr hilfreich, hast du sonst noch was für mich?");
            answ3 = RandPhraseSimple("Nun, alles kann in dieser Welt passieren. Tut mir leid, aber ich habe nichts Besonderes zu erzählen.","Ich habe es ziemlich eilig, also vielleicht beim nächsten Mal.");
            answ4 = "";
        }
        else
        {
            posrep1 = " Hier ist es ziemlich langweilig. Wenn also mal etwas passiert, redet jeder sofort darüber.";
            posrep2 = " Nichts Interessantes. Vielleicht weiß der " + GetAddress_Form(NPChar) + " etwas?";
            answ1 = RandPhraseSimple("Dann erzähl mir darüber...",RandSwear() + "Du weißt gar nichts! Na gut, anderes Thema...");
            answ2 = RandPhraseSimple("Wie auch immer, erzähl mir einfach etwas anderes...","Ja, du warst nicht sehr hilfreich, hast du sonst noch was für mich?");
            answ3 = RandPhraseSimple("Ich bezweifle, dass ich etwas Interessantes zu erzählen habe.","Gern, aber sprechen wir ein andermal.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Ach, ich habe nichts mehr zu erzählen, lass mich durch.","Ich habe genug von deinen Fragen, entschuldige mich, ich habe eine Menge anderer Dinge zu tun."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Danke, ich sollte gehen.","Auf Wiedersehen.");
		link.l2.go = "exit";
	break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_habitue":
		//-->работорговец
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
        {
			dialog.text = "(singt) Einmal traf ich ein Schiff aus Hamburg. An den Masten - Asseln und grüner Schimmel, das Holz faul, das Heck voller Muscheln. Die Kajüte voller Wanzen, die Kombüse... nun ja. Wie läuft's, Seem" + GetSexPhrase("ann", "frau") + "? Erzähl mal. Wie ist es da draußen auf See?";
            link.l1 = "Auf See ist alles beim Alten – nass und salzig. Sag du mir lieber: Weißt du vielleicht, wohin mein Kumpel verschwunden ist, der kürzlich hier ein Zimmer gemietet hatte? Sein Name ist François Gonthier.";
            link.l1.go = "Jamaica_ratH_1";
			break;
        }
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "(singt) Ich bin dem Whiskey dankbar für meine purpurrote Nase, und auf seinen Rat hin verpfändete ich meinen Mantel... Gieß ein, Seem" + GetSexPhrase("ann", "frau") + "! Bin gerade erst aus dem Einsatz zurück und noch nicht ganz nüchtern.";
            link.l1 = "Lass es dir schmecken, mein Freund! Und, wie war’s auf See, hast du was Interessantes erlebt?";
            link.l1.go = "EscapeSlave_Villemstad_H1";
			break;
        }
		//<--работорговец
				
		//Голландский Гамбит, против всех
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "LetterToLucasSent" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "Ach, das Meer... Wie gern wäre ich an deiner Stelle!";
            link.l1 = "Na, was hindert dich daran, Freund? Komm mit, ich nehme dich als Matrosen auf mein Schiff.";
            link.l1.go = "Lucas_Tavern";
			break;
        }
		//Голландский Гамбит
		
		//--> поиск дезертира
		if (CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE && !CheckAttribute(npchar, "quest.fugitive"))
        {
			dialog.text = LinkRandPhrase("Trink Rum, sei mutig – und du hast hundert Freunde! Ha-ha!", "Kipp einen guten Krug – und selbst der Kerkermeister wirkt charmant! Ha-ha!", "Rum und Ale zeigen dir das Paradies – also einschenken und trinken! Ha-ha!");
            link.l1 = "Trinken wir, mein Freund... Sag mal, ist hier in eurem Dorf jemand namens "+pchar.GenQuest.FindFugitive.Name+" aufgetaucht? Er war mal mein Kamerad. Gute Leute meinten, er sei hierher unterwegs gewesen...";
            link.l1.go = "FindFugitiveHb";
			break;
        }
		//<-- поиск дезертира
		
		//--> карибские нравы
		if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && npchar.location == "Portobello_tavern")
		{
			dialog.text = "Nachrichten? Ha! Hast du es noch nicht gehört? Unsere Soldaten haben einen französischen Spion gefangen. Verfluchter Hochstapler, versuchte sich als Händler auszugeben, aber *hicks* - unser Kommandant ist ein harter Bastard!";
            link.l1 = "Du sagst es nicht! Und was hat dieser Frosch versucht zu erschnüffeln?";
            link.l1.go = "trial_spy";
			break;
		}
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	    {
			dialog.text = "Eh, "+GetAddress_Form(pchar)+" was für eine Welt, in der wir leben... Scheiß Bastarde überall!";
			link.l1 = "Was meinst du, Kamerad?";
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
			break;
		}
		//<-- карибские нравы
		
		//--> Sinistra Длинные тени старых грехов
		if (CheckAttribute(pchar, "questTemp.DTSG_NightIskat") && npchar.city == "SentJons")
        {
			dialog.text = "Hast du es schon gehört?! Ich kann es nicht glauben! Der berühmte Kapitän Fleetwood wurde brutal in London ermordet! Jagte nach Ruhm, hatte alles und fand nur den Tod... Wäre er hier geblieben, wäre er sicherer. Ich sage, manchmal ist es besser zu schätzen, was man hat, anstatt nach Geld oder Rang zu jagen, merk dir meine Worte, Herr!";
            link.l1 = "Freund, du weißt, wo jeder in der Kolonie wohnt, nicht wahr?";
            link.l1.go = "DTSG_NightIskat";
			break;
        }
		//<-- Длинные тени старых грехов
		
		//--> Rebbebion, квест "Путеводная звезда"
		if (CheckAttribute(pchar, "questTemp.Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.Sotta") && !CheckAttribute(npchar, "questTemp.Lutter") && npchar.city == "Beliz")
		{
			link.l1 = "Also, der Held des Tages, Kapitän Edgardo Sotta. Was sagen die Leute über ihn? Und was denkst du? Ich habe mich darauf gefreut, den Mann zu treffen.";
			link.l1.go = "Sotta1";
			link.l2 = "Kumpel, warum trinkst du alleine? Jeder versammelt sich gerade, um die Hängung des Windbeutels Matt zu beobachten.";
			link.l2.go = "Lutter1";
			break;
		}
		
		if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(pchar, "questTemp.PZ.TortugaHabitueBlock") && npchar.city == "Tortuga")
		{
			link.l1 = "Hör zu, Kumpel, ich habe versucht, jemanden namens Joep van der Vink zu finden. Ich muss ihm eine Nachricht überbringen. Weißt du, wie er aussieht oder irgendetwas über ihn?";
			link.l1.go = "Sepp1";
			break;
		}
		//<-- квест "Путеводная звезда"
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Habt ihr es gehört? Man sagt, Thomas Morrisons Tochter liegt nun schon seit einem halben Jahr im Bett. Die Ärzte sind völlig machtlos gegenüber ihrer Krankheit. Die Einzige, die ihr helfen könnte, ist eine Zigeunerin, die für ihre Tränke bekannt ist, die selbst schwer Erkrankte wieder auf die Beine bringen. Doch sie hat sich strikt geweigert, etwas für das arme Mädchen zu tun.";
			link.l1 = RandPhraseSimple(RandSwear()+"Das ist einen weiteren Becher wert...","Gut, trinken wir noch einmal.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Danke, ich sollte gehen.","Eh, verdammt guter Rum. Gut, ich sollte gehen, hab hier Spaß.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_gypsy", "gipsy_2", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "dwh_gypsy_0";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Vorgestern gab es einen dreisten Mordversuch auf den Hafenmeister! Der Attentäter wartete am Ausgang des Büros auf ihn, aber er schaffte es, um Hilfe zu rufen. Ein Musketier kam rechtzeitig und verwundete den Angreifer, aber dem Verbrecher gelang die Flucht aus der Stadt\nMan sagt, der Hafenmeister bietet eine großzügige Belohnung für seinen Kopf! Bisher haben sich keine mutigen Seelen gemeldet. Wissen Sie, selbst wenn er tausend Dublonen anbieten würde - ich würde nicht zustimmen...";
			link.l1 = RandPhraseSimple(RandSwear()+"Das ist einen weiteren Becher wert...","Gut, trinken wir noch einmal.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Danke, ich sollte gehen.","Eh, verdammt guter Rum. Gut, ich sollte gehen, hab hier Spaß.");
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
			dialog.text = "Habt Ihr die Neuigkeiten gehört?! Eine himmelschreiende Schande ist das! Kein Tropfen Rum oder Wein mehr in der Taverne - wie soll man bei dieser verdammten Hitze Erleichterung finden? Der Wirt füttert uns seit einer Woche mit leeren Versprechungen, dass der Trank bald wieder fließen wird, aber nichts ist geschehen! Sollen wir etwa unsere Kehlen bis zum Jüngsten Gericht austrocknen lassen?";
			link.l1 = RandPhraseSimple(RandSwear()+"Das ist einen weiteren Becher wert...","Gut, trinken wir noch einmal.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Danke, ich sollte gehen.","Eh, verdammt guter Rum. Gut, ich sollte gehen, hab hier Spaß.");
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
			dialog.text = "Das Gerücht an den Docks besagt, dass unser Schankwirt in Schwierigkeiten steckt! Jemand hat seinen Gin gestohlen! Nicht nur eine Flasche, wohlgemerkt, sondern ein ganzes Fass davon - von der Sorte, die man sonst nirgendwo auf diesen Inseln findet! Direkt aus Europa gebracht, so sagt man. Der alte Fuchs will nicht verraten, für wen er es aufbewahrte, aber eines ist sicher: Wenn dieses Fass nicht bald auftaucht, wird der arme Kerl die Hölle bezahlen müssen!";
			link.l1 = RandPhraseSimple(RandSwear()+"Das ist einen weiteren Becher wert...","Gut, trinken wir noch einmal.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Danke, ich sollte gehen.","Eh, verdammt guter Rum. Gut, ich sollte gehen, hab hier Spaß.");
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
			dialog.text = "Am Hafen munkelt man, dass Julie d'Armagnac, die Nichte des Gouverneurs, nur noch ein Schatten ihrer selbst ist. Einst strahlend und voller Leben, treibt sie nun mit unverkennbarer Trauer im Gesicht durch die Straßen. Die Stadtbewohner tuscheln und rätseln, was ihr widerfahren sein könnte, doch niemand kennt die Wahrheit. Vielleicht hat irgendein Schurke ihr das Herz gebrochen?"+GetSexPhrase(" Vielleicht waren Sie es, Hauptmann?","")+"";
			link.l1 = RandPhraseSimple(RandSwear()+"Das ist einen weiteren Becher wert...","Gut, trinken wir noch einmal.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Danke, ich sollte gehen.","Eh, verdammt guter Rum. Gut, ich sollte gehen, hab hier Spaß.");
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
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Man munkelt, dass der Fischer Pierre Carno spurlos verschwunden ist. Vor zwei Morgenröten segelte er aufs Meer hinaus und seither kein Zeichen von ihm. Seine Frau Lea ist außer sich vor Kummer. Bei Tageslicht und Laternenschein hält sie am Pier Wache, den Blick auf das endlose Wasser gerichtet, betend um einen flüchtigen Blick auf das Segel ihres Geliebten.";
			link.l1 = RandPhraseSimple(RandSwear()+"Das ist einen weiteren Becher wert...","Gut, trinken wir noch einmal.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Danke, ich sollte gehen.","Eh, verdammt guter Rum. Gut, ich sollte gehen, hab hier Spaß.");
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
			dialog.text = "Kapitän, habt Ihr gehört? In unserem Wirtshaus arbeitet eine neue Kellnerin. Man sagt, sie sei eine wahre Schönheit. Männer von überall her eilten herbei, nur um einen Blick auf sie zu erhaschen. Aber vor drei Tagen erschien sie nicht zur Arbeit, was den Wirt sehr verärgerte, der seit ihrer Ankunft enorme Gewinne erzielte. Man sagt, er sei sogar bereit, demjenigen zu bezahlen, der das Mädchen finden kann.​";
			link.l1 = RandPhraseSimple(RandSwear()+"Das ist einen weiteren Becher wert...","Gut, trinken wir noch einmal.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Danke, ich sollte gehen.","Eh, verdammt guter Rum. Gut, ich sollte gehen, hab hier Spaß.");
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
		
		Dialog.Text = LinkRandPhrase("Nun... hic! ","Ach, guter Rum! ","Nun... ")+SelectRumourEx("Stammgast",NPChar);
		link.l1 = RandPhraseSimple(RandSwear()+"Das ist einen weiteren Becher wert...","Gut, trinken wir noch einmal.");
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple("Danke, ich sollte gehen.","Eh, verdammt guter Rum. Gut, ich sollte gehen, hab hier Spaß.");
		link.l2.go = "exit_sit";
	break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
            if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader!= 3 )
            strum = SelectRumourEx("trader", NPChar);
            else strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
			Dialog.Text = NPCStringReactionRepeat(strum,strum+"Jawohl. Nichts mehr zu erzählen.",strum+" Jetzt sollte ich zurück zur Arbeit gehen.",RandPhraseSimple("Ich habe dir schon gesagt, dass ich keine Zeit für billige Gespräche habe!","Ich bin ein beschäftigter Mann, ich habe keine Zeit, um Klatsch zu reden!"),"block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear()+"Interessant! Aber kommen wir zur Sache","Dankbarkeit, hier ist noch eine Sache."),pcharrepphrase(""+GetSexPhrase("Verdammt mich","Interessant")+"! Feiner Geschichtenerzähler. Aber ich habe noch eine Frage.","Lassen wir keine Zeit mehr verstreichen und reden wir Geschäftliches."),pcharrepphrase(RandSwear()+" Noch eine Sache und ich gehe.","Du hast recht, Zeit ist Geld."),pcharrepphrase("Immer nur an deinen eigenen Profit denken! Gut, dreh nicht durch.","Verzeih mir. Lass uns Geschäfte machen."),npchar,Dialog.CurrentNode);
			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Lebewohl, du alter Säufer.","Auf Wiedersehen, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("Verflucht! Geh nicht weit weg. Ich komme gleich wieder.","Freut mich, dich zu sehen, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"! Lebewohl!")),NPCharRepPhrase(npchar,pcharrepphrase("Leinen los!","Auf Wiedersehen!"),pcharrepphrase("He! Was versteckst du da? Rum? Nein!?! Egal, ich besorge mir etwas zu trinken.","Es tut mir leid, ich habe wichtige Geschäfte in der Stadt.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh! Bis zum nächsten Mal!","Ich sollte gehen. Tschüss, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("Streite nicht mit mir! Ich habe keine Lust darauf!","Ich denke, ich sollte mein Schiff überprüfen. Wir sehen uns, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("Was ist los mit dir, Kumpel? Ich bin's - "+GetFullName(pchar)+"! Mach ein Nickerchen, ich werde später mit dir reden.","Ich fürchte, dass dich deine Leber tötet, bevor ich wieder hierher komme."),pcharrepphrase("Zähle dein Silber, schlauer Hund! Wir sehen uns später.","Freut mich, dich zu sehen, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("Kapitän",NPChar);
			Link.l1 = RandPhraseSimple(RandSwear()+"Interessant! Es gibt noch eine Sache, die ich fragen möchte...","Noch eine Frage.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Danke, ich sollte gehen.","Auf Wiedersehen.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
		
		 case "rumours_landcaptain":
			Dialog.Text = SelectRumourEx("Landkapitän",NPChar);
			Link.l1 = RandPhraseSimple(RandSwear()+"Interessant! Es gibt noch eine Sache, die ich fragen möchte...","Noch eine Frage.");
			Link.l1.go = "question";
			Link.l2 = RandPhraseSimple("Danke, ich sollte gehen.","Auf Wiedersehen.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "question";
            NPChar.talk_date =  lastspeakdate();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06
				if(startHeroType == 4)
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Sie kennen den Preis. Informationen sind wie ein Zimmer, Essen oder Trinken - sie kosten. Das macht tausend Pesos.","Sie kennen den Preis. Informationen sind wie ein Zimmer, Essen oder Trinken - sie kosten. Das macht tausend Pesos.","Sie kennen den Preis. Informationen sind wie ein Zimmer, Essen oder Trinken - sie kosten. Das macht tausend Pesos."),"Nichts mehr hinzuzufügen. Nun, entschuldigen Sie mich, ich sollte gehen.","","","block",1,npchar,Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Eigentlich, warum frage ich überhaupt? Ich könnte jeden anderen danach fragen. Entschuldigung, dass ich dich belästigt habe.","Eigentlich, warum frage ich überhaupt? Ich kann jeden anderen danach fragen. Entschuldigung, dass ich Sie belästigt habe."),"","","",npchar,Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000)
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Ich weiß natürlich. Hier ist meine Bezahlung.","Ich weiß, natürlich. Hier ist meine Bezahlung."),"","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 = HeroStringReactionRepeat("Ich habe nicht so eine Summe.","","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
				}
				else
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Informationen kosten Geld. 1000 Pesos und ich erzähle dir alles, was ich weiß.","Etwas stimmt nicht mit meinem Gedächtnis, 1000 Acht-Reales-Stücke könnten mir helfen, mich an etwas zu erinnern.","Ich bin begierig darauf, Informationen mit Ihnen zu teilen. Aber es wird Sie 1000 Achtstücke kosten. Kein Feilschen."),"Nichts mehr hinzuzufügen. Jetzt entschuldigen Sie mich, ich sollte gehen.","","","block",1,npchar,Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear()+"Ich zahle nicht für wertloses Geschwätz.","Ich werde über bessere Möglichkeiten nachdenken, dieses Geld auszugeben."),"Lass uns das Thema wechseln.","Lassen wir das Thema wechseln.","Lassen wir das Thema wechseln.",npchar,Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000 )
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Du wirst sie haben, wenn ich etwas Würdiges von dir lerne.","Ich zahle, wenn du mir etwas von Wert gibst."),"","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 = HeroStringReactionRepeat("Ich habe nicht so viel Geld.","","","",npchar,Dialog.CurrentNode);
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
					Dialog.Text = "Unsere Patrouille hat kürzlich die Brigantine eines französischen Schmugglers namens Morel zerstört. Der Mann sitzt jetzt in den Verliesen und sieht dem Todesurteil ins Auge. Unser Kommandant glaubt, dass seine Schiffsladung nicht vollständig war, also sucht er immer noch danach... der Franzose wird sterben, wenn der Kommandant die fehlende Ladung findet.";
					link.l1 = "Interessant... Gut, nimm das Geld. Hast du sonst noch etwas zu erzählen?";
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
				Dialog.Text = "Es gab eine große Feier im Gouverneurspalast. Seine Exzellenz' Freund, Don Carlos de Milyar, ist zurück. Er wurde in einer Seeschlacht gefangen genommen, aber er schaffte es mit Hilfe eines französischen Leutnants zu entkommen. Don Carlos ist nicht nur klug, er ist auch ein sehr großzügiger Mann. Mit seiner Unterstützung ist dieser Leutnant, Jean Deno, nun Kapitän der 'Sario'. So weit ich gehört habe, wurde ihm auch eine kleine Plantage geschenkt. Jetzt wird der Froschfresser Juan genannt! Was für eine Geschichte!";
				link.l1 = "Intrigierend... Gut, das Geld gehört dir. Nimm das. Hast du noch etwas zu erzählen?";
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
				Dialog.Text = "Unser Kommandant hat zusätzliche Truppen zur Patrouille des Dschungels geschickt und die Anzahl der Wachen in der Stadt erhöht. Es gibt Gerüchte, dass die Engländer planen, in Philipsburg einzudringen und die gefangenen Offiziere zu befreien.";
				link.l1 = "Du sagst es! Haben sie tatsächlich die Eier, einen solchen Trick abzuziehen? Und von welchen Offizieren sprichst du genau?";
				link.l1.go = "FMQN_r";
				break;
			}	
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && npchar.location == "Havana_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "Neulich hat sich die ganze Stadt aufgeregt wie ein Hornissennest. Ein Offizier von einer Militärschaluppe wurde in meiner Taverne stockbetrunken und hat fast eine verheiratete Frau vergewaltigt. Dann hat er ihren Ehemann verprügelt, der versuchte, seine Frau zu verteidigen, und ihn sogar mit einem Schwert bedroht. Stell dir das mal vor, direkt vor der Stadtwache! Wie man so schön sagt, das Recht respektiert die Macht. Die Soldaten sahen einfach weg, während dieser Bastard wütete\nAber der Schurke wurde entwaffnet von, wer hätte das gedacht, einigen Seeleuten von einem Handelsschiff. Sie haben ihn fast in eine Schleife gewickelt, obwohl der Bastard entkam und sich auf seinem Schiff versteckte. Der Kommandant und der Alcalde versuchten, es unter den Teppich zu kehren, aber der empörte Ehemann ist ein angesehener Bürger, der sich an seine Exzellenz Don Diego de Toledo wandte und unter der örtlichen Gentry für Aufsehen sorgte\nSie erließen einen Haftbefehl für den Offizier. Es gab Gerüchte, dass seinem Kapitän vorgeschlagen wurde, den Hafen mit ihm zu verlassen und den Schurken an einen anderen Ort zu verlegen. Der Kapitän der Schoner, Esberdo Cabanas, ist jedoch ein Ehrenmann. Als er erfuhr, was sein Offizier getan hatte, verhaftete er ihn sofort und schickte ihn zurück an Land. Der Bastard verfault für die absehbare Zukunft im Gefängnis, wo er hingehört, wenn du mich fragst. Und dann wird er vielleicht zu einem gewöhnlichen Soldaten degradiert und ausgepeitscht, als Beispiel für andere.";
				link.l1 = "Warte, hast du Kapitän Esberdo Cabanas gesagt? Huh... eine spannende Geschichte, in der Tat! Gut, du hast dein Geld verdient, hier nimm. Gibt es noch etwas, was du mir erzählen könntest?";
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
				Dialog.Text = "Man sagt, einige Verbrecher wurden auf einer der unbewohnten Inseln ausgesetzt! Angeblich sind sie solch gnadenlose Ungeheuer, dass weder der Henker noch die heiligen Väter es wagten, sich mit ihnen anzulegen! Aber warum bringen sie sie immer hierher?!";
				link.l1 = "Hmm... wie interessant! Vielleicht sollte ich sie aufspüren und rekrutieren - ich bin immer auf der Suche nach verzweifelten Seelen... Warum so bleich, Kumpel? Ich mache nur Spaß, ich mache nur Spaß... Du hast dein Geld verdient - hier, nimm. Hast du sonst noch etwas Bemerkenswertes gehört?";
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
					link.l1 = "Es stellt sich heraus, dass du doch nichts weißt. Ich hätte nicht erwartet, dass du mich so hintergehst. Nicht besonders schlau. Nun, auf Wiedersehen.";
				}
				else
				{
					link.l1 = RandPhraseSimple("Wertloser Mist. Ich werde dir keinen einzigen Peso zahlen! Tschüss.","Deine Informationen kosten nichts, also bekommst du auch nichts.");
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
					link.l1 = "Wirklich? Interessant, danke. Nun, ich muss los, bis zum nächsten Mal.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = RandPhraseSimple("Danke, nimm das Geld. Hast du noch etwas zu erzählen?","Gut, nimm das Geld. Noch etwas zu erzählen?");
					link.l1.go = "rumours_tavern";
				}
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;

		case "rumours_tavern_no":
			if(startHeroType == 4)
			{
				Dialog.Text = "Du hättest mit ein paar Münzen helfen können. Im Gegensatz zu dir, Helen, habe ich nicht die Unterstützung des Barons der Bruderschaft.";
				link.l1 = "Du hast ein ganzes Etablissement. Und ich habe es alleine bis hierher geschafft. Nun, abgesehen von dem Schiff, den Kanonen, der Mannschaft und den Vorräten, die der Baron mir besorgt hat. Na gut, vergiss es.";
				link.l1.go = "exit";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
			else
			{
				Dialog.Text = "Versteh mich richtig, ich muss meine Familie ernähren.";
				link.l1 = "Lassen wir das Thema wechseln.";
				link.l1.go = "first time";
				NextDiag.CurrentNode = NextDiag.TempNode;
				link.l2 = LinkRandPhrase("Danke, ich sollte gehen.","Auf Wiedersehen.","Tschüss.");
				link.l2.go = "Exit";
			}
		break;	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("arm",NPChar);
				Link.l1 = RandPhraseSimple(RandSwear()+"Interessant. Noch eine Frage...","Hm, lass mich etwas anderes fragen...");
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple("Nun, leb wohl.","Tschüss, Kumpel.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("Ich habe dir alles erzählt, was ich wusste.","Es gibt nichts mehr zu teilen, tut mir leid...");
				Link.l1 = RandPhraseSimple("Ich verstehe. Lebewohl.","Auf Wiedersehen, Kumpel...");
				Link.l1.go = "exit";			
			}
            NPChar.talk_date = lastspeakdate();
		break;
        case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("arm",NPChar);
				Link.l1 = RandPhraseSimple(RandSwear()+"Interessant. Noch eine Frage...","Hm, lass mich etwas anderes fragen...");
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple("Nun, lebewohl.","Tschüss, Kumpel.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("Ich habe dir alles gesagt, was ich weiß.","Es gibt nichts mehr zu teilen, tut mir leid...");
				Link.l1 = RandPhraseSimple("Ich verstehe. Lebewohl.","Verstanden. Auf Wiedersehen, Kumpel...");
				Link.l1.go = "exit";			
			}
			NPChar.talk_date = lastspeakdate();
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC",NPChar);
				Link.l1 = RandPhraseSimple("Verstanden...","Ich sehe...");
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else  
			{
				Dialog.Text = NPCharSexPhrase(npchar,RandPhraseSimple("Ich habe dir alles erzählt, was ich wusste.","Ich habe nichts Neues gehört, tut mir leid..."),RandPhraseSimple("Ich habe dir alles erzählt, was ich wusste.","Ich habe nichts Neues gehört, tut mir leid..."));
				Link.l1 = RandPhraseSimple("Ich verstehe, dann auf Wiedersehen.","Verstanden. Lebewohl, Kamerad.");
				Link.l1.go = "exit";			
			}
		break;
		
//Jason -------------слухи смотрителей маяков, идентичны таверне, но бесплатны, по 1 шт за день--------------------
		case "rumours_lighthouse": 
			Dialog.Text = NPCStringReactionRepeat(RandPhraseSimple("Eh, Kapitän! Es ist immer schön, mit Ihnen zu plaudern. Alleine hier zu sein ist manchmal ziemlich langweilig...","Ich lebe allein, Besucher sind eine seltene Gelegenheit. Also bin ich immer in Stimmung zum Reden."),"Wie wär's mit einem Plausch, Käpt'n? Nun, ich könnte noch etwas anderes zu erzählen haben...","Nimm beim nächsten Besuch bei mir eine Flasche Rum mit. Gespräche sind besser mit Getränken...","Ach, ich habe dir alles erzählt, was ich wusste. Ich habe nichts hinzuzufügen.","block",1,npchar,Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Dann teile deine Informationen. Ich unterhalte mich gern mit Leuten, weißt du...","Sag mir! Wie sie sagen, wer die Information besitzt - er besitzt die Welt?"),"Wie bitte?","Aber natürlich! Hast du noch etwas zu teilen?","Gut, wir hatten sowieso ein nettes Gespräch.",npchar,Dialog.CurrentNode);
    		link.l1.go = HeroStringReactionRepeat("rumours_lighthouse_yes", "rumours_lighthouse_void", "rumours_lighthouse_void", "exit", npchar, Dialog.CurrentNode);
		break;
		
		case "rumours_lighthouse_yes":
            RumText = SelectRumourEx("tavern", NPChar);
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("Danke! Noch etwas?","Sehr interessant! Noch etwas?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Dankbarkeit! Es war ziemlich unterhaltsam...","Danke, dass du es mir erzählt hast!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                Dialog.Text = RumText;
    			link.l1 = RandPhraseSimple("Danke dir! Noch etwas?","Sehr interessant! Noch etwas?");
    			link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Dankbarkeit! Es war ziemlich unterhaltsam...","Danke, dass du es mir erzählt hast!");
			    link.l2.go = "exit";
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;
		
		case "rumours_lighthouse_void":
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("Danke dir! Sonst noch etwas?","Sehr interessant! Noch etwas?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Dankbarkeit! Es war ziemlich unterhaltsam...","Danke, dass Sie es mir gesagt haben!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
		break;
//Jason ------------------------------------почтовый генератор 2 уровня-------------------------------------------
		case "Postcureer_LevelUp_ForAll":
			//начинаем проверять
			if (!CheckCharacterItem(pchar, pchar.questTemp.WPU.Current.Item))
			{
				dialog.text = "Aber wo ist das Paket? Hast du es nicht?";
	        	link.l1 = "Nun... Ich sollte es dir liefern. Aber es wurde... um ganz ehrlich zu sein, es wurde mir genommen. Ich konnte mich nicht wehren und gab den Angreifern das Paket selbst.";
	        	link.l1.go = "Postcureer_LevelUp_complete_fail";
				break;
			}
			
			if (sti(pchar.questTemp.WPU.Postcureer.AgentChance) == 4)//раскрыли обман
			{
				dialog.text = "Hm. Entschuldigung, aber das Paket wurde zuvor geöffnet! Das ist mir kristallklar. Das Siegel wurde neu gestempelt...";
	        	link.l1 = ""+GetAddress_FormToNPC(NPChar)+", es ist das Paket, das ich im Hafenbüro bekommen habe "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+", und ich habe keine Ahnung...";
	        	link.l1.go = "Postcureer_LevelUp_complete_Agentfail";
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				int iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money)/(sti(iTime)+1));//сильно снижаем оплату
				dialog.text = "Ich habe auf dich gewartet. Aber du bist "+FindRussianDaysString(iTime)+" zu spät! Die Informationen, die du trägst, sind viel weniger nützlich geworden... Sie haben natürlich noch einen gewissen Wert, also werde ich dich bezahlen "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+". Bitte, nimm das Geld und leb wohl.";
	        	link.l1 = "Danke. Ich vermute.";
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
				dialog.text = "Also bist du es! Ich habe schon eine Weile auf dich gewartet, habe sogar Schritte unternommen, um das Paket zu beschaffen. Gib es mir. Ich brauche es jetzt wirklich nicht, dank deiner Zeitplanung, aber ich möchte es für mich behalten\nWie du verstehst, kann ich dir nichts zahlen, aber ich werde dafür sorgen, dass dein guter Name wiederhergestellt wird.";
	        	link.l1 = "Danke... glaube ich. Es tut mir leid für die Verzögerung, wirklich. Auf Wiedersehen.";
	        	link.l1.go = "Postcureer_LevelUp_complete_bad";
				break;
			}
			dialog.text = "Ich habe auf dich gewartet. Du kommst gerade rechtzeitig, die Informationen, die du mir gebracht hast, werden nützlich sein. Bitte, nimm dieses Geld für deine Arbeit - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+". Meinen Dank für deine Zeit.";
        	link.l1 = "Sie sind willkommen. Auf Wiedersehen!";
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
			dialog.text = "Eh, ich wusste, dass es so enden würde... Ich hätte ein militärisches Kurierschiff anheuern sollen, nicht einen zivilen Kapitän... Was auch immer, "+GetAddress_Form(NPChar)+", Sie sind kein Soldler, also gibt es nichts, Ihnen vorzuwerfen. Auf Wiedersehen.";
			link.l1 = "Auf Wiedersehen, "+GetAddress_FormToNPC(NPChar)+".";
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
			dialog.text = "Herr, ich kenne den Hafenmeister von "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+" persönlich, er ist ein ehrlicher Mann. Außerdem gab es für ihn keinen Grund, das Paket zu öffnen. "+GetAddress_Form(NPChar)+", du bist ein Betrüger! Ich werde dir keinen einzigen Kupfer bezahlen. Verpiss dich!";
			link.l1 = "Hm...";
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
			dialog.text = "Sah aus wie wandelnder Müll. Ein Vagabund oder ein Bettler. Kann nicht sagen, wohin genau er gegangen ist, ich hatte keine Lust, ihm zu folgen.";
			link.l1 = "Besser als nichts. Danke! Ich sollte gehen.";
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
			Dialog.Text = "Nicht vor langer Zeit wurde ein englisches Schiff in den Gewässern von Sint-Maarten erobert, es transportierte einige hochrangige Offiziere. Es wurde entschieden, sie nach Willemstad zu schicken, aber im Moment werden sie hier in unseren komfortablen Verliesen festgehalten. Man sagt, dass einer der gefangenen Soldaten unserem Kommandanten von den Absichten der Engländer berichtet hat, eine Razzia zur Rettung der Offiziere zu schicken. Deshalb ist unser guter alter Kommandant bereit und bewaffnet. Warum sollte er es nicht sein, wenn die Gefangenen weg sind, wird er zu einem gewöhnlichen Soldaten degradiert!";
			link.l1 = "Intrigant... Gut, das Geld ist deins. Nimm das. Hast du noch etwas zu erzählen?";
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
            Dialog.Text = RandPhraseSimple("Sehr gut dann. Ich habe das Paket hier, bereit zur Lieferung. Nimm es\nKomm nicht hierher und sprich nicht mehr mit mir, es ist zu gefährlich. Pass auf dich auf da draußen...","Hm, großartig. Nimm das Paket und stelle sicher, dass du es dem Mann überbringst, über den wir gerade gesprochen haben\nAuf Wiedersehen und sprich nicht mehr mit mir, es ist zu gefährlich.");
            link.l1 = RandPhraseSimple("Hab's verstanden. Auf Wiedersehen...","Auf Wiedersehen und viel Glück.");
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
			dialog.text = LinkRandPhrase("Ein Raubüberfall mitten am Tag!!! Wirklich?! Bleib wo du bist, Kumpel...","He, was machst du da?! Es scheint, als wollte mich jemand ausrauben. Du bist erledigt...","Warte, wohin gehst du? Ein Dieb! Ende der Linie, Kumpel...");
			link.l1 = LinkRandPhrase("Mist!","Verdammt!","Verdammt!");
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
	STR_MAYOR[0] = "Oh, der Herr Gouverneur ist ein wunderbarer Mensch. Er leitet unsere Kolonie geschickt — seit ihrer Gründung gab es keinen einzigen größeren Konflikt\nSein einziger Makel ist, dass er... hmm... sehr sparsam ist. Obwohl das vielleicht eher eine Tugend ist.";
	STR_MAYOR[1] = "Oh, der Herr Gouverneur ist ein wunderbarer Mensch. Er leitet unsere Kolonie geschickt — seit ihrer Gründung gab es keinen einzigen größeren Konflikt\nSein einziger Makel ist, dass er... hmm... sehr sparsam ist. Obwohl das vielleicht eher eine Tugend ist.";
	STR_MAYOR[2] = "Leider ist unser Gouverneur ein guter Mensch... aber charakterlich schwach. Mit etwas mehr Entschlossenheit hätten unsere Händler kleine Steuererleichterungen erhalten... Und die Subventionen für die Reparatur des Forts wären längst bereitgestellt worden.";
	STR_MAYOR[3] = "Hmm... Er ist erst kürzlich unser Gouverneur geworden. Er ist ziemlich jung und daher sehr initiativ — unter seiner Führung blüht unsere Kolonie auf.";
	STR_MAYOR[4] = "Unser Gouverneur ist noch relativ jung. Man sagt, er sei der ungeratene jüngste Sohn eines spanischen Grafen, der vom Hof verbannt wurde, um die Familie nicht weiter zu blamieren. Er wurde erst kürzlich hierher versetzt und hatte noch keine Gelegenheit, sich auszuzeichnen.";
	STR_MAYOR[5] = "Hmm... Er ist erst kürzlich unser Gouverneur geworden. Er ist ziemlich jung und daher sehr initiativ — unter seiner Führung blüht unsere Kolonie auf.";
	STR_MAYOR[6] = "Äh... Ich kann nichts Schlechtes über ihn sagen.";
	
	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; // Тавернщики
	STR_TAVERNKEEPER[0] = "Hm, ich würde diesem Halunken mein Eigentum nicht anvertrauen. Verstehen Sie mich nicht falsch, aber ich glaube, er ist der unzuverlässigste Mensch in unserer Stadt. Man sagt, er hat mit Schmugglern und Piraten zu tun – und in seiner Taverne treiben sich ständig zwielichtige Gestalten herum!";
	STR_TAVERNKEEPER[1] = "Was kann man über ihn sagen! Er ist feige und nicht besonders klug. Außerdem ist er geldgierig, was ihn ständig in Schwierigkeiten bringt! Aber er ist immer über alle Neuigkeiten informiert.";
	STR_TAVERNKEEPER[2] = "Ein recht angenehmer Typ. In seiner Taverne ist es immer gemütlich, und er hat einen guten Sinn für Humor. Vor allem sorgt er für Ordnung und lässt keine betrunkenen Raufbolde anständige Bürger belästigen.";
	STR_TAVERNKEEPER[3] = "Ein erstaunlicher Mensch. Er sollte eher als Informant für die geheime Kanzlei arbeiten als eine Taverne führen. Manchmal scheint es, als wüsste er alles, was in unserer Stadt vor sich geht. Das ist schon unheimlich.";
	STR_TAVERNKEEPER[4] = "Ich weiß nicht, was ich Ihnen über ihn sagen soll. Ein Mensch wie jeder andere. Er führt eine Taverne und ist daher über alle Neuigkeiten unserer Insel informiert.";
	STR_TAVERNKEEPER[5] = "Man sagt, man kann sich auf ihn verlassen. Andererseits habe ich gehört, dass er unnötige Risiken meidet und seine Geschäfte stets kalkuliert führt. Und mit dunklen Machenschaften scheint er nichts zu tun zu haben.";
	STR_TAVERNKEEPER[6] = "Die Taverne hat er von seinem Vater geerbt. Sein Vater führte eine Taverne nicht weit von hier auf der kleinen Insel Hairoch in einem anderen Archipel. Später zog der Vater hierher, baute eine neue Taverne, und nun leitet sein Sohn sie.";

	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; // Верфисты
	STR_SHIPYARDER[0] = "Er baut gute Schiffe... Aber als Mensch ist er schwer einzuschätzen – er lebt ruhig und zurückgezogen. Wahrscheinlich ein guter Kerl.";
	STR_SHIPYARDER[1] = "Er baut gute Schiffe... Aber als Mensch ist er schwer einzuschätzen – er lebt ruhig und zurückgezogen. Wahrscheinlich ein guter Kerl.";
	STR_SHIPYARDER[2] = "Ein anständiger Mensch, aber man sagt, er sei übermäßig streng. Er tadelt seine Arbeiter ständig. Deshalb wechselt das Personal oft. Trotzdem ist er ein ausgezeichneter Schiffbauer.";
	STR_SHIPYARDER[3] = "Ein sehr gebildeter Mann. Man sagt, er habe Schiffbau in England und dann in Holland studiert. Und schließlich landete er hier – fern der Heimat, in einem abgelegenen Archipel. Es heißt, er habe sich einst mit der Heiligen Inquisition überworfen und musste in die Kolonien fliehen.";
	STR_SHIPYARDER[4] = "Ja, der alte Mann taugt nicht mehr viel. Er träumt ständig von alten Zeiten und murrt, wenn man etwas anderes als eine Karavelle oder eine Galeone bestellt.";
	STR_SHIPYARDER[5] = "Ein großartiger Kerl. Immer bereit zu helfen, einen aus der Patsche zu ziehen. Und für ein so abgelegenes Nest baut er wirklich gute Schiffe.";
	STR_SHIPYARDER[6] = "Er war ein Verbannter in unserer Kolonie, bis sich herausstellte, dass er Talent im Schiffbau hatte. Nachdem unter seiner Leitung zwei prächtige Briggs gebaut wurden, wurden ihm seine Vergehen verziehen und er ist jetzt ein vollwertiges Mitglied unserer Gesellschaft.";

	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; // Магазинщики
	STR_TRADER[0] = "Ich kann nichts Schlechtes über ihn sagen. Ein ordentlicher Bürger, fleißiger Kirchgänger. Ich habe noch nie gehört, dass jemand schlecht über ihn sprach oder ihm etwas nachtrug.";
	STR_TRADER[1] = "Er ist der Hauptlieferant unseres Gouverneurs und verdient gut daran. Aber er führt seine Geschäfte ehrlich. Zumindest wurde er bisher in nichts Anrüchigem erwischt.";
	STR_TRADER[2] = "Dieser dicke Kerl genießt in unserer Stadt wohlverdienten Respekt. Seine Waren sind stets ausgezeichnet, und ich kann mich nicht erinnern, dass er je jemanden betrogen hätte.";
	STR_TRADER[3] = "Er ist ein Taugenichts. Handelt und handelt, aber es kommt nichts dabei heraus. Mal fehlt dies, mal jenes. Und selbst kommt er aus den Schulden nicht heraus.";
	STR_TRADER[4] = "Ein unangenehmer Mensch, Monsieur. Man sagt, er war Assistent von Baudouin Coffier, ruinierte ihn dann und kaufte den Laden auf. Über die Qualität seiner Waren kann ich nichts sagen, aber als Mensch ist er mir äußerst unsympathisch.";
	STR_TRADER[5] = "Oh! Ein abscheulicher Mensch, ich rate Ihnen dringend, keine Geschäfte mit ihm zu machen. Er hält die halbe Stadt in Schulden! Und die Waren in seinem Laden sind immer von schlechter Qualität.";
	STR_TRADER[6] = "Niemand weiß so recht etwas über ihn. Er ist erst kürzlich hergezogen und hat sofort sein Geschäft eröffnet. Er scheint ehrlich zu handeln, schmuggelt wohl nicht.";

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
