// Addon-2016 Jason, французские миниквесты (ФМК) Последний урок
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Egy nyilvánvaló bogár. Szólj róla a fejlesztôknek.";
			link.l1 = "Ó, meg fogom.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_04.wav");
			pchar.quest.FMQL_delete_guide.over = "yes";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
			if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Ó, "+GetFullName(pchar)+"! Másképp nézel ki barátom és sikeres vagy! Elkezdenek beszélni rólad, tudod? Gyorsan tanulsz, monseniour, nagyon büszke vagyok rád. További szerencsét és szerencsét kívánok neked a jövôben! Örülök, hogy újra találkozunk!";
				link.l1 = "Monseniour Gregoire Valinnie, micsoda találkozás! Sokkal tartozom önnek szerény eredményeimért. Öröm volt Önnel is találkozni! Sok szerencsét!";
				link.l1.go = "greguar_exit_1";
			}
			else
			{
				dialog.text = "Ó, "+GetFullName(pchar)+"! Másképp nézel ki barátom és sikeres vagy! Elkezdenek beszélni rólad, tudod? Gyorsan tanulsz, monseniour, azt kell mondanom, hogy büszkévé tettél.";
				link.l1 = "Monseniour Gregoire Valinnie, micsoda találkozó! Sokkal tartozom önnek szerény eredményeimért. Örülök, hogy megismerhettem! Hadd találjam ki, van egy üzleti ajánlata számomra?";
				link.l1.go = "greguar_1";
			}
		break;
		
		case "greguar_1":
			dialog.text = "Igenis! Igen, így van. Rövid leszek, az idô pénz. Szóval, egy holland koronás hajóraj, amely Brazíliából Curacaóba hajózott stratégiai értékû árukkal, az angolok rajtaütöttek Trinidad és a szárazföld között. A társaság egyik fuvolájának sikerült elmenekülnie és kikötni a Boca de la Serpienta partján. A rakomány egy részét megmentették, de nem sokáig - megtámadta ôket egy helyi indián törzs\nAz információim szerint minden hollandot kiirtottak azon a parton, és a rakományt a falujukba vitték. Az indiánok a hollandok lôfegyvereit is magukhoz ragadták, de súlyos veszteségeket szenvedtek. Ez a mi esélyünk! A britek és a hollandok még mindig azon a vidéken harcolnak, és túlságosan elfoglaltak ahhoz, hogy az elveszett furulyával törôdjenek. Egyelôre... Van egy hajód és egy legénységed. Elhajózhatunk oda, partra szállhatunk, és végezhetünk az indiánokkal. A rakomány rendkívül értékes, és nagy mennyiségben van ott\nMár elküldtem egy kisebb expedíciót felderítésre - csak ennyit engedhettem meg magamnak, emlékszel, pénzgondok? Van egy megbízható vevôm, számíthatsz a kardomra és a zsoldosaimra. Ötven-ötvenen osztozunk, egy hetünk van, hogy odaérjünk. Szóval barátom, benne vagy?";
			link.l1 = "Bocsásson meg, monseniour, de passzolok. Éppen egy kemény utazáson vagyok túl, nincs elég idônk a javításokra és a toborzásra. Még ezen az isten háta mögötti helyen sem lehet az embernek mindene.";
			link.l1.go = "greguar_exit";
			link.l2 = "Veszélyes üzletnek hangzik, tisztességes haszon és kalandok szagával. Természetesen benne vagyok! Ne vesztegessük az idôt!";
			link.l2.go = "greguar_2";
		break;
		
		case "greguar_exit":
			dialog.text = "Kár. Akkor a te döntésed. Isten éltessen, monseniour, én úgyis oda megyek. Az embernek meg kell próbálnia, nem?";
			link.l1 = "Isten éltessen, uram, Valinnie!";
			link.l1.go = "greguar_exit_1";
		break;
		
		case "greguar_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 20.0);
		break;
		
		case "greguar_2":
			dialog.text = "Jó választás, barátom! Jól jön a plusz pénz, igaz? Egyébként hogy van a bátyád?";
			link.l1 = "Mindig jól jön a plusz pénz. Michel? A bátyám jó egészségnek örvend, és unatkozik. Néha irigylem ôt... Ideje kihajózni!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_Begin");
		break;
		
		case "greguar_3":
			PlaySound("Voice\English\QuestMan02.wav");
			dialog.text = "Könnyû, mint a pite! Ezek voltak azok az újoncok, akik túlélték a hollandokkal való összecsapást. Mélyebbre kell mennünk a szárazföldön, az expedíciómnak ott kell lennie!";
			link.l1 = "Túl könnyûnek tûnt... de még túl korán van az ünnepléshez, Valinnie uram. Nézz csak oda...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_SecondCoastBattle");
		break;
		
		case "greguar_4":
			PlaySound("Voice\English\LE\Greguar\Greguar_05.wav");
			dialog.text = "A fenébe ezekkel a rézbôrûekkel! Majdnem elkaptak minket! Most már biztos vagyok benne, hogy csak nôk és gyerekek maradtak a faluban. Gyerünk, kifelé!";
			link.l1 = "Nem vagyok benne biztos, hogy muskétákat említettél. Nem láttam ôket... Áh, mindegy. Gyerünk, mozgás!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_GoToJungle");
		break;
		
		case "greguar_5":
			PlaySound("Voice\English\LE\Greguar\Greguar_06.wav");
			dialog.text = "Hogy érted? A hollandok és mi megöltük ôket!";
			link.l1 = "";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_7":
			dialog.text = "Menekülni? Megôrültél? Már majdnem ott vagyunk! Félsz egy csapat festett vadembertôl?";
			link.l1 = "";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_9":
			dialog.text = "A legalantasabbak közül a legalantasabbak, kapitány. Visszamegyek Európába. Csalódott vagyok! Benned, ezekben a gyávákban és ebben a kibaszott régióban!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			DialogExit();
			DoQuestReloadToLocation("shore18", "goto", "goto8", "FMQL_JungleExit");
		break;
		
		case "greguar_11":
			dialog.text = "Fuh! Megcsináltuk!";
			link.l1 = "De milyen áron! Nézzétek! A csapatunkból majdnem mindenki meghalt. Vissza kellene vonulnunk, Gregoire, nincs rá garancia, hogy több harcos vár ránk. Ráadásul egyszerûen nincs elég emberünk a zsákmányhoz.";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "A francba! Szomorú, de igazad van, "+pchar.name+": még ha a vademberek mind halottak is, nem fogjuk tudni elszállítani a rakományt, mielôtt a hollandok vagy az angolok partra szállnak. Azonnal el kell mennünk! Csessze meg ez az átkozott part!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_13":
			dialog.text = "Fuh! Megcsináltuk! Szép munka, "+pchar.name+"! Most pedig irány a vadak barlangja a nyereményünkért! Most már semmi sem állíthat meg minket!";
			link.l1 = "Sietnünk kell, amíg a britek és a hollandok még egymással vannak elfoglalva. Gyerünk!";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			DialogExit();
			DoQuestCheckDelay("FMQL_RunToGrabbing", 1.0);
		break;
		
		case "greguar_15":
			dialog.text = "Jól csináltuk, "+pchar.name+". Most már csak el kell adnunk a rakományt anélkül, hogy gyanút keltenénk. Van egy biztos vevôm, aki éjfélkor vár minket a Lamentin öbölben. Ne vigyenek tiszteket, és kerüljék el a helyet a találkozó elôtt, a vevô nagyon ideges fickó.";
			link.l1 = "Az üzlet az üzlet. A rakományt el kell adni, és biztonságosan kell megtenni, különben az adósságom Poincy felé még nagyobbra nô. Rendben, éjfélre ott leszek.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.quest.FMQL_goods_timer.win_condition.l1 = "Timer";
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQL_goods_timer.function = "FMQL_MeetingOnLamanten";
			AddQuestRecord("FMQ_Lesson", "7");
			LAi_LocationDisableOfficersGen("Shore38", true); // may-16
			LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], true);
			locations[FindLocation("Shore38")].DisableEncounters = true;
			Pchar.GenQuest.Hunter2Pause = true;
		break;
		
		case "greguar_17":
			PlaySound("Voice\English\Master_01.wav");
			pchar.quest.FMQL_goods_over.over = "yes";// лесник снято прерывание на встречу.
			dialog.text = "El van intézve. A rakományt kirakodták, az ügyfél itt van. Beszélgessünk.";
			link.l1 = "...";
			link.l1.go = "greguar_18";
		break;
		
		case "greguar_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("FMQL_contra_"+i);
				if (i == 2) 
				{
					LAi_CharacterEnableDialog(sld);
					AddLandQuestMark(sld, "questmarkmain");
				}
			}
		break;
		
		case "greguar_19":
			dialog.text = "Meglepetés, ti szemetek!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_LookOnGuards");
		break;
		
		case "greguar_20":
			PlaySound("Voice\English\OliverTrast01.wav");
			dialog.text = "Á, Johnny, micsoda fickó! Nagyszerû! Van valami mondanivalód, "+pchar.name+"?";
			link.l1 = "Nem. Igazából, igen! Mi a fasz?!";
			link.l1.go = "greguar_21";
		break;
		
		case "greguar_21":
			dialog.text = "Ne piszkáld a halottat, uram. Hol van a jó modorod? A pénz itt van, a szállítmányt én és a barátaim elintézzük. Nem küldtem ôket a tengerpartra, kár lett volna érte. Fôleg Johnny-t nem. Látod azt a rézbôrû fickót, egy coulevrinával a kezében? Tudod, Johnny sosem szerette igazán a saját törzsét.";
			link.l1 = "Értem... Most mi lesz? Engem is meg fogsz ölni?";
			link.l1.go = "greguar_22";
		break;
		
		case "greguar_22":
			dialog.text = "Nos, meg kéne. De szentimentális vagyok. Menj el, és vidd el a pénz negyedét. A rakomány és a többi pénz itt marad velem. Ne próbálj hôst játszani, ez nem a szárazföld dzsungele. Nincs esélyed.";
			link.l1 = "És hol van a nemességed és a modorod, Gregoire? Ezt nem gondoltam volna, hogy ezt fogod csinálni. Elmegyek, de ezt nem felejtem el.";
			link.l1.go = "greguar_23";
			link.l2 = "Nem játszom a hôst, soha nem is tettem. Egyszerûen megöllek titeket! Elôször ezeket a hölgyeket, aztán a majmot a gránátvetôvel, aztán téged!";
			link.l2.go = "greguar_25";
		break;
		
		case "greguar_23":
			dialog.text = "Ezen a parton nincsenek sem nemesek, sem gengszterek, uram. Csak öt ember van, egy nagy fegyver és egy áldozat. Itt mindig ez történik, de te az egyetlen helyes döntést hoztad. Szép munka. Tudja, hogy maga helyett két másik ember is állhatna a maga helyében, itt és most? Ôk majdnem olyanok, mint te. De te itt vagy, ôk pedig nem, és szerintem emiatt el fognak pusztulni.";
			link.l1 = "Nem tudom követni...";
			link.l1.go = "greguar_24";
		break;
		
		case "greguar_24":
			dialog.text = "Egy nap majd fogsz. Nem kapták meg a végsô leckét. Te kaptad meg. Szívesen látlak. Viszlát, uram. Isten hozott a Karib-tengeren!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_PeaceFinal");
		break;
		
		case "greguar_25":
			dialog.text = "Ahh... Nem te vagy a legokosabb diákom. Rendben... mindenkinek a sajátja!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_BattleOnBeach");
		break;
		
		case "mercen":
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "Tökéletes idôzítés! Alig menekültünk el a karibok hordája elôl, máris felétek tartottak, és a tekinteted alapján máris találkoztál velük. A falujuk a közelben van, de a problémáink csak most kezdôdnek.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper":
			dialog.text = ""+GetFullName(pchar)+"! Hát itt vagytok! És miért nem vagyok meglepve! Tökéletes idôzítés, barátom. Alig menekültünk el a karibok hordája elôl, máris felétek tartottak, és a tekinteted alapján máris találkoztál velük.";
			link.l1 = "Prosper! Meg vagyok lepve! Megint lyukakat csinálsz az indiánokba? Remélem, Selina jól van?";
			link.l1.go = "prosper_1";
		break;
		
		case "prosper_1":
			dialog.text = "Bolondság volt tôlem, hogy csatlakoztam ehhez az expedícióhoz, kíváncsi vagyok, hogy a lányom valaha is viszontlát-e engem. Selina? Nos, otthon ül és rólad álmodik! A martinique-i fiatalok már minden reményt elvesztettek... Tudod, már nem bánom, hogy megvettem ezt a muskétát. Szilárd lôfegyver. Megbízható. Szintén egy újabb ok arra, hogy részt vegyek egy újabb öngyilkos vállalkozásban, bár ez most egy kicsit kevésbé öngyilkos, mióta felbukkantál. A falujuk a közelben van, de a problémáink csak most kezdôdnek.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper_2":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_3":
			dialog.text = "Nem mindegyik. A felderítônket meglôtték, de így is sikerült eljutni a búvóhelyükre. Maga a törzsfônök is ide tart az ôrségével. És holland muskéták vannak náluk. Számbeli fölényben vannak, és pokolian dühösek. A törzsfônök a törzsük legjobb harcosa, az emberei hús-vér ördögök. Gyorsan kell döntenünk, itt és most. Vagy harcolunk velük, vagy elmenekülünk. Én inkább az utóbbit választanám, hogy ôszinte legyek...";
			link.l1 = "";
			link.l1.go = "prosper_4";
		break;
		
		case "prosper_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_5":
			dialog.text = "Nem láttad ôket, jóember! Ezeknek 'savage-oknak' van muskétájuk, és meglepôen jól bánnak vele. Valaki leckéket adott nekik, ez nem kétséges! Úgyhogy ne nevezz megint gyávának!";
			link.l1 = "Nyugodjunk meg, és döntsük el, mit tegyünk. Még van idônk.";
			link.l1.go = "prosper_6";
		break;
		
		case "prosper_6":
			int n = 0;
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("FMQL_sailor_"+i) != -1) n++;
			}
			dialog.text = "Figyelek, "+pchar.name+".";
			if (n > 2 && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 30)
			{
				link.l1 = "Harcolni fogunk velük, fiúk! A domb mögött van áru és pénz! Itt vagyunk értük, és nem megyünk el. Kizárt, hogy egy csapat rézbôrû, még muskétával sem állíthat meg minket! Temessük el a rohadékokat és fejezzük be a munkát! Van elég emberünk, van esélyünk rajtaütni rajtuk. Négy ember fogadja ôket tûzzel az oldalról, mi többiek pedig itt foglaljuk el a pozíciónkat. Vágjuk le a létszámukat és végezzünk velük!";
				link.l1.go = "prosper_8";
			}
			else
			{
				if (n > 0)
				{
					link.l1 = "Harcolni fogunk velük, fiúk! A domb mögött áru és pénz van! Mi miattuk vagyunk itt, és nem megyünk el. Kizárt, hogy egy csapat rézbôrû, még muskétával sem állíthat meg minket! Temessük el a rohadékokat és fejezzük be a munkát!";
					link.l1.go = "prosper_7";
				}
				else
				{
					link.l1 = "Az esélyek minden lehetséges módon ellenünk szólnak. Ne feledkezzünk meg a hollandokról, akik mögöttünk vannak.";
					link.l1.go = "prosper_9";
				}
			}
		break;
		
		case "prosper_9":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_7":
			DialogExit();
			pchar.questTemp.FMQL = "battle";
			AddDialogExitQuestFunction("FMQL_PrepareAttack");
		break;
		
		case "prosper_8":
			DialogExit();
			pchar.questTemp.FMQL = "sneak";
			AddDialogExitQuestFunction("FMQL_PrepareSneakAttack");
		break;
		
		case "prosper_9x":
			dialog.text = "Élünk és otthon vagyunk! Esküszöm, elég volt a kalandokból... a következô néhány hónapra, ha-ha! Mennem kell a lányomhoz, kérem látogasson meg minket, "+pchar.name+". És kérlek, légy óvatos!";
			link.l1 = "Nem ígérhetek semmit, Prosper. Isten éltessen!";
			link.l1.go = "prosper_10";
		break;
		
		case "prosper_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
		break;
		
		case "prosper_11":
			pchar.quest.FMQL_prosper_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "Figyelmeztettelek, kapitány, hogy légy óvatos! Gyanakodtam erre a fattyúra.";
			link.l1 = "Prosper! Köszönöm! De hogyan?";
			link.l1.go = "prosper_12";
		break;
		
		case "prosper_12":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.FMQL.PirateDead")) sTemp = "Szegény fiú, pedig kalóz volt.";
			dialog.text = "Johnny túl beszédes lett. A vörösbôrû fickó a homokban. Elment egy bordélyházba, és megpróbált felszedni egy lányt. Nem voltak hajlandóak kiszolgálni, Johnny dühös lett, elkezdte kiabálni, hogy hamarosan gazdag lesz, ha egyszer ô és a haverjai megölnek valami kapitányt a dzsungelben. Láttam, mi következik, és odarohantam a tisztjéhez, akinek szintén sikerült némi hírhedtséget szereznie a városban. "+sTemp+" sokat köszönhetek neked, "+pchar.name+", úgyhogy nem kell túlságosan megköszönnöd.";
			link.l1 = "És mégis nagyon szépen köszönöm, Prosper! Kemény volt itt... túl kemény. Akarsz csatlakozni a csapatomhoz? Szükségem van egy olyan tisztre, mint te. Nehéz manapság hûséges embereket találni, különösen mesterlövészeket.";
			link.l1.go = "prosper_13";
		break;
		
		case "prosper_13":
			dialog.text = "Nem, barátom. Kötelezettségeim vannak a lányommal szemben. Megesketett, hogy magam mögött hagyom a kalandjaimat. Ez volt az utolsó. A fenébe is, milyen kár, de a lányomat mindennél jobban szeretem a világon. Isten veled, "+pchar.name+". És... Selina állandóan rólad beszél. Talán egyszer meglátogathatnál minket?";
			link.l1 = "Ki tudja, talán fogok is... Viszlát, Prosper! Kívánom, hogy a lányod találjon egy jó férjet... (magának) A leckét megtanulta, monsieur Gregoire, a leckét megtanulta... mindenkinek a sajátja, mondta... Ezt nem felejtem el.";
			link.l1.go = "prosper_14";
		break;
		
		case "prosper_14":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "15");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "contra":
			DelLandQuestMark(npchar);
			dialog.text = "Ki a fene maga?";
			link.l1 = "Megvan a rakomány. Érdekli?";
			link.l1.go = "contra_1";
		break;
		
		case "contra_1":
			dialog.text = "Ha. Nagyon érdekes. Az ügyfelemet különösen. Mi a helyzet?";
			link.l1 = ""+FindRussianQtyString(sti(pchar.questTemp.FMQL.Sanl))+" vasfából, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Silk))+" hajóselyembôl, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Rope))+" kötélbôl és "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Oil))+" gyantából.";
			link.l1.go = "contra_2";
		break;
		
		case "contra_2":// Addon 2016-1 Jason пиратская линейка
			iTotalTemp = 2200*sti(pchar.questTemp.FMQL.Sanl)+1600*sti(pchar.questTemp.FMQL.Silk)+1000*sti(pchar.questTemp.FMQL.Rope)+900*sti(pchar.questTemp.FMQL.Oil);
			dialog.text = "Nagyon jó. 2200 pezó minden egyes darab vasfáért, 900 pezó a gyantáért, 1600 pezó a hajóselyemért és 1000 pezó a kötelekért. Mi van itt... Nos, nos... "+iTotalTemp+" pezó. Megegyeztünk?";
			link.l1 = "Áll az alku!";
			link.l1.go = "contra_3";
		break;
		
		case "contra_3":
			LAi_Fade("", "");
			FMQL_CreateGuidesWarriors();
			dialog.text = "Pompás! Hozz még. A hollandok mindig nagylelkûek a rézbôrûekkel... És kik ezek a vendégek? Mi a fasz?!";
			link.l1 = "";
			link.l1.go = "contra_4";
		break;
		
		case "contra_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_19";
			AddMoneyToCharacter(sld, iTotalTemp);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FMQL_beach":
			pchar.quest.FMQL_pirate_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			dialog.text = "Igen, kapitány. Okkal ittam túl a vitorlást.";
			link.l1 = "És te? Hogy?!";
			link.l1.go = "FMQL_beach_1";
		break;
		
		case "FMQL_beach_1":
			dialog.text = "Sajnálom, kapitány. Meg kellett innom egy-két pohárral az indiánokkal való balhé után. Volt egy lány, kivettem egy szobát száz pezóért, és ô... ô... ô...";
			link.l1 = "Micsoda? Kirabolta magát?";
			link.l1.go = "FMQL_beach_2";
		break;
		
		case "FMQL_beach_2":
			sld = CharacterFromID("FMQL_Prosper");
			dialog.text = "Nem! Beleszeretett! A francba, el kellett volna szöknöm onnan! De aztán megjelent a barátod, és ordibált velem errôl a söpredékrôl, a volt társadról, aki meg akar dugni és meg akar ölni.";
			if (LAi_GetCharacterHP(sld) > 0)
			{
				link.l1 = "Szép munka, Prosper...";
				link.l1.go = "FMQL_beach_3";
			}
			else
			{
				link.l1 = "Prosper... Nagyon sajnálom. Vigyázni fogok a lányodra. A leckét megtanultam, Gregoire úr... Mit mondtál? Mindenki a maga módján? Ezt nem szabad elfelejtenem.";
				link.l1.go = "FMQL_beach_3";
			}
		break;
		
		case "FMQL_beach_3":
			dialog.text = "Mehetünk, kapitány?";
			link.l1 = "Igen, uram. Köszönöm a szolgálatot. Maradjon távol a csészétôl, és megmentjük ettôl a szépségtôl. Gyerünk, menjünk.";
			if (CheckAttribute(pchar, "questTemp.FMQL.ProsperDead")) link.l1.go = "FMQL_beach_5";
			else link.l1.go = "FMQL_beach_4";
		break;
		
		case "FMQL_beach_4": // Проспер жив
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload_sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			sld = CharacterFromID("FMQL_Prosper");
			sld.Dialog.currentnode = "prosper_11";
			sld.MusketerDistance = 20;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		break;
		
		case "FMQL_beach_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			if (sti(pchar.money) >= 20000) DoQuestFunctionDelay("FMQL_MoneyForSelina", 0.5);
			else
			{
				pchar.quest.FMQL_money_20k.win_condition.l1 = "Money";
				pchar.quest.FMQL_money_20k.win_condition.l1.value = 20000;
				pchar.quest.FMQL_money_20k.win_condition.l1.operation = ">=";
				pchar.quest.FMQL_money_20k.function = "FMQL_MoneyForSelina";
			}
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "10");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
