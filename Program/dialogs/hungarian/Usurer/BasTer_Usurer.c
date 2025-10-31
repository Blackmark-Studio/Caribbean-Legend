// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek?"), "Nemrég próbálta ezt a kérdést feltenni nekem...", "Igen, hadd találjam ki... Már megint körbe-körbe jársz?",
                          "Figyelj, én itt a pénzügyekkel foglalkozom, nem válaszolok kérdésekre...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Kitaláltad, sajnálom...", "Megértem...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "continue")
            {
                link.l1 = "Kapitány vagyok "+GetFullName(pchar)+". Az embere mondta, hogy látni akar. Csupa fül vagyok.";
                link.l1.go = "FMQG";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "sucsess")
            {
                link.l1 = "Én megint, monseniour "+GetFullName(pchar)+". Elhoztam neked Bertrand Pinette-et. A raktérben van.";
                link.l1.go = "FMQG_14";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "letter")
            {
                link.l1 = "Én megint, monseniour "+GetFullName(pchar)+". Beszélgessünk.";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers")
            {
                link.l1 = "Én megint, monseniour "+GetFullName(pchar)+". Beszélgessünk.";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
            {
                link.l1 = "Én megint, monseniour "+GetFullName(pchar)+". Gondolom, nem számítottál arra, hogy újra látni fogsz.";
                link.l1.go = "FMQG_23";
            }
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "A-ah, kapitány "+GetFullName(pchar)+"! Annyira örülök, hogy látlak! Már régóta vártam rád... Jól van. Lenne egy kérdésem. Nemrég egy Bertrand Pinette nevû férfi kereste meg önt a kikötôben, hogy feljusson a hajójára. Gazdag kinézetû fickó, luxus parókában. Ismerôsen cseng?";
			link.l1 = "Igen, ismerôs. Tényleg ezzel a céllal keresett meg.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			DelLandQuestMark(npchar);
			Log_Info("Kaptál egy nehéz pénztárcát");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "purse3");
			dialog.text = "Fel akarta bérelni magát és a hajóját? Kapitány, nagy szívességet tenne nekem, ha elmondaná az ügy minden részletét. Megérdemli a fáradozását. Tessék, fogja ezt az erszényt, tele pénzérmékkel. Az öné, most pedig kérem, meséljen nekem Bertrand Pinette-rôl.";
			link.l1 = "Rendben. Monsieur Pinette felbérelte a hajómat, hogy szállítsa ôt és két barátját Guadeloupe-ról a spanyol Maine-re. Pontosabban a Portobello Mosquitoes-öbölbe. Elvégeztem a munkát, ôk elhagyták a hajómat, és besétáltak a dzsungelbe.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "Értem. És említette monsieur Pinette a végsô célállomást? És mi van a társaival?";
			link.l1 = "A saját szavai szerint Panamába tartottak. A barátai elég érdekesnek tûntek: két tiszt, egy spanyol és egy francia. Még mindig nem értem, mi kötötte össze ôket, de nem azért fizettek, hogy kérdezôsködjek.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "Egy spanyol tiszt? És egy francia tiszt? Ó! Hát ez nem semmi! Szép volt, monsieur Pinette! Micsoda ravasz kutya! Még itt is megtalálta a módját, hogy pénzt keressen! Panamát mondott?";
			link.l1 = "Igen, és mindent elmondtam, amit tudok. Elmehetek?";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			dialog.text = "Várjon, kapitány. Van egy üzleti ajánlatom az ön számára. Nem bánja, ha keres egy kis pénzt? De elôbb hadd mondjak valamit az utasairól.";
			link.l1 = "Nos, halljuk.";
			link.l1.go = "FMQG_5";
		break;
		
		case "FMQG_5":
			dialog.text = "Monsieur Bertrand Pinette két évvel ezelôtt jelent meg a kolóniánkon, és azonnal elkezdett üzletelni a kapitányokkal. Az üzlet, nos, egy sötét üzlet is... Olyan árukat szállítottak neki, amelyekbôl nagy hiány volt ezen a helyen, értéktárgyakat, csempészárut, sôt néha még rabszolgákat is... Rendszeresen vett fel kölcsönöket az illegális üzleteihez az irodámban, de mindig visszafizette minden kamatával együtt\nMielôtt az önök jóvoltából elhagyta a szigetet, felvett egy nagy kölcsönt, sokkal nagyobbat, mint általában. Ô... megbízható ügyfél volt, kifogástalan hiteltörténettel, ezért nyújtottam neki kölcsönt. Nagy hiba volt. Monsieur Pinette elszökött, és nyilvánvalóan nem fogja visszafizetni az érméimet.";
			link.l1 = "Mekkora az összeg, ha szabad kérdeznem?";
			link.l1.go = "FMQG_6";
		break;
		
		case "FMQG_6":
			dialog.text = "Nagy összeg. Körülbelül százötvenezer pezó dublónokban. Tíz láda, mindegyikben százötven dublonnal. Nem is beszélve a kamatokról.";
			link.l1 = "Hm... Két évig fizetett neked, megszoktattad vele, felvett egy jelentôs kölcsönt, aztán megszökött. Okos.";
			link.l1.go = "FMQG_7";
		break;
		
		case "FMQG_7":
			dialog.text = "Pontosan, kapitány. Ezért szeretném felbérelni magát egy munkára: találja meg a söpredéket, és hozza ide. Én, a kormányzó és a parancsnok megtaláljuk a módját, hogy eltörölje az adósságát. Maga látta azt az embert, a maga utasa volt, ez azt jelenti, hogy önnek nagyobb esélye van megtalálni monsieur Pinette-et, mint bárki másnak. Persze, én is felbérelek egy hivatásos fejvadászt a szerencsétlen seggére, de van egy olyan érzésem, hogy az önök segítsége hatékonyabbnak bizonyul majd.";
			link.l1 = "Mit szólna egy kis jutalomhoz?";
			link.l1.go = "FMQG_8";
		break;
		
		case "FMQG_8":
			dialog.text = "A munka elvégzéséért adok neked egy ládát tele dublonnal, százötven érmével.";
			link.l1 = "Azt mondom, ez elég szánalmas jutalom lenne a spanyol városban élô lélek felkutatásáért és elrablásáért.";
			link.l1.go = "FMQG_9";
		break;
		
		case "FMQG_9":
			dialog.text = "Kapitány, feltételezem, hogy Pinette úr jól megfizette önt az én pénzembôl, hiszen ilyen olcsón értékeli az ajánlatomat. Biztosíthatom, hogy megéri az erôfeszítést. Természetesen minden joga megvan ahhoz, hogy visszautasítsa... de valamit el kell mondanom, és ez biztosan meggondolja magát.";
			link.l1 = "És mi ez?";
			link.l1.go = "FMQG_10";
		break;
		
		case "FMQG_10":
			dialog.text = "Néhány nappal Pinette guadeloupe-i szökése elôtt egy rab megszökött a basse-terre-i börtönbôl. A neve don Carlos de Milyar, egy spanyol nagyúr és tiszt. Egy francia tiszt, egy tengerészgyalogos hadnagy árulásának köszönhetôen sikerült neki... Érti, mire gondolok?";
			link.l1 = "Hm... És ez engem miért érint? Én csak utasokat szállítottam, semmi több.";
			link.l1.go = "FMQG_11";
		break;
		
		case "FMQG_11":
			dialog.text = "Dehogynem! Személy szerint nincs kétségem afelôl, hogy semmi köze don de Milyar szökésének megszervezéséhez. De a kormányzó és a parancsnokunk nem így gondolkodik errôl. Ha szerencséje van, bûnrészességgel vádolják, ha nem... Nem akarom folytatni. Nézze, maga egymagában egy szökött spanyol tisztet vett a fedélzetére, valószínûleg valami rejtett öbölben... jól mondom, kapitány?";
			link.l1 = "Értem. Megzsarol engem. Hibát követtem el, hogy idejöttem...";
			link.l1.go = "FMQG_12";
		break;
		
		case "FMQG_12":
			dialog.text = "Mit mond, kapitány?! Nem zsarolom magát! Csak annyit kérek, hogy segítsen nekem egy jó jutalomért cserébe. Lenne olyan kedves megkeresni Monsieur Pinette-et és elszállítani Basse-Terre-be? Várni fogom a visszatérését. Azt hiszem, két hónap elég lesz, hogy elhajózzunk Panamáig és vissza.";
			link.l1 = "Nem hagy nekem más választást. Bár kétlem, hogy egy ilyen üzleti megközelítés jót tenne a barátságunknak. Viszlát, uram.";
			link.l1.go = "FMQG_13";
		break;
		
		case "FMQG_13":
			DialogExit();
			LocatorReloadEnterDisable("Baster_town", "reload1_back", false);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", false);
			LocatorReloadEnterDisable("Baster_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.FMQG = "headhunter_panama";
			ReOpenQuestHeader("FMQ_Guadeloupe");
			AddQuestRecord("FMQ_Guadeloupe", "7");
			if(bImCasual)
			{
				NewGameTip("Felfedezô mód: a küldetés idôtartama megduplázódott");
				SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 122, false);
			}
			else SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 61, false);
			AddMapQuestMarkCity("panama", false);
			AddLandQuestMark(characterFromId("Panama_tavernkeeper"), "questmarkmain");
			
			// Sinistra - Старт квеста "Мерзкий Божок"
			PChar.quest.ChickenGod_StartLoc.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_StartLoc.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_StartLoc.function = "ChickenGod_BrothelCheck";
		break;
		
		case "FMQG_14":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Kitûnô hírek, kapitány! Azonnal elküldöm az embereimet, hogy szedjék le ezt a fattyút a hajójáról. Ez a madárka ezúttal nem fog elrepülni elôlem... Megérdemelted a jutalmad, vedd el ezt a ládát. Kérlek, ne haragudj rám, itt egy amulett neked. Ez egy ajándék.";
			link.l1 = "Hála. Feltételezem, hogy a hallgatásod is része a jutalmamnak?";
			link.l1.go = "FMQG_15";
		break;
		
		case "FMQG_15":
			Log_Info("Kaptál egy ládát tele dublonnal.");
			Log_Info("Kaptál egy 'Halász' amulettet.");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "obereg_7");
			dialog.text = "Hallgatás? Mirôl? Örülnék, ha az ügyfeleim között látnám. Tudja, mit mondanak a hallgatásról és az aranyról?";
			link.l1 = "Néha sokkal többet ér, mint az arany, monsieur. A lecke megtanulva. Viszontlátásra!";
			link.l1.go = "FMQG_16";
		break;
		
		case "FMQG_16":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			ref sld = characterFromId("FMQG_pass_1");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "23");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		case "FMQG_17":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("baster");
			dialog.text = "Hallgatom. Bertrand Pinette a hajóján van, gondolom?";
			link.l1 = "Nem. Bár van valami sokkal jobbat is tudok önnek. Olvassa el ezt.";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_18":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "Mi ez?";
			link.l1 = "Olvasson tovább, monsieur. Késôbb folytatjuk.";
			link.l1.go = "FMQG_19";
		break;
		
		case "FMQG_19":
			LAi_Fade("", "");
			dialog.text = "(olvasás) Ahem ... Mi ez az ostobaság a lázas betegrôl?";
			link.l1 = "Komolyan mondod? Rendben, akkor ezt a 'hülyeséget' a kormányzóhoz viszem. Úgy vélem, hogy nagy érdeklôdést fog tanúsítani az igazság kiderítése iránt a 'Courage' és a gyémántszállítmánya eltûnésével kapcsolatban... Miért lettél ilyen sápadt?";
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter")) link.l1.go = "FMQG_24";
			else link.l1.go = "FMQG_20";
		break;
		
		case "FMQG_20":
			dialog.text = "Szóval mégiscsak megtaláltad Pinette-et...";
			link.l1 = "Igen. Ezért ajánlok egy üzletet. Felejtse el Carlos de Milyart, Jean Denót és a többi jó urat, tegye ezt, és én elfelejtem ezt a levelet.";
			link.l1.go = "FMQG_21";
		break;
		
		case "FMQG_21":
			dialog.text = "Rendben, kapitány... Elfogadom a feltételeit.";
			link.l1 = "Remek. Remélem, nem haragszik rám, most már végeztünk, azt hiszem. Viszontlátásra.";
			link.l1.go = "FMQG_22";
		break;
		
		case "FMQG_22":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			pchar.questTemp.FMQG = "cave";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.quest.FMQG_cave.win_condition.l1 = "location";
			pchar.quest.FMQG_cave.win_condition.l1.location = "Guadeloupe_Cave";
			pchar.quest.FMQG_cave.function = "FMQG_InCave";
			// заполним сундук
			pchar.GenQuestBox.Guadeloupe_Cave = true;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse1 = 5;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse2 = 2;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse3 = 1;
			SetFunctionTimerCondition("FMQG_ClearBox", 0, 0, 3, false);
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
			{
				SetFunctionTimerCondition("FMQG_RemoveHunterScore", 0, 0, 1, false);
				AddQuestRecord("FMQ_Guadeloupe", "29");
				DeleteAttribute(pchar, "questTemp.FMQG.Letter");
			}
			else AddQuestRecord("FMQ_Guadeloupe", "25");
		break;
		
		case "FMQG_23":
			dialog.text = "Ha... Igaza van, kapitány.";
			link.l1 = "Van valamim a számodra. Fogja ezt és olvassa el.";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_24":
			dialog.text = "Szóval mégiscsak megtaláltad Pinette-et...";
			link.l1 = "Igen. Szóval, egy üzletet ajánlok neked. Állítsa helyre a jó hírnevemet a francia gyarmatokon, és én elfelejtem ezt a levelet.";
			link.l1.go = "FMQG_25";
		break;
		
		case "FMQG_25":
			dialog.text = "De...";
			link.l1 = "Leszarom, hogyan fogja ezt megtenni. Ha a fejem utáni vadászat nem ér véget holnap, a kormányzó mindent megtud.";
			link.l1.go = "FMQG_21";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
