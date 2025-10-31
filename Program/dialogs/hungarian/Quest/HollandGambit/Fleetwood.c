// Ричард Флитвуд - английский капитан
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "Start_main")
				{
					dialog.text = "Üdvözlöm, kapitány! Ne zavarjon meg a külsôm, jól vagyok, majdnem vak, de jól vagyok. Hadd mutatkozzam be, Richard Fleetwood vagyok.";
					link.l1 = "Jó napot, örülök, hogy megismerhetem, én vagyok a kapitány " + GetFullName(pchar) + ".";
					link.l1.go = "First_Task";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "GotoPortoffice")
				{
					if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
					{
						dialog.text = "Megkértem, hogy kössék ki a hajójukat. Figyel rám egyáltalán?";
						link.l1 = "Persze, hogy hallgatok. Vigyázok rá.";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Szóval, megint itt vagy. Vedd át a 'Valkyrie parancsnokságát - a legénységemet figyelmeztették a részletekre -, és hajózz el Bridgetownba. Látogassatok meg minden érdeklôdôt a városban, és terjesszétek a pletykákat, amikrôl beszéltünk. Aztán készüljetek fel a fattyú támadására. Ne cseréljetek hajót, és ne csináljatok rajthajót, különben csapdát sejt, és nem fog megjelenni\na hajójára kell szállnotok, és el kell szállítanotok St. John' s-ba. Feltétlenül meg kell találnod a kalóz naplóját, mivel ez az egyetlen bizonyítékunk Lucas Rodenburg részvételére. Biztos vagyok benne, hogy megoldja ezt. Sok szerencsét, kapitány.";
						link.l1 = "Köszönöm! A tervünk szerint fogom elvégezni a munkát.";
						link.l1.go = "First_Task_3";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
					}
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "MirageTake")//а вот теперь начинается перебор кораблей
				{
					pchar.quest.ToAntiguaMirageOver.over = "yes"; //снять таймер
					int iMir = 0;
					int iVal = 0;
					for(i = 0; i < COMPANION_MAX; i++)
					{
						iTemp = GetCompanionIndex(PChar, i);
						if(iTemp > 0)
						{
							sld = GetCharacter(iTemp);
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE)
							{
							iMir = 1;
							RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;//чистый корпус
							SetShipSailsFromFile(sld, "ships/parus_silk.tga");
							SetSailsColor(sld, 0);//белый хлопковый парус
							DeleteAttribute(sld, "ship.sails");//починить паруса
							DeleteAttribute(sld, "ship.masts");//вернуть мачты
							}
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
						}
					}//установили признак наличия кораблей в эскадре.
					if (iMir == 1 && iVal == 0)//потеряли Валькирию
					{
						dialog.text = "Visszatért, kapitány... Már mindent tudok az útjáról.";
						link.l1 = "Tudja? Szóval tudnia kell, hogy...";
						link.l1.go = "Fleetwood_lostVal";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 1)//потеряли Мираж
					{
						dialog.text = "Visszatért, kapitány... Már mindent tudok az útjáról.";
						link.l1 = "Tudja? Szóval tudnia kell, hogy...";
						link.l1.go = "Fleetwood_lostMir";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 0)//а это вообще плохо
					{
						dialog.text = "Visszatért, kapitány... Már mindent tudok az útjáról.";
						link.l1 = "Tudja? Szóval tudnia kell, hogy...";
						link.l1.go = "Fleetwood_lostFull";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
						dialog.text = "Visszatért, kapitány... Már mindent tudok az útjáról.";
						link.l1 = "Tudja? Szóval tudnia kell, hogy...";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "toAntigua")
				{
					dialog.text = "Üdvözletem, barátom! Örülök, hogy látlak! Abigail a hajón van?";
					link.l1 = "Sajnos nincs, Richard. Nem volt hajlandó velem jönni, mert a távozása súlyos csapás lenne az apjának, aki már minden egyes érmét elvesztette. Úgy döntöttem, hogy megoldom a problémát, és megkeresem Salamon pénzét és azt a szigetet...";
					link.l1.go = "Fleetwood_LastTask";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				dialog.text = "Még valami, kapitány?";
				link.l1 = "Nem, máris indulok.";
				link.l1.go = "exit";		
				NextDiag.TempNode = "First time";
			}
				dialog.text = "Még valami, kapitány?";
				link.l1 = "Nem, én máris megyek.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Fleetwood_abordage":
			PlaySound("Voice\English\hambit\Richard Flitwood-03.wav");
			dialog.text = "Átkozott kalóz! Megnyertétek a partraszállási harcot, de én mégis teljesítem a kötelességemet. Elintéztem, hogy meggyújtsam a puskaporos szobát, és a hajóm hamarosan felrobban a te 'Ghost Ship'. szellemhajóddal együtt, és többé nem fogsz elsüllyeszteni egyetlen angol hajót sem. Becsülettel fogok meghalni!";
			link.l1 = "Sajnálom, hogy csalódást kell okoznom, de tévedsz, Fleetwood. Az én hajómon nincsenek kalózok, már volt dolgom velük korábban is. Szükségem volt rád, és ez a hajó szép csapdaként szolgált.\nElég a kedves szavakból, még mindig meg kell öljelek, és el kell tûnnöm a lángoló kádadból!";
			link.l1.go = "Fleetwood_abordage_1";
		break;
		
		case "Fleetwood_abordage_1":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.HWIC.Holl = "FleetwoodCapture";
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "First_Task":
			dialog.text = "Charlie már tájékoztatott az ellenséges kereskedelmi karaván sikeres elfogásáról. Örülök, hogy megismerhetlek, Angliának szüksége van ilyen bátor kapitányokra. Most pedig hadd mondjak neked valami nagyon fontosat.";
			link.l1 = "Hallgatom, Mr. Fleetwood.";
			link.l1.go = "First_Task_1";			
		break;
		
		case "First_Task_1":
			dialog.text = "Egy kalóz erôszakos cselekményeket követ el az egész szigetvilágban, és a 'Flying Dutchman', legendás szellemhajónak álcázza magát. A 'Flying Dutchman', legendás szellemhajónak adja ki magát. Biztos vagyok benne, hogy ô egy holland, de nem tud repülni. Hajlamos vagyok azt hinni, hogy ez Lucas Rodenburg, a Holland Nyugat-indiai Társaság igazgatóhelyettese zsoldosa.\nRodenburg árnyékkereskedelmi háborút hirdetett Anglia ellen - ez 'szellemhajó' támadja meg az egyetlen angol zászló alatt közlekedô kereskedelmi hajót. A társaság számára létfontosságú, hogy valódi háború nélkül gyengítse a befolyásunkat ezen a területen.\nEzt a szellemhajót már egy ideje vadászom, de a kapitánya nagyon tapasztalt tengerész, a hajója pedig gyors és ravasz.\nMivel lehetetlen nyílt harcban elkapni a sakált, akkor ravaszul kell cselekednünk, és a nemrég ellenem elkövetett merénylet nagy szolgálatot tesz nekünk. Mit gondolsz errôl, kapitány? Megijedtél?";
			link.l1 = "Kizárt dolog. Örömmel segítenék a nyomára bukkanni és elsüllyeszteni ezt a fattyút. Erre akart megkérni, igazam van?";
			link.l1.go = "First_Task_2";	
		break;
		
		case "First_Task_2":
			dialog.text = "Igazad van. Most pedig beszéljünk a részletekrôl. Az embereim elterjesztik a pletykát, hogy majdnem halott vagyok, és eladtam a hajómat, a 'Valkyrie' t neked. Ezután folytatjuk a kis csalásunkat. Úgy fogsz tenni, mintha egy kereskedô lennél, aki megvásárolta tôlem a brigget, és megszabadult a legtöbb ágyútól.\nA feladatod tehát az, hogy elhajózz Barbadosra, és ott mindenkinek elmondd, hogy a raktered tele van értékes rakománnyal, a zsebeid pedig tele vannak pénzérmékkel. Tudasd velük, hogy hamarosan kihajózol. Játszd el a kapzsi, egyszerû, de gazdag kereskedô szerepét.\nAz átkozott hollandunk Bridgetownnál kapja az információt a kereskedelmi hajóról. Nem tudni, hogy pontosan ki látja el vele. Mindenki gyanúba keveredik - a helyi kereskedôtôl kezdve a kormányzóig, bár ez utóbbi lehetôség elég rémisztô.\nVezesd a 'Valkyrie' és legénységét. De elôbb hagyja itt az összes hajóját, már beszéltem a helyi kikötômesterrel, havi 10 000 pesóba fog kerülni a zászlóshajója.\nHa ez megtörtént, térjen vissza hozzám, és intézkedem. Á, kapitány, ne felejtsd el a részedet az ezüstkaraván elfogásáért és a tízezret a kikötômesternek, a pénz a fiókban van.";
			link.l1 = "Megvan, Mr. Fleetwood. Megyek a kikötômesterhez.";
			link.l1.go = "exit";	
			pchar.questTemp.HWIC.Eng = "GotoPortoffice";
			bDisableFastReload = false;//откроем быстрый переход
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			AddLandQuestMark(characterFromId("SentJons_PortMan"), "questmarkmain");
		break;
		
		case "First_Task_3":
			DialogExit();
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.EngEquip = "true"; //форма солдат
			pchar.questTemp.HWIC.Eng = "GotoBridgetown";
			GetValckiriaToCharacter(pchar);
			pchar.quest.Knippel_Officer.win_condition.l1 = "location";
			pchar.quest.Knippel_Officer.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Knippel_Officer.function = "KnippelToOfficer";
			pchar.questTemp.HWIC.Eng.BridgeCounter = 0;//счетчик посещений неписей Бриджтауна по квесту
			AddQuestRecord("Holl_Gambit", "2-5");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_shipyarder"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Mayor"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_usurer"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_PortMan"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Hostess"), "questmarkmain");
		break;
		
		//изымаем корабль
		case "Fleetwood_lostMir":
			dialog.text = "Igen, tisztában vagyok vele, hogy kudarcot vallott a kalózhajó elfogása. Minden tervemet tönkretettem. Elveszem 'Valkyrie' tôled. Most már elmehet, nincs szükségem a szolgálataira.";
			link.l1 = "Nagyon sajnálom. Viszlát, Mr. Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
		break;
		
		case "Fleetwood_lostVal":
			dialog.text = "Igen, tisztában vagyok vele, hogy elvesztetted 'Valkyrie'. Ez volt a legelfogadhatatlanabb... El fogom vinni az elfogott kalózhajót. Most már elmehet, nincs szükségem a szolgálataira.";
			link.l1 = "Nagyon sajnálom. Viszlát, Mr. Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_MIRAGE;
		break;
		
		case "Fleetwood_lostFull":
			dialog.text = "Igen, tisztában vagyok vele, hogy ön egy ritka zavaros és zavaros ember. Nem foglaltad el a kalózhajót és elvesztetted a 'Valkyrie'. nagyon csalódott vagyok benned. Kifelé!";
			link.l1 = "Nagyon sajnálom. Viszlát, Mr. Fleetwood.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Knippel");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Книппеля из офицеров
			sld = characterFromId("Knippel");
			ChangeCharacterAddressGroup(sld, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("Azt mondják, hogy Richard Fleetwood valamilyen titkos megbízását buktad el. Nos, most már nincs semmi dolgod Antiguán...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("Azt mondják, hogy Richard Fleetwood valamilyen titkos megbízását buktad el. Nos, most már nincs semmi dolgod Antiguán...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_complete":
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");	
			if (CheckCharacterItem(pchar, "JacobJournal"))//проверяем журнал
			{
				dialog.text = "Igen, tudom, hogy sikerrel jártál a tervünkben. Megsemmisítetted a gonosz kalózt és elfoglaltad a hajóját. Mi a valódi neve?";
				link.l1 = "Délibáb";
				link.l1.go = "Abigile";
			}
			else//нет журнала - нет продолжения квеста
			{
				dialog.text = "Igen, tisztában vagyok vele, hogy sikerrel jártál a tervünkben. Megsemmisítetted a gonosz kalózt és elfoglaltad a hajóját. Visszaviszem a 'Valkyrie' vissza.A kalózhajót megtarthatod zsákmányként. Ez egyfajta... kárpótlásként is szolgál majd. A kikötôben lehorgonyzott hajód leégett, amikor a tûz a dokkokban terjedni kezdett. Elnézést kérek a kellemetlenségért, " + pchar.name + "... Remélem, a szellemhajó jobban fog szolgálni.\nMegparancsoltam, hogy az új hajótokat tisztítsák meg a makacs szennyezôdésektôl és a hínártól. Szépségedet a legjobb pamutból készült új vitorlákba is öltöztetik.\nVégül, kérlek, fogadd el a 100 000 pezó jutalmat és ezt a navigációs eszközt. Mindig is szerettem volna átadni egy arra érdemes hajósnak, és te csodálatra méltó munkát végeztél odakint! Nos, eljött a búcsú ideje, elvégeztem itt a dolgomat, és vissza kell térnem Európába. Sok szerencsét, kapitány úr!";
				link.l1 = "Neked is, Richard!";
				link.l1.go = "exit";
				LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//закроем Флитвуда в комнате и пусть там сидит
				pchar.questTemp.HWIC.Eng = "end";
				pchar.questTemp.HWIC.Detector = "eng_win_half";
				CloseQuestHeader("Holl_Gambit");
			}
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "bussol");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			AddSimpleRumourCity("Azt mondják, hogy te és Richard Fleetwood valami katonai akciót terveztek, és személyesen te pusztítottad el azt a megfoghatatlan kalózt, aki kirabolta a kereskedelmi hajóinkat. Igazi hôs vagy, kapitány!", "SentJons", 20, 3, "");
		break;
		
		case "Abigile":
			dialog.text = "Káprázat? Azt mondanám, hogy ez egy nagyon megfelelô név... Elveszem a 'Valkyrie' visszaveszem tôled, és ezért megtarthatod a kalózhajót jutalomként. Ez egyfajta kárpótlásként is szolgál majd. A kikötôben lehorgonyzott hajód leégett, amikor a tûz a dokkokban terjedni kezdett. Sajnálom, " + pchar.name + "... Remélem, a szellemhajó jobban fog szolgálni.\nMegparancsoltam, hogy tisztítsák meg az új hajótokat attól a makacs szennyezôdéstôl és hínártól. Szépségedet új vitorlákba is öltöztetik, a legjobb pamutból.\nVégül fogadd el a 100 000 pezó jutalmat és ezt a navigációs eszközt, mindig is át akartam adni egy méltó tengerésznek... Jó munkát végeztél odakint, és büszke vagyok rád! Megvan a rohadék naplója?";
			link.l1 = "Igen, persze. Itt van, vedd el. Szeretnék kérdezni valamit, van valami... ázsiai Lucas Rodenburg bérencei között?";
			link.l1.go = "Abigile_1";			
		break;
		
		case "Abigile_1":
			RemoveItems(PChar, "JacobJournal", 1);
			dialog.text = "Igen, van. Kínai Longway, a magánhajójának kapitánya 'Meifeng'. Ezt olvastad a kalóz naplójából? Nézzük csak...(olvasás) Lám, lám. Ahogy vártam, Lucas Rodenburg állt mindezek mögött! Hát, mindegy, ez most nem a mi dolgunk... A fôkormányzónk majd elintézi ezt a szemetet. Lucas Rodenburgnak vállalnia kell a felelôsséget mindazért, amit tett!";
			link.l1 = "Hm, érdekes, és hogyan lesz képes az angol fôkormányzó 'megbirkózni' egy holland alattvalóval?";
			link.l1.go = "Abigile_2";			
		break;
		
		case "Abigile_2":
			dialog.text = "Mindig vannak politikai szálak, amiket meg lehet mozgatni, kedves barátom... Hollandiának el kell majd ismernie, hogy ôk kezdték a kereskedelmi háborút Anglia ellen, de nem valószínû, hogy ezt meg is teszik. Ehelyett mindenért Rodenburgot fogják hibáztatni. Lucas lehet, hogy elveszíti a pozícióját, de az is lehet, hogy nem. Akárhogy is, a karrierje súlyos csapást fog szenvedni.\nMindenesetre ez most nem a mi dolgunk, kapitány úr. Ön jól végezte a munkájából a maga részét. Ezért van még egy nagyon kényes ügyem az ön számára.";
			link.l1 = "Hallgatom, Richard. Ki lesz az angol korona következô ellensége, akit ezúttal el kell pusztítani?";
			link.l1.go = "Abigile_3";			
		break;
		
		case "Abigile_3":
			dialog.text = "Nem, arra szeretném kérni, hogy ezúttal egy sokkal személyesebb és békésebb üggyel foglalkozzon. Hadd meséljek el egy rövid történetet, ami egyébként az ön 'Mirage'.önre vonatkozik.";
			link.l1 = "Folytasd.";
			link.l1.go = "Abigile_4";			
		break;
		
		case "Abigile_4":
			dialog.text = "Egy hónappal a találkozásunk elôtt egy rajtaütésen voltam, a szellemhajóra vadásztam. Martinique-tól délre volt, nem messze a 64. hosszúsági foktól. 41'. Hallottuk, hogy valahol a távolban harc folyik, de a szél túl gyenge volt, így nem értünk oda idôben. Egy angol flótást elsüllyesztett egy szellemhajó valami kis sziget közelében, ami még a térképre sem került fel\nnem sikerült elkapnom a kalózt, és úgy döntöttem, hogy meglátogatom azt a szigetet, remélve, hogy találok túlélôket. És meg is találtam ôket. Egy zsidó menekültpárt, apát és lányát. A lányt Abigailnek hívták, és gyönyörû volt! Egy élô csoda... A fedélzetre vettem ôket, és Curacaóra szállítottam, bár a lány apja, Salamon, nem mutatott sok szimpátiát irántam\nAmennyire értettem, azt hitte, hogy én vagyok a kalóz, aki elsüllyesztette a hajójukat, az öreg nem sokat tud a hajókról és a köztük lévô különbségekrôl. Abigail és én azon a kis utazáson összebarátkoztunk, vagy, hogy teljesen ôszinte legyek, egymásba szerettünk. Hát nem egy történet?\nÉs nemrég tudtam meg, hogy az a fattyú Rodenburg már egy ideje udvarol az én Abigailomnak, gondolj csak bele! Ide akartam ôt vinni, amint megoldom az apja elveszett pénzével kapcsolatos ügyet, minden egyes érmét azon a szigeten rejtette el, amit említettem. Nem sikerült megtalálnom a helyét. Nem várhatunk tovább\nMivel az egészségem még mindig nem engedi, hogy magam hajózzak ki, arra kérlek, menj el Willemstadba, keresd meg Abigailt, és hozd ide. Említsd meg a nevemet, és ô bízni fog benned.";
			link.l1 = "Ne lássak semmi problémát ebben az ügyben. Készen állok a vitorlázásra.";
			link.l1.go = "Abigile_5";			
		break;
		
		case "Abigile_5":
			PlaySound("Voice\English\hambit\Richard Flitwood-02.wav");
			dialog.text = "Kiváló! Örülök, hogy számíthatok rád, " + pchar.name + ". A munkád jól meg lesz fizetve, ne aggódj emiatt.";
			link.l1 = "Nem akarom, hogy túl sokáig kelljen várnod. Hamarosan találkozunk, Richard!";
			link.l1.go = "Abigile_6";			
		break;
		
		case "Abigile_6":
			DialogExit();
			npchar.greeting = "fleetwood_2";
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload2", true);//закроем спальню Аби
			AddQuestRecord("Holl_Gambit", "2-16");
			pchar.questTemp.HWIC.Eng = "toAbigile";
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			sld.greeting = "barmen_1";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Fleetwood_LastTask":
			dialog.text = "" + pchar.name + ", Tényleg úgy döntöttél, hogy megtalálod a szigetet? Le vagyok nyûgözve a nagylelkûségedtôl. Megtaláltad?";
			link.l1 = "Igen, megtaláltam. Sajnos, itt kezdôdnek a rossz hírek. Alig tudtam élve megmenekülni arról az átkozott helyrôl... Még mindig reszketek, ha rágondolok...";
			link.l1.go = "Fleetwood_LastTask_1";
		break;
		
		case "Fleetwood_LastTask_1":
			dialog.text = "Mi történt ott? Mondd el, barátom, ne hagyj bizonytalanságban!";
			link.l1 = "A szigetre érkeztem, és a barlang felé vettem az irányt, ahol Salamon valószínûleg elrejtette a ládáját. Tényleg ott volt. De amikor megérintettem, valami ismeretlen erô feldobott. Robbanást hallottam, és a ládától tíz lábnyira a földre zuhantam...";
			link.l1.go = "Fleetwood_LastTask_2";
		break;
		
		case "Fleetwood_LastTask_2":
			dialog.text = "Hihetetlen!";
			link.l1 = "Alig éltem túl - néhány fájdalmas karcolást szereztem. Amikor magamhoz tértem, ijesztô zajok zúgtak a fejemben, és a szörnyû lény megjelent egyenesen a földbôl... ó, Istenem, az a szörnyeteg!";
			link.l1.go = "Fleetwood_LastTask_3";
		break;
		
		case "Fleetwood_LastTask_3":
			dialog.text = "" + pchar.name + "...";
			link.l1 = "Richard, nem vagyok ôrült. Tényleg megtörtént, bár én magam is alig hiszek ebben. Egy teljesen kiszáradt és kifestett indián holttest volt, egy csomó tollal a fején. Ez a szörnyeteg morgott valamit, aztán elôvett egy hatalmas indiánbunkót és megtámadott!";
			link.l1.go = "Fleetwood_LastTask_4";
		break;
		
		case "Fleetwood_LastTask_4":
			dialog.text = "";
			link.l1 = "Te jó ég... Még mindig nem értem, hogyan tudtam elbánni azzal a valamivel... Annyiszor ütöttem meg, hogy egy tucat embert is meg tudtam volna ölni vele, és még mindig állt... Miután visszanyertem a lélegzetemet, kinyitottam azt a szerencsétlen ládát... Nem volt benne pénz, helyette volt benne valami. Nézd meg, egy nagyon érdekes tárgy!";
			link.l1.go = "Fleetwood_LastTask_5";
		break;
		
		case "Fleetwood_LastTask_5":
			RemoveItems(PChar, "GastonHead", 1);
			dialog.text = "B-r-r... szörnyû..." + pchar.name + ", várj... biztos, hogy ô az! Ez annak a szemétládának a feje, aki megpróbált megölni azzal, hogy paprikával vakított meg!";
			link.l1 = "Ismered ôt? A neve Gaston, Bridgetown csaposa és van Berg, a szellemhajó kapitányának támogatója. Azonnal felismertem, de nem tudom, ki ölte meg, és hogyan került a levágott feje a Salamon mellkasába az ismeretlen szigeten!";
			link.l1.go = "Fleetwood_LastTask_6";
		break;
		
		case "Fleetwood_LastTask_6":
			dialog.text = "Igazad van, ez egy igazán hátborzongató és homályos történet. Misztikus...";
			link.l1 = "Pontosan. A pénz hiánya miatt nem volt értelme visszatérni Abigailhez. Ezért vagyok itt, hogy elmeséljem neked. Talán te, Richard, megértesz valamit ebben a zûrzavarban...";
			link.l1.go = "Fleetwood_LastTask_7";
		break;
		
		case "Fleetwood_LastTask_7":
			dialog.text = "Én? Én semmit nem kapok itt, mint te... De valamit biztosra mondhatok - rossz érzésem van..." + pchar.name + ", most figyelj rám. Menj és nézd meg Bridgetownt, hogy biztos legyél benne, hogy... Gaston végleg eltûnt. Aztán megkérlek, hogy 20 nap múlva gyere el a Curacao Blanca Lagúnába. Charlie Knippel ott fog várni rád. Pénzt fogok gyûjteni Abigail apjának. Átadom Charlie-nak, te pedig elviszed Salamonhoz, és elviszed Abigailt Antiguára. Ezúttal nem lesz semmi akadály, ezt meg kell értened. Menj, barátom!";
			link.l1 = "Rendben, Richard. Azonnal vitorlát bontok.";
			link.l1.go = "Fleetwood_LastTask_8";
		break;
		
		case "Fleetwood_LastTask_8":
			DialogExit();
			pchar.questTemp.HWIC.Eng = "toBarbados";
			AddQuestRecord("Holl_Gambit", "2-21");
			SetFunctionTimerCondition("HWICEng_toBarbadosOver", 0, 0, 20, false);//чтобы не тянули
			AddSimpleRumourCity("Ó, kapitány, hallottam, hogy Richard Fleetwood nagyon csodálja önt. Higgye el, a dicsérete sokba kerül. Ön bizonyára nagyon fontos ember...", "SentJons", 20, 3, "");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
		break;
		
//---------------------------------------------против всех-----------------------------------------------
		
		case "InTerksShore":
			DelLandQuestMark(npchar);
			pchar.quest.Fleetwood_ShoreOver.over = "yes";//снять таймер
			dialog.text = "Gondolom, maga az a fattyú, aki elrabolta az én Abigailomat. Charlie nem tért vissza hozzám, tehát szintén téged kell hibáztatni.";
			link.l1 = "Igaza van, Mr. Fleetwood. Én vagyok az. Charlie segített nekem Abigail bizalmába férkôzni, hála a levélnek, amit ön írt neki. De térjünk rögtön a tárgyra... Elhozta a pénzt?";
			link.l1.go = "InTerksShore_1";
		break;
		
		case "InTerksShore_1":
			dialog.text = "Igen, elhoztam. De elôbb látni akarom Abigailt. Biztosnak kell lennem abban, hogy életben van és érintetlen, hiszen nem fogok megbízni egy fattyú szavában.";
			link.l1 = "Nem gondolja, uram, hogy nincs abban a helyzetben, hogy feltételeket diktáljon?";
			link.l1.go = "InTerksShore_2";
			// belamour legendary edition -->
			link.l2 = "Nem akarom tovább játszani ezt a játékot. Abi velem marad, te pedig itt maradsz a parton! Tûz!";
			link.l2.go = "InTerksShore_2a";
		break;

		case "InTerksShore_2a"://массовая драка на необитаемом острове
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;

		case "InTerksShore_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Ezt megértem, de én sem vagyok bolond. Nem beszélünk a pénzrôl, amíg nem látom Abigailt. És akkor mi van? Várok.";
			link.l1 = "Várjatok. Itt az ideje, hogy kiterítsem a kártyáimat, Fleetwood kapitány. Nem a pénz miatt szerveztem ide a találkozónkat. Nos, persze, szívesen elfogadnám, de elôbb szükségem van magára.";
			link.l1.go = "InTerksShore_3";
		break;
		
		case "InTerksShore_3":
			dialog.text = "Én? Ez kezd nagyon érdekes lenni... Azt hiszem, kezdem megérteni, hogy mi folyik itt valójában. Mondd, Abigail életben van? Él, vagy megölted, te szemétláda?";
			link.l1 = "Gondolom, nem tudsz semmit a sorsáról. Csak egy dolgot kell tudnod - ô nincs itt. Jól játszotta a szerepét, te itt vagy a kezemben. A szerelem olyan csodálatos dolog... Hogy máshogy tudnék egy rókát elôcsalogatni az odújából a nyílt terepre? Ha-ha-ha-ha!";
			link.l1.go = "InTerksShore_4";
		break;
		
		case "InTerksShore_4":
			dialog.text = "Ne örülj ilyen hamar, gazember! Szép üdvözletet szerveztem neked ezen a szigeten, és nem tudni, ki kinek a kezében van! Úgyhogy készülj fel, sok mindent el kell mondanod nekem - Abigailrôl, Charlie-ról, megfizetsz azért, ha bántod ôket!";
			link.l1 = "Már most reszketek a félelemtôl! Ideje befejezni a beszélgetésünket, uram. Készüljön fel, hogy a pokolba megy, mert az égben nincs helye magának.";
			link.l1.go = "InTerksShore_5";
		break;
		
		case "InTerksShore_5"://массовая драка на необитаемом острове
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
