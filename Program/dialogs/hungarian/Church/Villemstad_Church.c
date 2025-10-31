// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések, "+ GetSexPhrase("fiam","lányom") +"?", "Kérdezz csak, hallgatlak..."), "Figyelek, beszélj most, "+ GetSexPhrase("fiam","lányom") +"...", "Harmadszorra, "+ GetSexPhrase("fiam","lányom") +", kérd, amire szükséged van.",
                          "Egy lelkésznek rengeteg munkája van, és te eltereled a figyelmemet, "+ GetSexPhrase("fiam","lányom") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Most nem, atyám..."), "Nincs mit mondanom, elnézést kérek.",
                      "Megkérdezem, de késôbb. Bocsásson meg, atyám.", "Bocsásson meg, szent atyám...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "priest")
			{
				link.l1 = "Bocsásson meg, atyám, az ön egyházközségének egyik lelkésze kért meg, hogy vizsgáljam meg a házat, amelyben Joachim Merriman szobát bérelt...";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Szóval? Jártál ott, fiam?";
			link.l1 = "Voltam. De ôszintén szólva, jobb lett volna, ha nem teszem. Egy csontváz támadt rám egy hatalmas fejszével a felsô szobában. Sikerült gyôztesen kijutnom, bár nem volt könnyû.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Uram, könyörülj a lelkünkön! Legrosszabb félelmeim váltak valóra!";
			link.l1 = "Ez még nem minden, atyám. Amikor végre letettem, sikoltozott, és olyan hangja volt, mint egy nônek. Amikor átnéztem a csontokat, találtam néhány ékszert, így feltételezhetjük, hogy az eltûnt házinéni volt az.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "(keresztet vet önmagán)... Szegény Isten szolgája, az Úr nyugtassa meg a lelkét...";
			link.l1 = "Úgy tûnik, Merriman valóban varázsló. Fogalmam sincs, hogyan lehet egy élô embert ilyen förtelemmé változtatni.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Joachim Merriman egy nagyon félelmetes varázsló, fiam. Ismertem ôt Európában, de akkoriban még nem volt képes ilyesmire. Itt, a Karib-tengeren sikerült megszereznie valamit, ami természetfeletti erôket adott neki.";
			link.l1 = "Ismerte Merrimant, atyám?";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "Ezt tettem. Akkoriban még csak egy szerény pap voltam Lisszabon egyik plébániáján. Joachim Merriman gazdag nemesember volt, és valamikor elkezdett érdeklôdni a régi kéziratok és tekercsek iránt, amelyeket tengerészek hoztak távoli országokból. Az alkímiát is tanulmányozni kezdte, de egy idô után visszavonult.\nA házában az emberek fényvillanásokat láttak; néha valami furcsa szagot is éreztek. Aztán a temetôben látták ôt éjszaka. Egyszer látták, amint kiásott egy friss holttestet, és behozta a házába. És amikor elfogyott a türelem, a helyi elöljáró atya kapcsolatba lépett az inkvizícióval.\nAmikor az ôrök betörtek Merriman házának ajtaján, Joachim nem volt ott - egy titkos folyosón keresztül megszökött. A pincében egy laboratóriumot találtak, és még a tapasztalt katonák is megdöbbentek és megundorodtak attól, amit láttak. Egész rothadó és feldarabolt testek, emberi és állati csontvázak, furcsa dolgok... A Merriman iránti félelem és gyûlölet olyan jelentôs volt, hogy a házát egy pillanat alatt lerombolták.\nMerriman nyomtalanul eltûnt. Az inkvizíció keresni kezdte, és távollétében máglyahalálra ítélte, mint veszélyes boszorkánymestert. De soha nem találták meg. És most, ennyi év után újra megláttam ôt Willemstad utcáin.";
			link.l1 = "Miért nem szóltál az inkvizítoroknak?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Fiam, nem tudod, hogy az egyházunk ellentétben áll az inkvizícióval? Én inkább távol tartanám magam Vincento atyától és a gazembereitôl.";
			link.l1 = "Megértem. Atyám, azt hiszem, tudom, honnan merítette Merriman az erejét. Egy ôsi ereklye került a birtokába, Yum Cimil jáde koponyája, a halál ôsi istene, akit a Chavin törzs indiánjai imádtak.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Hm, Merriman arról volt ismert, hogy varázslatos rituálékat és kísérleteket hajtott végre holttesteken, szóval ez nagyon is igaz lehet. Hálát adok Istennek, hogy ez a szörnyû ember elhagyta Willemstadot, és hogy önök elpusztították az ördögi magokat, amelyeket megpróbált elültetni itt. Nagyon hálásak vagyunk neked, fiam. Kérlek, fogadd el jutalmadként ezeket a megszentelt tárgyakat.";
			link.l1 = "Köszönöm, atyám.";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			Log_Info("Egyházi amulettet kaptál");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_2"); 
			GiveItem2Character(pchar, "amulet_6"); 
			GiveItem2Character(pchar, "amulet_8"); 
			GiveItem2Character(pchar, "amulet_10"); 
			ref sld = characterFromId("Havana_Priest");
			dialog.text = "De ezzel még nem értek véget a gondjaink, fiam. Nemrég kaptam egy levelet a "+sld.name+", a havannai egyház elöljárójától. Szörnyû híreket hozott. Egy barlangban, a kubai dzsungelben vadászok ijesztô förtelmeket láttak, két lábon járó halottakat. És mindez még nyugtalanítóbb, tekintve, hogy az utóbbi idôben emberek tûntek el, miután a dzsungelbe mentek.";
			link.l1 = "Hmm... arra céloz, hogy ez is Merriman mûve?";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 30) link.l1.go = "caleuche_8_1";
			else link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Nem tudom, mit gondoljak, fiam. De ha az a fekete boszorkány ilyen hatalmas lett, akkor a szigetvilág minden lakója komoly veszélyben van. Csak Isten tudja, mit forgathat a fejében az ördögnek ez a szolgája\nremélem, hogy atyám "+sld.name+" tévedett, de akárhogy is - kérlek, menj el Havannába, és beszélj vele. Készítettem önnek egy kereskedelmi engedélyt, amely egy hónapig érvényes. Ezzel minden nehézség nélkül be tudsz majd menni Havanna kikötôjébe.";
			link.l1 = "Rendben, atyám. Elmegyek Havannába.";
			link.l1.go = "caleuche_9";
			npchar.quest.givelicence = true;
		break;
		
		case "caleuche_8_1":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Nem tudom, mit gondoljak, fiam. De ha az a fekete boszorkány ilyen hatalmas lett, akkor a szigetvilág minden lakója komoly veszélyben van. Csak Isten tudja, mit forgathat a fejében az ördögök eme szolgája.\nremélem, hogy atyám "+sld.name+" tévedett, de nem számít - arra kérlek, utazz Havannába, és beszélj vele.";
			link.l1 = "Természetesen, atyám. Azonnal Havannába megyek.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Örülök, hogy az Egyház igaz fia vagy. Éjjel-nappal imádkozni fogok az egészségedért és a jólétedért. Menj az áldásommal. Az Úr erôsítsen meg téged a szentségtelen hatalmak elleni harcodban.";
			link.l1 = "Köszönöm és Isten veled, atyám.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			DialogExit();
			AddQuestRecord("Caleuche", "26");
			AddCharacterMaxHealth(pchar, 1);
			if (CheckAttribute(npchar, "quest.givelicence")) GiveNationLicence(HOLLAND, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, HOLLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			pchar.questTemp.Caleuche = "havana";
			Caleuche_PrepareCubaGrot();
			AddLandQuestMark(characterFromId("Havana_Priest"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
