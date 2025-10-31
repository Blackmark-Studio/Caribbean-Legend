// Соломон Шнеур - старый еврей
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
//--------------------------------------за Голландию------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyFather")
				{
					dialog.text = "Mit akarsz ettôl az öreg zsidótól, fiatalember?";
					link.l1 = "Salamon, gondolkozz el alaposan, és emlékezz az elveszett szigetre, ahol hajótörést szenvedtél. Elrejtettél ott egy rejtekhelyet. Beszéltem a lányoddal. A fônököm, Lucas Rodenburg szabad kezet adott, hogy a családod érdekében cselekedjek. Ahogy én látom, jelenleg a legfontosabb dolog számodra, hogy visszaszerezd a családod tôkéjét, és a segítségem nélkül egy szippantást sem kapsz abból az aranyból.";
					link.l1.go = "SolomonBonanza";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "Ó, fiatalember, te vagy az? Nem tudsz nekem semmi jót mondani? Ti keresztények vagytok itt, hogy megint kérdésekkel kínozzátok ezt a szegény öreg zsidót?";
					if (CheckCharacterItem(pchar, "SkullAztec"))
					{
						link.l1 = "Megtaláltam a szigetet, bár elég nehéz volt. Megtaláltam a ládát is a pénzzel és ezzel a koponyával. Gondolom, ez a nagyapád-pátriárkád koponyája, akármirôl is beszéltél.";
						link.l1.go = "SolomonBonanza_2";
					}
					link.l2 = "Megtaláltam a szigetet, bár nem volt könnyû dolgom. Megtaláltam a ládát is a pénzzel. De abban a ládában nem volt koponya.";
					link.l2.go = "SolomonBonanza_3";
					link.l3 = "Nem, jelenleg nincsenek kérdéseim.";
					link.l3.go = "exit";
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "GiveLucasMoney" && GetQuestPastDayParam("questTemp.HWIC.Holl.LucasMoney") > 7)
				{
					dialog.text = "Ó, fiatalember, maga az? Tudsz nekem valami jót mondani? Vagy megint kérdésekkel akarod kínozni ezt a szegény öreg zsidót?";
					link.l1 = "Megtaláltam a szigetet, bár elég nehéz volt. És megtaláltam a ládát is a pénzzel. Tessék, tessék.";
					link.l1.go = "SolomonBonanza_5";
					break;
				}
				dialog.text = "Helló, fiatalember. Mit akarsz ettôl a szegény öreg zsidótól?";
				link.l1 = "Jó napot, uram. Nem, semmit, csak köszönni jöttem.";
				link.l1.go = "exit";
				break;
			}
//----------------------------------------за Англию-----------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "toAbigile")
				{
					dialog.text = "Jó napot, fiatalember. Látom, hogy valamiért jött... Mit akar? Kapok valamit ebbôl, vagy lemaradtam valamirôl?";
					link.l1 = "Jó napot, Solomon. Abigail-lel szeretnék beszélni.";
					link.l1.go = "Solomon_treasure";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Helló, fiatalember. Mit akarsz ettôl a szegény öreg zsidótól?";
				link.l1 = "Jó napot, Solomon. Semmi, csak köszönni jöttem.";
				link.l1.go = "exit";
				break;
			}
//-----------------------------------------против всех-------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "Jó napot, fiatalember. Látom, hogy valamiért jött... Mit akar? Kapok valamit ebbôl, vagy lemaradtam valamirôl?";
					link.l1 = "Beszélnem kell Abigail-lel. Van egy levelem neki.";
					link.l1.go = "Abigile_kidnap";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDayOver")
				{
					dialog.text = "Helló, fiatalember. Mit akarsz? Még egy levelet a lányomnak?";
					link.l1 = "Nem. Hol van Abigail?";
					link.l1.go = "Abigile_GoOver";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistory")
				{
					dialog.text = "Ó... A pénzemrôl beszél, fiatalember?";
					link.l1 = "Igen, mynheer. A pénzrôl, amit elrejtettél egy szigeten. Igaz, hogy te és Abigail nem emlékeztek a helyére?";
					link.l1.go = "Solomon_history";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryAfter")
				{
					dialog.text = "Jól van, rendben. Emlékszem a flottára és a kapitányára. Egyszer már láttam ôt Amszterdamban. A fluyt neve 'Leiden' és a kapitány neve Toff Keller volt.";
					link.l1 = "Ez már valami! Most már van egy nyomom.";
					link.l1.go = "Solomon_history_3";
					pchar.questTemp.HWIC.Self = "SolomonHistoryEnd";
					break;
				}
				dialog.text = "Hé, mit akarsz ezúttal ettôl a szegény öreg zsidótól?";
				link.l1 = "Jó napot, uram. Nem, semmit, csak köszönni jöttem.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Hé, mit akarsz ezúttal ettôl a szegény öreg zsidótól?";
			link.l1 = "Jó napot, uram. Nem, semmit, csak köszönni jöttem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-----------------------------------------------За Голландию-----------------------------------
		case "SolomonBonanza":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "És mit akarsz tôlem? Úgy nézek ki, mint aki tud valamit? Honnan tudhatnám, hogy egy ilyen isten háta mögötti napon pontosan hol van odakint egy telek, ahol szabadon elvihetô áru és arany van? Képzeljétek el, hogy bármelyik nem zsidó, aki odakint az utcán sétál, hogyan akar túljárni egy olyan zsidó eszén, mint én, és elvenni a pénzemet!\nEz egy sziget. Egyetlen ember sincs ott, csak Abi és én. Egyetlen egy sem. Egyáltalán senki. Volt egy barlang a közepén. Oda tettem a ládámat, hogy megmentsem attól a kalóz gój Amalektôl! Egy láda tele arannyal, egy csecsebecse sem volt benne. Egészen az óhazából cipeltem! Minden, amit a homlokom verejtékével kerestem, ott van benne. Plusz a nagyapám koponyája... Hidd el, az a valami megmentett minket, igen-igen\nOh-ho-ho, ez egy ôsi talizmán, tele talmudi mágiával! Isten óvjon meg minket Amálektôl! Jaj, de nehéz újrakezdeni a pogányok korában! Bárcsak tudná, fiatalember! Ó, bárcsak tudnád!";
			link.l1 = "Mi a fenérôl fecsegsz, te holdkóros? Kit érdekel? Majd megoldom magam. Viszlát!";
			link.l1.go = "SolomonBonanza_1";
		break;
		
		case "SolomonBonanza_1":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbySeekIsland";
			pchar.quest.Joakim_meeteng.win_condition.l1 = "location";
			pchar.quest.Joakim_meeteng.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Joakim_meeteng.function = "Create_Joakim";
		break;
		
		case "SolomonBonanza_2"://отдаем всё
			dialog.text = "Ó, van Isten, és te egy igazi ember vagy! Nemcsak az aranyamat hoztad vissza, hanem a Shneur nevet is megváltottad! Micsoda shande-ot akadályoztál meg! Mynheer Rodenburg joggal lehet büszke arra, hogy ilyen kapitányok vannak a parancsnoksága alatt, mint te. A koponyát odaadom mynheer Rodenburgnak, megígérte, hogy jelentôs összeget fizet érte. Szeretném személyesen megköszönni neked, te egy remek sábesz gój vagy - kérlek, fogadd el ezt az amulettet e zsidó köszönetének apró jeléül.";
			link.l1 = "Uh, köszönöm, azt hiszem.";
			link.l1.go = "SolomonBonanza_4";
			RemoveItems(PChar, "SkullAztec", 1);
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			AddDialogExitQuestFunction("DeleteJoakimFromRoom");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Joakim"));
			pchar.questTemp.Caleuche.SolomonSkul = true;
		break;
		
		case "SolomonBonanza_3":
			dialog.text = "Jaj, van Isten, és te egy igazi ember vagy! Nemcsak az aranyamat hoztad vissza, hanem a Shneur nevet is megváltottad! Micsoda shande-ot akadályoztál meg! Ami a koponyát illeti - na, mindegy, úgyis egy meshuggeneh szarházi volt! Mynheer Rodenburg joggal lehet büszke arra, hogy olyan kapitányok állnak a parancsnoksága alatt, mint te. Szeretném személyesen megköszönni neked, te egy remek sábesz gój vagy - kérlek, fogadd el ezt az amulettet emlékül.";
			link.l1 = "Uh, köszönöm, azt hiszem.";
			link.l1.go = "SolomonBonanza_4";
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "obereg_10");
			pchar.questTemp.HWIC.Holl.ScullnotReturn = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			DelLandQuestMark(npchar);
		break;
		
		case "SolomonBonanza_4":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyLeavesMarried";//теперь можно говорить с Аби
			AddQuestRecord("Holl_Gambit", "1-32");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "SolomonBonanza_5":
			dialog.text = "Micsoda? - Nem, nem, nem, nem. Mit akar ezzel mondani, fiatalember? Ez igaz? Hadd nézzem meg... ";
			link.l1 = "Itt a pénze. A tiéd és Abigailé. De sajnos nem találtam meg a nagyapád koponyáját.";
			link.l1.go = "SolomonBonanza_6";
		break;
		
		case "SolomonBonanza_6":
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			dialog.text = "Ó, pénz, pénz, pénz, pénz, csodálatos pénz... Hmm, ez nem úgy néz ki, mint az én pénzem... Nem olyan az illata, mint az én kedves pénzemnek. De aztán megint - a pénz mind egyforma, fiatalember, nem igaz? Nem fogok siránkozni rajta. 'Ne nézz egy ajándék gój szájába,' ahogy mi szoktuk mondani! Köszönöm szépen, hogy visszaadta a megtakarításaimat. Én is szeretném megköszönni, kérem, fogadja el ezt az amulettet. Most menj, és mondd el Abinak a jó hírt. Ezt meg kell számolnom.";
			link.l1 = "Sok boldogságot, Solomon.";
			link.l1.go = "SolomonBonanza_4";
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

//-------------------------------------------за Англию------------------------------------------------
		
		case "Solomon_treasure":
			dialog.text = "Vigyázz magadra! Mynheer Rodenburg egy lépésre van attól, hogy a gój vejem legyen. A helyôrség összes katonája egy pillanat alatt itt lesz, ha segítségért kiáltok!";
			link.l1 = "Ki a fasz vagy te?";
			link.l1.go = "Solomon_treasure_1";
		break;
		
		case "Solomon_treasure_1":
			dialog.text = "Figyeljen rám, kapitány. Én vagyok az apja, Salamon. Tégy helyesen, hozd el nekem az elveszett érméimet és a dédapja jáde koponyáját. Lehet, hogy ez az öreg zsidó nem olyan ravasz, mint te, de még ô is tudja, hogy akarsz valamit a lányától\nTéged talán valaki küldött, valami kapitány, aki ismer engem, mindent elmondok Abinak, ne aggódj. Most nincs otthon, a hozzád hasonló nemzsidó bûnösök lelkéért imádkozik.";
			link.l1 = "Ennek alig volt értelme... Baszd meg, te egy igazi szerencsétlen vagy. Viszlát, te vén fösvény.";
			link.l1.go = "Solomon_treasure_2";
		break;
		
		case "Solomon_treasure_2":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-17");
			pchar.questTemp.HWIC.Eng = "AbigileInChurch";
			sld = characterFromId("Abigile");
			sld.greeting = "abigile_3";
			ChangeCharacterAddressGroup(sld, "Villemstad_church", "goto", "goto1");//Аби в церковь
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
//----------------------------------------------против всех---------------------------------------------	
		
		case "Abigile_kidnap":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Villemstad");
			dialog.text = "Levél? Ne is mondd! Figyelj ide gój, Mynheer Rodenburg egy lépésre van attól, hogy a vejem legyen. Elhúzhatod innen a segged, mert én kedvelem ôt!";
			link.l1 = "Figyelj, leszarom, hogy ki a vejed. Kötelességem átadni ezt a levelet Abigailnak. Tudja, hol találom meg ôt? És ki az ördög vagy te?";
			link.l1.go = "Abigile_kidnap_1";
		break;
		
		case "Abigile_kidnap_1":
			dialog.text = "Ki vagyok én? Én vagyok az apja, Solomon... És én nem kedvellek téged, gój.";
			link.l1 = "Jobban aggódnék, ha azt mondanád, hogy kedvelsz engem. Most akkor továbbra is lekezelôen fogsz bánni velem, vagy elkapod Abigailt? Még egyszer mondom, én vagyok a hírnök! Levelet hoztam a lányodnak!";
			link.l1.go = "Abigile_kidnap_2";
		break;
		
		case "Abigile_kidnap_2":
			dialog.text = "Add ide ezt a levelet! Átadom a lányomnak.";
			link.l1 = "Leborotválom a hajad és megcsipkedem az orrodat, mielôtt átadom neked ezt a levelet. Parancsom van, hogy személyesen adjam át neki ezt az üzenetet. Egy szót sem szóltak az apjáról, és nem is érdekel. Hol találom Abigailt?";
			link.l1.go = "Abigile_kidnap_3";
		break;
		
		case "Abigile_kidnap_3":
			dialog.text = "Amint kiabálok, fiatal gój, a város összes katonája azonnal itt lesz. Ne legyen olyan makacs, láthatja, hogy nálam van minden kártya.";
			link.l1 = "Jézus, Mária és József! József és József! És aztán mi lesz? Azt várod, hogy vasra verjenek, mert levelet kézbesítettem? Ne légy nevetséges!";
			link.l1.go = "Abigile_kidnap_4";
		break;
		
		case "Abigile_kidnap_4":
			DialogExit();
			sld = characterFromId("Abigile");
			ChangeCharacterAddressGroup(sld, "Villemstad_houseSP2", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_GoOver":
			dialog.text = "Meshuggeneh vagy? Félholtra izgatod szegény lányomat a leveleddel... Úgy döntött, hogy utána megy annak a hülye angol kapitánynak! Elhajózott az elsô szabad hajóval! Oy veyy, szegény lányom! Mit csináljon most ez az öreg zsidó? Az életem tönkrement! Ez egy szégyen! Hagyjatok a nyomorúságomra, vagy maradjatok és kárörvendjetek, nem érdekel! Ó, szegény Abigail! Apád ôsz fejét kétségbeesésében a pokolba vitted!";
			link.l1 = "Na, mit szólsz ehhez? Gondolom, egy percet sem tudott tovább várni. Viszlát, Solomon!";
			link.l1.go = "Abigile_GoOver_1";
		break;
		
		case "Abigile_GoOver_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-69");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
		break;
		
		case "Solomon_history":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "Hogy néz ki? Csak egy sziget, ahol nincs senki, csak én és Abigail. Ott rejtettem el a ládámat, hogy az a kalóz gój Amalek ne tudja elvenni. Minden, amit becsületesen, homlokom verejtékével kerestem, abban a ládában van...";
			link.l1 = "Mondd, Salamon, talán fel tudnád idézni annak a folyosónak a nevét, amelyrôl a lányod beszélt? És hogy hívták a kapitányát?";
			link.l1.go = "Solomon_history_1";
		break;
		
		case "Solomon_history_1":
			dialog.text = "Hmm... Hát, nem tudom. Ennek a szegény öreg zsidónak a feje úgy össze van törve, mint egy serpenyô gefilte hal! És miért kérdezed, fiatalember?";
			link.l1 = "Csak segíteni akarok a lányodnak, Salamon. Nem ígérhetek semmit, de szeretném megpróbálni. Az elôzô fônököm rosszul bánt vele, és ezek után azt hiszem, kötelességem segíteni neki, hogy valahogy rendbe jöjjön.";
			link.l1.go = "Solomon_history_2";
		break;
		
		case "Solomon_history_2":
			dialog.text = "Hát, ha ez a helyzet...";
			link.l1 = "";
			link.l1.go = "Solomon_history_3";
			pchar.questTemp.HWIC.Self = "SolomonHistoryNext";
		break;
		
		case "Solomon_history_3":
			DialogExit();
			sld = characterFromId("Abigile");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Solomon_thanks":
			dialog.text = "Fiatalember! Várjon!";
			link.l1 = "Igen?";
			link.l1.go = "Solomon_thanks_1";
		break;
		
		case "Solomon_thanks_1":
			dialog.text = "Fiatal ember! Szeretném megköszönni mindazt, amit értem és a lányomért tett. Megmentett minket. Sajnálom, hogy az elsô találkozásunkkor nehezen fogadtam, és hogy kételkedtem a segítô szándékában. Kérem, bocsásson meg ennek az öreg zsidónak. Ön valóban áldott ember a nem zsidók között. Most mondd csak, nem találtál mást, mint a pénzemet a barlangban?";
			link.l1 = "Nem, Salamon. A pénzen kívül semmi más nem volt ott. Van Berg gyilkosai ellen kellett harcolnom - ô volt az, aki hónapokkal ezelôtt elsüllyesztette a hajódat. Lehet, hogy már elloptak valamit... Mi másnak kellett volna ott lennie?";
			link.l1.go = "Solomon_thanks_2";
		break;
		
		case "Solomon_thanks_2":
			dialog.text = "Ó, semmi fontos... Egy ôsi családi ereklye... Hát, mindegy! Felejtsd el, úgyis egy balfácán volt! És... Csak még egy dolog, fiatalember... ";
			link.l1 = "Folytasd.";
			link.l1.go = "Solomon_thanks_3";
		break;
		
		case "Solomon_thanks_3":
			dialog.text = "Maga... nos, megtudtam valamit magáról. Kormányzónk nagyra becsüli önt, és ön egy neves kapitány. Elárulok egy titkot... a lányom nagyon kedveli magát. Ô maga mondta nekem. Talán... elgondolkozol ezen? Abigail nagyon jó kislány, biztosíthatom, jobb, mint bármelyik sicsa ribanc, akivel az utazásai során találkozott.";
			link.l1 = "Oy vey... Ez nem ilyen egyszerû, Solomon. A lánya valóban ritka ékszer. Jól vigyázol rá.";
			link.l1.go = "Solomon_thanks_4";
		break;
		
		case "Solomon_thanks_4":
			dialog.text = "Gondold át, fiatalember. Gondold át még egyszer, és gyere vissza! Szeretnénk újra látni téged!";
			link.l1 = "Persze... viszlát, Solomon.";
			link.l1.go = "Solomon_thanks_5";
		break;
		
		case "Solomon_thanks_5":
			DialogExit();
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload1", false);
			AddQuestRecord("Holl_Gambit", "3-65");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "Solomon_poor":
			dialog.text = "Oyyy... Néha lehetetlen új életet kezdeni, fiatalember. Szegénységben élni - mi lehet ennél rosszabb egy olyan vén szerencsétlennek, mint én?";
			link.l1 = "Sajnálom, Solomon. Maradj szilárd és keresd Krisztust.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Solomon_poor";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Maga egy "+ GetSexPhrase("tolvaj, uram! Ôrök, vigyétek","tolvaj, lány! Ôrök, vigyétek") +"!!!", "Csak nézd meg ezt! Amint elmerültem az elmélkedésben, úgy döntöttél, hogy megnézed a mellkasomat! Kapjátok el a tolvajt!!!", "ôrök! Rablás! Kapjátok el a tolvajt!!!");
			link.l1 = "A francba!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
