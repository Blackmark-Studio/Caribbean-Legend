// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi to pytanie niedawno...","Tak, pozwól mi zgadnąć... Znowu krążysz w kółko?","Słuchaj, ja tu prowadzę finanse, nie odpowiadam na pytania...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam teraz nic do omówienia."),"Umph, gdzież podziała się moja pamięć...","Zgadłeś, przykro mi...","Rozumiem...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Mynheer, mam do czynienia z niecodzienną sprawą. Wiem, że pewien francuski korsarz o imieniu Gaius Marchais sprzedał ci niedawno dwa unikalne przedmioty: złoty relikwiarz i złoty trybularz. Chciałbym je od ciebie odkupić.";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(npchar, "quest.GOT_chest") && CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "Przyniosłem ci małą skrzynię dublonów.";
                link.l1.go = "guardoftruth_3";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "O, tak! Oczywiście, pamiętam je! Tak, rzeczywiście były oryginalne i, co ważniejsze, drogie. Ale jesteś za późno, kapitanie, już ich nie mam. Już je sprzedałem.";
			link.l1 = "Nie do wiary! A kto interesował się takim kościelnym sprzętem? Panie, komu je sprzedałeś? Chciałbym spróbować je odkupić...";
			link.l1.go = "guardoftruth_1";
			npchar.quest.utensil = "true";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Hm, a dlaczego miałbym wam zdradzać nazwiska moich klientów?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "self_win")
			{
				link.l1 = "Może dlatego, że jestem dobrym przyjacielem w oczach gubernatora Matthiasa Becka i mogę poprosić go o odpowiednią sankcję dla ciebie?";
				link.l1.go = "guardoftruth_2_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "holl_win")
				{
					link.l1 = "Może dlatego, że mam świetne relacje z Holenderską Kompanią Zachodnioindyjską i udzieliłem wielkiej pomocy wielu holenderskim osadnikom na archipelagu?";
					link.l1.go = "guardoftruth_2_2";
				}	
				else
				{
					link.l1 = "Może dlatego, że za to zapłacę?";
					link.l1.go = "guardoftruth_2_3";
					npchar.quest.GOT_chest = "true";
				}
			}
		break;
		
		case "guardoftruth_2_1":
			dialog.text = "Ach, czyli to ty jesteś "+GetFullName(pchar)+", przyjaciel samego gubernatora, który ujawnił przestępczy spisek Lucasa Rodenburga... Jakże mógłbym o tym zapomnieć? Oczywiście, powiem ci.";
			link.l1 = "Zatem, zamieniam się w słuch.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_2":
			dialog.text = "Ach, racja, jesteś "+GetFullName(pchar)+", wielki zdobywca pirackiego 'statku widmo'. Jakże mógłbym o tym zapomnieć? Oczywiście, powiem ci.";
			link.l1 = "Zatem zamieniam się w słuch.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_3":
			dialog.text = "W porządku. Za skrzynię wypełnioną po brzegi złotymi dublonami, przypuszczam, że opowiem ci o tych, którzy cię wyprzedzili, by dokonać zakupu.";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "Oto ona. Są dla mnie bardzo cenne...";
				link.l1.go = "guardoftruth_3";
			}
			else
			{
				link.l1 = "Dobrze, przyniosę ci to, o co prosisz. To dla mnie bardzo cenne przedmioty...";
				link.l1.go = "exit";
			}
		break;
		
		case "guardoftruth_3":
			RemoveItems(pchar, "chest", 1);
			Log_Info("Przekazałeś skrzynię z dublonami");
			PlaySound("interface\important_item.wav");
			dialog.text = "Cudownie. W takim razie jestem skłonny podzielić się z tobą pewnymi informacjami.";
			link.l1 = "Zamieniam się w słuch.";
			link.l1.go = "guardoftruth_4";
			DeleteAttribute(npchar, "quest.GOT_chest");
		break;
		
		case "guardoftruth_4":
			dialog.text = "Kadzielnica złota została kupiona przez człowieka imieniem Rolande Moses, lepiej znanego jako Rollie Kapelusz. Dlaczego ten rzeźnik potrzebował cennego kościelnego przedmiotu, nie potrafię zrozumieć, ale z jakiegoś powodu był nim niezmiernie uradowany... Przy okazji, wątpię, byś spotkał samego Rollie'ego.";
			link.l1 = "Dlaczego tak jest?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Bo ten chciwy łupieżca samotnych angielskich kupców niedawno wpadł ze swoim szkunerem prosto w łapy pułkownika Foxa. Wiesz, kto to taki?";
			link.l1 = "Zgadza się! Dowódca 'morskich lisów' w St. Jones na Antigui...";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "A zatem rozumiesz, dlaczego już nigdy nie zobaczymy naszego biednego Rolande'a. Pułkownik przejął jego szkuner z wszystkimi ocalałymi członkami załogi i dostarczył ich do St. Jones, gdzie prawdopodobnie już zawiązano im sznury wokół szyi.";
			link.l1 = "Rozumiem. A co z monstrancją?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Ostensory został niedawno nabyty przez Senorę Belindę de Ribero z Cumany. Bardzo znakomita senora, krewna samego Fernanda de Villegas, gubernatora Kumany. Domyślam się, że chciała go przynieść jako dar dla kościoła.";
			link.l1 = "Senora Belinda de Ribero? Znajdę ją w Kumanie, prawda?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Z pewnością. Sama powiedziała, że wraca prosto do domu z Willemstad.";
			link.l1 = "Dobrze. Dziękuję, "+npchar.name+", byłeś wielką pomocą!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Zawsze do usług, panie. Odwiedzaj mnie od czasu do czasu!";
			link.l1 = "Życzę ci bogatych klientów z tłustymi portfelami i ubogimi mózgami... Ha-ha!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			AddQuestRecord("Guardoftruth", "23");
			pchar.questTemp.Guardoftruth.Usurer = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
