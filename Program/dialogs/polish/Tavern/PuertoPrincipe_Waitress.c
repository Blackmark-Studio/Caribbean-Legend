// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Pytania, "+GetAddress_Form(NPChar)+"?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?")," "+GetSexPhrase("Hm, co to za pomysł, "+GetAddress_Form(NPChar)+"? ","Znowu te dziwne pytania? Kochanie, idź się napij rumu czy coś...")+" ","Przez cały ten dzień, to już trzeci raz, kiedy mówisz o jakimś pytaniu..."+GetSexPhrase(" Czy to jakieś oznaki uwagi?","")+"","Więcej pytań, jak sądzę, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie","Nie mam teraz o czym rozmawiać."),"Nie, nie piękna...","Nie ma mowy, kochanie...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_2"))
			{
				link.l1 = "Muszę ci zadać kilka pytań. Pracowałaś w karczmie w dniu, kiedy zniknęła beczka ginu, prawda? Co możesz mi powiedzieć o tym, co się tu działo tamtego dnia?";
				link.l1.go = "OS_Tavern2_1";
			}
			//<-- Старые счёты
		break;
		
		//--> Старые счёты
		case "OS_Tavern2_1":
			dialog.text = "Ja... nie wiem, co powiedzieć. Wszystko było normalne, nic nadzwyczajnego.";
			link.l1 = "Naprawdę? Nic dziwnego? A co z tym marynarzem z 'Sea Beast', który cię nagabywał? Wydawał się przekonany, że chętnie spędzisz z nim noc.";
			link.l1.go = "OS_Tavern2_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OS_Tavern2_2":
			dialog.text = "Ach, on! Po prostu wypił za dużo, to wszystko. To się tutaj często zdarza, wiesz. Z pewnością nie dawałam mu powodów, ale zaczął się narzucać. Więc postawiłam go do pionu.";
			link.l1 = "Nie dawałaś powodów? On twierdzi co innego. Dlaczego tym razem zrobiłaś taką awanturę, a nie przy innych okazjach?";
			link.l1.go = "OS_Tavern2_3";
		break;
		
		case "OS_Tavern2_3":
			dialog.text = "Ja... naprawdę nic nie wiem! Przez cały wieczór byłam na widoku! Nic nie widziałam, nic nie słyszałam! I o beczce... nie mam pojęcia, co się z nią stało! Po co to przesłuchanie? Po prostu robiłam swoje jak zawsze!";
			link.l1 = "Myślę, że wiesz więcej, niż mówisz. Wiesz, noc w ładowni bez światła i jedzenia potrafi zdziałać cuda z pamięcią. Chcesz się przekonać? A może pogadamy po dobroci?";
			link.l1.go = "OS_Tavern2_4_HO";
			link.l2 = "Masz niepowtarzalną okazję - opowiedz wszystko, a zachowam twoją rolę w tym przedstawieniu dla siebie. Ale jeśli będziesz milczeć – będzie gorzej dla ciebie.";
			link.l2.go = "OS_Tavern2_4_harizma";
		break;
		
		case "OS_Tavern2_4_HO":
			dialog.text = "Ja... powiem wszystko! To wszystko przez mojego... zalotnika, Jacka. Jacka Veilsa! Namówił mnie, żebym uwiodła dowolnego marynarza z 'Sea Beast'. Gdyby się narzucał, miałam zrobić scenę, by wyciągnąć karczmarza zza lady. Gdyby zamieszanie zaczęło cichnąć, dwóch marynarzy miało rozpocząć bójkę, by go zatrzymać. Tak właśnie było\nW tym czasie kapitan 'Sea Beast' zdołał ukraść beczkę. To wszystko, co wiem, "+GetSexPhrase("panie","pani")+"! Proszę, nie wydawaj mnie! Chciałam tylko, żeby Jack w końcu zaczął mnie szanować!";
			link.l1 = "Pomogłaś jednemu, a drugiego bez wahania rzuciłaś na pożarcie? No cóż, dotrzymuję słowa – nie wydam cię. Ale będziesz musiała z tym żyć. Przez twoją głupotę karczmarz mógł mieć poważne kłopoty. Gdzie znajdę Jacka? I pamiętaj – jeśli skłamiesz, wrócę. I nie spodoba ci się to.";
			link.l1.go = "OS_Tavern2_5";
			AddComplexSelfExpToScill(40, 40, 40, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "OS_Tavern2_4_harizma":
			dialog.text = "Ja... powiem wszystko! To wszystko przez mojego... zalotnika, Jacka. Jacka Veilsa! Namówił mnie, żebym uwiodła dowolnego marynarza z 'Sea Beast'. Gdyby się narzucał, miałam zrobić scenę, by wyciągnąć karczmarza zza lady. Gdyby zamieszanie zaczęło cichnąć, dwóch marynarzy miało rozpocząć bójkę, by go zatrzymać. Tak właśnie było\nW tym czasie kapitan 'Sea Beast' zdołał ukraść beczkę. To wszystko, co wiem, "+GetSexPhrase("panie","pani")+"! Proszę, nie wydawaj mnie! Chciałam tylko, żeby Jack w końcu zaczął mnie szanować!";
			link.l1 = "Pomogłaś jednemu, a drugiego bez wahania rzuciłaś na pożarcie? No cóż, dotrzymuję słowa – nie wydam cię. Ale będziesz musiała z tym żyć. Przez twoją głupotę karczmarz mógł mieć poważne kłopoty. Gdzie znajdę Jacka? I pamiętaj – jeśli skłamiesz, wrócę. I nie spodoba ci się to.";
			link.l1.go = "OS_Tavern2_5";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "OS_Tavern2_5":
			dialog.text = "Nie wiedziałam, że to tak poważna sprawa! To przecież tylko beczka... Jack mieszka naprzeciwko. Wynajmuje tam dom, ja... nic więcej nie wiem! Proszę, wybacz mi! Kapitanie, przysięgam, że już nigdy tak nie zrobię!";
			link.l1 = "Wracaj do pracy i nawet nie próbuj płakać, żeby właściciel niczego nie zauważył.";
			link.l1.go = "OS_Tavern2_6";
		break;
		
		case "OS_Tavern2_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_2");
			AddQuestRecord("OS", "4");
			
			//
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.cask_gin = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.map_full = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.jewelry2 = 10;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.GunPowder = 50;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.bullet = 50;
			
			PChar.quest.OS_Zasada.win_condition.l1 = "item";
			PChar.quest.OS_Zasada.win_condition.l1.item = "cask_gin";
			PChar.quest.OS_Zasada.function = "OS_Zasada";
			
			SetFunctionLocationCondition("DWH_Close_House", "PuertoPrincipe_QuestHouse_1", false);
		break;
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
