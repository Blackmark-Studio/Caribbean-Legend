// Ян Свенсон - пиратский барон Западного Мэйна
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson")) {
				if (pchar.questTemp.HelenDrinking.Result == "won") {
					dialog.text = "Á, Charles. Köszönöm, hogy eljöttél. Csak meg akartam köszönni, hogy idôt töltöttél Helennel. A lánynak szüksége volt arra, hogy begyógyuljanak a sebei, és hallottam, hogy te is jól érezted magad, ha-ha! A fenébe, még irigy is vagyok!";
					link.l1 = "Nem vagy mérges? A hordó miatt és... minden más miatt?";
					link.l1.go = "after_drinking";
				} else {
					dialog.text = "Á, Charles. Köszönöm, hogy eljöttél. Csak meg akartam köszönni, hogy idôt töltöttél Helennel. A lánynak szüksége volt a sebei gyógyítására, és hallottam, hogy te is jól érezted magad, ha-ha! Sok szerencsét Cartagenában!";
					link.l1 = "Igen, én is örülök, hogy minden jól ment tegnap. A viszontlátásig, Jan.";
					link.l1.go = "exit";
				}
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson");
				break;
			}
		
			if(CheckAttribute(pchar, "questTemp.Saga"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga_Late")) // отсекание при провале по времени
				{
					dialog.text = "Ó, barátom "+pchar.name+"! Öröm volt látni téged! Mit tehetek érted?";
					link.l1 = "Csak beugrottam megnézni, hogy vagy.";
					link.l1.go = "exit";
					if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
					{
						if (GetDataDay() == 14 || GetDataDay() == 28)
						{
							link.l2 = "Jan, szeretnék vasfát vásárolni.";
							link.l2.go = "trade_bakaut";
						}
					}
					break;
				}
				if(pchar.questTemp.Saga == "svenson")
				{
					dialog.text = "Miben segíthetek, uram?";
					link.l1 = "A segítségét szeretném kérni, Erdei Ördög.";
					link.l1.go = "saga";
					break;
				}
				if(pchar.questTemp.Saga == "svenson1")
				{
					dialog.text = "Aha, barátom "+pchar.name+"! Mi a hír?";
					link.l1 = "Sikerült sok érdekes dolgot megtudnom Hangman-tól.";
					link.l1.go = "saga_11";
					break;
				}
				if(pchar.questTemp.Saga == "svenson2")
				{
					dialog.text = "Szóval, "+pchar.name+", beszéltél Gladysszel?";
					link.l1 = "Igen. Jan, nézz ide... Tudsz mondani valamit errôl a pergamenfoltról?";
					link.l1.go = "saga_17";
					break;
				}
				if(pchar.questTemp.Saga == "helena1" || pchar.questTemp.Saga == "helena2" || pchar.questTemp.Saga == "svenson_wait")
				{
					dialog.text = "Egyelôre semmi újat nem tudok mondani, "+pchar.name+". De dolgozom egy megoldáson az ügyünkre. Gyere vissza késôbb.";
					link.l1 = "Rendben, Jan. Késôbb találkozunk.";
					link.l1.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests") // старт трех квестов баронов
				{
					// первая проверка времени. Свенсон очень недоволен растяпством ГГ. Счищаем Элен, к Свенсону доступ закроем
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = ""+pchar.name+", nagyot csalódtam benned. Azt vártam, hogy komoly ember leszel, de mint kiderült, csak egy buta fiú vagy. Hol voltál egész idô alatt, huh? Az angolok elfoglalták Isla Tesorót, amíg te isten tudja, mit csináltál!\nMinden tervemnek annyi! Hogy ôszinte legyek, már majdnem elfelejtettem a létezésedet, és nem akarom, hogy emlékezzenek rá. Tûnjetek el!";
						link.l1 = "Ezt nem hiszem el!";
						link.l1.go = "saga_l1";
					}
					else
					{
						dialog.text = "Tessék, "+pchar.name+". Kicsit átrágtam magam a helyzetünkön. Nem feltétlenül nevezném tervnek, de...";
						link.l1 = "Csupa fül vagyok, Jan.";
						link.l1.go = "saga_25";
					}
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests_1") // идут три квеста баронов
				{
					dialog.text = "Hogy haladnak a dolgok? Van valami, amiben segíthetek?";
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "after_marlow")
					{
						link.l3 = "Beszéltem a fekete lelkésszel. Sajnos a beszélgetésünk eredménye miatt visszatértem hozzád tanácsért, nem tudok mit kezdeni vele.";
						link.l3.go = "shark_hunt_2";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "LSC" && !CheckAttribute(pchar, "questTemp.Saga.BaronReturn"))
					{
						link.l3 = "Megtaláltam Diost, és kellemesen elbeszélgettünk. Sok érdekes dolgot mondott, de sajnos nem jutottunk el a lényegre.";
						link.l3.go = "shark_hunt_7";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "third_teleport")
					{
						link.l3 = "Ó, Jan, annyi mindent kell elmondanom, hogy egész éjjel tartana, hogy mindent átadjak neked, úgyhogy rövid leszek.";
						link.l3.go = "return_LSC";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "shamane" && !CheckAttribute(npchar, "quest.shamane"))
					{
						link.l3 = "Elhoztam Nathaniel Hawkot a Justice Islandrôl. Most is a hajómon van.";
						link.l3.go = "nathaniel";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "treatment")
					{
						link.l3 = "Letettem Nathaniel Hawkot a miskitó faluban, hogy egy Kígyószem nevû sámán kezelje. Megígérte, hogy helyreállítja Nathan egészségét.";
						link.l3.go = "nathaniel_2";
					}
					link.l4 = "Jelenleg nincs sok mondanivalóm. Csak beugrottam megnézni, hogy vagy.";
					link.l4.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "fail_centurion") // провал - потоплен Центурион
				{
					dialog.text = "Mi a hír, "+pchar.name+"? Hogy mennek a dolgok?";
					link.l1 = "Ó, rosszabb már nem is lehetne. Annyi munkát végeztem... Lenyomoztam Jackmant, eldobtuk a hüvelyeket, és megfojtottam, mint a legnagyobb idiótát, mindennel együtt, ami a kunyhójában lehetett. Most nincs semmi, ami segíthetne levenni a bûzt Shark nevérôl, és Barbazonra terelni a szót. Attól tartok, ez egy vesztes ügy, Jan.";
					link.l1.go = "saga_f_1";
					break;
				}
				if(pchar.questTemp.Saga == "calendar") // квесты баронов завершены
				{
					// вторая проверка времени. Отбираем Элен, со Свенсоном нейтральные отношения - ну не выщло и не вышло, хоть попытались. Данни и Натана - в Марун-Таун
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = "Hallottam a hôstetteidrôl! Dannie elmondta a rövid változatot. Egyébként most már barátok vagyunk. És Nathan teljesen megváltozott! Minden depressziója elszállt, amikor meglátta a 'Centurion'.\nDe rossz hírem van számodra, "+pchar.name+". Annyi idôt vesztegettünk el, hogy Sharp végrendeletének öröklési jogai már régen eltûntek, és Isla Tesoro egy angol katonai bázissá vált. Már semmit sem tehetek, hogy segítsek neked Levasseurrel."
						link.l1 = "Teljesen szótlan vagyok... Annyi bajon mentünk keresztül a semmiért. Tényleg nem tehetünk semmit?";
						link.l1.go = "saga_l2";
					}
					else
					{
						dialog.text = "Hallottam a hôstetteidrôl! Dannie tájékoztatott. Egyébként kibékültünk. Még Nathant sem ismered fel. Amint meglátta a 'Centurion', , úgy hagyta maga mögött a morgását, mint egy rossz álmot...";
						link.l1 = "Nathan megint jól van? Örömmel hallom!";
						link.l1.go = "saga_26";
					}
					break;
				}
				if(pchar.questTemp.Saga == "mine") // рудник взят
				{
					dialog.text = "Tessék, "+pchar.name+"! Most valamit el kell mondanom neked.";
					link.l1 = "Szia, Jan, nagyon örülök! Hogy is van ez a szó? Remélem, valami pozitív?";
					link.l1.go = "saga_32";
					break;
				}
				if(pchar.questTemp.Saga == "mine_1") // рудник взят совместно
				{
					dialog.text = "Tessék, "+pchar.name+"! Pihentél egy kicsit? És megállapíthatom, hogy ismét készen állsz a nagy kalandokra?";
					link.l1 = "Helló, Jan. Igen, készen állok.";
					link.l1.go = "saga_32a";
					break;
				}
				if(pchar.questTemp.Saga == "late_l3") // провал по времени у адвоката
				{
					dialog.text = "Mi a hír, "+pchar.name+"? Hogy mennek a dolgok?";
					link.l1 = "Igen, készen állok. A dolgok teljesen szörnyûek.  Foggal-körömmel küzdöttem, de végül mégis vesztésre álltam. Mint emlékszel, Sharp végrendelete idôhöz volt kötve. Nos, ez az idô lejárt, és Isla Tesoro most egy angol katonai bázis. Ez egy vesztes ügy, Jan.";
					link.l1.go = "saga_l3";
					break;
				}
				if(pchar.questTemp.Saga == "bakaut") // пришёл от адвоката за деньгами
				{
					dialog.text = "Üdvözlet, "+pchar.name+"! Jó hír: a Tanács ülése megtörtént, és a Partiumi Testvérek új vezetôt találtak.";
					link.l1 = "Jó napot, Jan. Örülök magának.";
					link.l1.go = "saga_44";
					break;
				}
				if(pchar.questTemp.Saga == "sellbakaut" && GetSquadronGoods(pchar, GOOD_SANDAL) >= 1) // отдает бакаут
				{
					dialog.text = "Nos, "+pchar.name+"? Utolérted Molligan-t?";
					link.l1 = "Igen. Ô volt az, aki ellopta a vasfádat.";
					link.l1.go = "saga_55";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut") && GetNpcQuestPastDayParam(npchar, "bakaut_date") >= 1) // за деньгами за бакаут
				{
					dialog.text = "Idôben, mint mindig, "+pchar.name+". Eladtam a vasfát, amit hoztál nekem.";
					link.l1 = "Kitûnô. Mennyi pénzt kerestél?";
					link.l1.go = "saga_57";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut_sum")) // сам продал бакаут
				{
					dialog.text = "Nos, "+pchar.name+"? Utolérted Molligan-t?";
					link.l1 = "Igen. Ô volt az, aki ellopta a vasfádat. Véletlenül ráakadtam a vevôjére is. Valami holland katonai parancsnok volt. Neki adtam el a terméket.";
					link.l1.go = "saga_59";
					link.l2 = "Én adtam el. Megpróbáltam rávenni, hogy mutassa meg a rakterét... csetepatéba keveredtünk, és... most már nincs többé Molligan. De a raktérben nincs semmi, amit láthatna, kivéve az ébenfát és a mahagónit.";
					link.l2.go = "saga_59_1";
					break;
				}
				if(CheckAttribute(npchar, "quest.jessika")) // информация о Джессике
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Mi újság?";
					link.l1 = "Jan, egy dologról szeretnék beszélni veled. Helen anyjának, Beatrice-nak a múltjában kutakodtam, és véletlenül belebotlottam valakibe, akit jól ismersz. Amennyire én tudom...";
					link.l1.go = "saga_62";
					break;
				}
				if(pchar.questTemp.Saga == "lastpages") 
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Hogy haladnak a dolgok? Az arcodból ítélve gratulálhatok? ";
					link.l1 = "Igen. Végre sikerült elrendeznem ezt a zûrzavart. Helen megkapta az Isla Tesoro összes jogát. Soha többé senki nem fog a Parti Testvérek menedékébe behatolni!";
					link.l1.go = "saga_82";
					break;
				}
				if (pchar.questTemp.Saga == "vége") sTemp = "Ó, barátom "+pchar.name+"! Örülök, hogy látlak! Mi szél hozott ide?";
				else sTemp = "Még valami, "+pchar.name+"?";
				dialog.text = sTemp;
				link.l1 = "Nem, Jan. Egyelôre semmi.";
				link.l1.go = "exit";
				if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
				{
					if (GetDataDay() == 14 || GetDataDay() == 28)
					{
						link.l2 = "Jan, szeretnék vásárolni a vasfádból.";
						link.l2.go = "trade_bakaut";
					}
				}
				NextDiag.TempNode = "First time";
			}
			else
			{
				// заглушка Элен
				if(startHeroType == 4)
				{
					dialog.text = "Helen, helló, kedvesem. Milyen híreid vannak? Akartál valamit?";
					link.l1 = "Helló, Jan! Mindegy, csak beugrottam, hogy lássalak.";
					link.l1.go = "exit";
					NextDiag.TempNode = "First time";
					break;
				}
				dialog.text = "Segíthetek valamiben?";
				link.l1 = "Nem, jól vagyok.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First time";
			}
		break;
		
		case "saga":
			dialog.text = "Ismerlek, az istenit! Te vagy az a bátor kapitány, aki megmentette a Rumbát, és fejjel ment az angol korvett ágyúi ellen! Micsoda öröm látni téged! Helen olyan nekem, mintha a lányom lenne. A mai naptól kezdve örökre lekötelezettje leszek. Hívhatsz csak Jan-nak vagy Svensonnak, ha akarsz. Mit tehetek önért?";
			link.l1 = "Ki kell iktatnom Levasseur-t, Tortuga kormányzóját. Tudom, hogy nem lesz könnyû feladat eljutni hozzá a szigetén, ezért fordultam önhöz tanácsért.";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "Te jó ég, hol voltál pár évvel ezelôtt! Én is ugyanezt a szökést terveztem. Az egész játékot elrontotta nekünk a franciákkal. De akkoriban minden más volt. Blaze élt, Sharknak volt némi tekintélye, és Nathan volt a fônök Maroon Townban... Most minden megváltozott, és Isten tudja, nem a jobbik irányba. Tudsz valamit rólunk, a Testvérekrôl?";
			link.l1 = "Nemrég érkeztem ide, szóval gyakorlatilag semmit sem tudok. Azon kívül, hogy te és Jackman a Tanács tagjai vagytok.";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			dialog.text = "Ki nem állhatom ezt a Jackmant! Amikor idejött, akkor kezdôdött minden bajunk. Megfontolom a kérését. Rögtön az elején semmi sem jut eszembe.";
			link.l1 = "Van valami érdekes Jackmannel kapcsolatban.";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			dialog.text = "Hm. Az meg mi?";
			link.l1 = "Jackman Gladys Chandlert és a lányát keresi. Miután beszéltem Higgins-szel, arra gondoltam, hogy Rumbát keresi. Úgy tûnik, hogy Gladys nem Helen biológiai anyja, és a vezetékneve Chandler volt, mielôtt hozzáment Sean McArthurhoz.";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			dialog.text = "Az istenit! Ez rossz hír. Jackman most erôsebb, mint valaha. Ráadásul van egy rossz érzésem, hogy nem egyedül dolgozik. Elég vészjósló árnyék van a háta mögött. Ha tényleg szüksége van Helenre, akkor a lánynak nagy szüksége van egy védelmezôre. Attól tartok, én magam már túl öreg vagyok ehhez...";
			link.l1 = "Ez még nem minden. Jackman keres egy Henry the Hangman nevû embert is, aki aNeptune hajón volt hajóskapitány, a 'Neptune', Butcher kapitány legénységébôl.";
			link.l1.go = "saga_5";
		break;
		
		case "saga_5":
			dialog.text = "Caramba! Legrosszabb sejtéseim valóra váltak! Ez a Mészáros és az ô 'Neptunszokta rettegésben tartani az egész szigetvilágot. Akkoriban még nem voltak Testvérek, mindenki magára volt utalva. Az az ember sok rossz dolgot tett, egy számomra kedves ember meghalt miatta.\nNem volt alkalmam találkozni vele. A 'Neptune' egy angol fregatt elsüllyesztette, Butchert pedig St. John' s-ban kivégezték. Jó, hogy megszabadultunk tôle! Bár sokan voltak, akik csodálták szerencséjét és vakmerô bátorságát.\nJackman maga volt a jobb keze és elsô tisztje a 'Neptune'. meglepôdött? A volt bûnözôk a nemzet hôsei lettek, mindezt Cromwellnek köszönhetôen! Hová tûnt a jó öreg Anglia?\nMeg kell találnunk Henriket, a hóhért, mielôtt Jackman emberei megteszik. Talán nála van a rejtély kulcsa, ha még életben van.";
			link.l1 = "Lefogadom, hogy könnyebben megtalálnád a tût a szénakazalban. Legalább van valami nyom?";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Ismertem Henry-t, amikor még gyerek volt. Egy cartagenai kurva fia, félig spanyol, bár ezt mindig titokban tartotta. Az anyja dögös volt! Nem mondhatnám, hogy csinos volt, de nagyon kevés olyan flamenco táncos volt, mint ô. Az egész bordélyház nézte a meztelen Chica Gonzales és a kasztanyettái bemutatóit.\nSzerencsétlen lány. Elkapott egy csúnya betegséget és meghalt, mint egy gyertya. Ekkor rábeszéltem Henryt, hogy menjen Providence-be, ahol gyorsan hírnevet szerzett magának, és csatlakozott Thomas Beltrope, Nicolas Sharp közeli barátjának legénységéhez. Ôk ketten voltak Erzsébet királynô utolsó kutyái, és mindig együtt dolgoztak. Jó idôk voltak!\nThomas visszahajózott Angliába, amikor a társa meghalt. Magával vitte a legénységét, de Henry a Karib-tengeren maradt. Különbözô kapitányok alatt hajózott, amíg Butcher fel nem bukkant. A becenevét egyébként egy bicska miatt kapta, amit mindig magánál tartott.";
			link.l1 = "És mit árul el nekünk ez az információ?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Ha Akasztó úgy döntött, hogy elrejtôzik a kalózok elôl, a legjobb hely számára egy spanyol város lenne. Különösen otthonában, Cartagenában, ahol vannak barátai és rokonai. Henry meglehetôsen vallásos volt. Így nem valószínû, hogy más szentek templomába járna. Valószínûleg még mindig ugyanaz a neve, amit gyerekkora óta visel, Enrique.";
			link.l1 = "Igen... Kevés a nyeremény, de legalább jobb, mint a semmi.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Próbáld megkeresni, Charles! Kevesen tudnak Henry spanyol gyökereirôl, így van egy kis elônyünk. Gondolkodom, hogyan gyôzzem meg Rumbát, hogy csatlakozzon a csapatodhoz. A lány tökös, soha senki más parancsnoksága alatt nem szolgált, csak az apja parancsnoksága alatt.\nDe nincs se hajója, se legénysége, és meg kell élnie. Persze, továbbra is segítek Gladysnek, ahogy mindig is tettem, de Helent nem sokáig tudom Blueweldben tartani. És egy ilyen tisztet nagyon hasznosnak fogsz találni. Sean mindent megtanított neki, amit tudott, és úgy nevelte, mint egy fiút.\nMég jobban érezném magam, ha egy olyan kapitány parancsnoksága alatt állna, mint te.";
			link.l1 = "Rumba eléggé méltónak bizonyult rá. Több ilyen emberre van szükségem a legénységemben. Szóval, ha sikerül rábeszélned, akkor tisztet csinálok belôle. De elôbb meg akarom érteni, hogy ki is ô valójában, és miért van rá szüksége Jackmannek. Attól tartok, hogy Donovannal ellentétben ôt nem érdekli a bája. Ezért megpróbálom megtalálni Akasztófát, bár nem ígérhetek semmit.";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Nos, nagyszerû. Vegye el a Holland Nyugat-indiai Társaság engedélyét három hónapra. Írja oda a nevét, nagyon jól jöhet a keresések során. Addig is átgondolom, amit Levasseurrôl és Tortugáról mondott.";
			link.l1 = "Köszönöm szépen! Ez az írás még jól fog jönni nekem. Ebben az esetben, akkor megyek Cartagenába.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			DialogExit();
			GiveNationLicence(HOLLAND, 90);
			AddQuestRecord("Saga", "14");
			pchar.questTemp.Saga = "cartahena";//идем в Картахену
			pchar.quest.Saga_Gonsales.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales.win_condition.l1.location = "Cartahena_town";
			pchar.quest.Saga_Gonsales.function = "Saga_CreateGonsalesB";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			LocatorReloadEnterDisable("FortOrange_town", "reload6", true); // закрыть резиденцию Джекмана
			npchar.greeting = "svenson_3";
			
			AddQuestRecord("HelenDrinking", "1");
			pchar.questTemp.HelenDrinking.CanDrink = true;
			SetFunctionTimerConditionParam("HelenDrinking_NoVisit", 0, 0, 1, 24 - GetHour(), false);
			
			pchar.questTemp.Saga.HelenRelation = 0;
		break;
		
		case "saga_11":
			dialog.text = "Henry meghalt?  Várj, te ölted meg?";
			link.l1 = "Ne nézz rám ilyen nagy szemekkel! Semmi közöm hozzá. Saját magától halt meg, a rothadó lelkiismeretétôl és a Jackmantól való félelmétôl. Az öreg kalóznak gondjai voltak a szívével, és nem volt sok ideje hátra. A következôket sikerült kiderítenem...";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Kérlek, mondd el!";
			link.l1 = "Húsz évvel ezelôtt Henrynek egy láda aranyat kellett volna átadnia Mészáros kapitány nevében a biológiai lánya nevelôanyjának. Egyáltalán nem kétséges, hogy ez a nevelôanya Mrs. McArthur volt. Akkoriban a Chandler vezetéknevet viselte, és Belize-ben élt. A körülmények azonban még egy teljes hónapig feltartották Hangman-t St. John's-ban, és amikor végre megérkezett Belize-be, az a spanyolok által végrehajtott rajtaütés után romokban hevert, Gladys néni és Sean pedig már a szárnyai alatt vágott neki az útnak.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "";
			link.l1 = "Helent a biológiai lányuknak adták ki, és sajátjukként nevelték fel. Henry nyomukat vesztette, és meghúzta magát, mivel tisztában volt Jackman bosszújával, és az azóta eltelt húsz évet végig félelemben élte le. Kiderült, hogy Jackman a kapitány lányát keresi. De hogy miért, azt nem tudni.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "Talán valakinek a parancsát hajtja végre...";
			link.l1 = "Kétlem. Ki adhatna neki parancsot? Mészáros halott. A halálát hivatalos dokumentumok igazolják. Több tucat, ha nem több száz ember látta a halálát.";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "Talán nem is arról van szó, hogy ki Helen apja. Talán az egész a biológiai anyjáról szól. Már sejtem, hogy ki volt az, de nem merem bevallani. De Gladys! Hogy tudta ezt ennyi éven át titokban tartani anélkül, hogy még a férjének is elárulta volna! Sean McArthur biztosan elmondta volna nekem. Soha nem volt olyan titkunk, amit ne mondtunk volna el egymásnak.";
			link.l1 = "Megyek, és elbeszélgetek Gladysszel. Azt hiszem, megvan az eszközöm, hogy szóra bírjam. A következô alkalomig, Jan!";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			DialogExit();
			pchar.questTemp.Saga = "gladis1";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_history";
			AddQuestRecord("Saga", "21");
		break;
		
		case "saga_17":
			dialog.text = "Honnan szerezted ezt?";
			link.l1 = "Gladys adta nekem. Azt mondta, hogy Helen édesanyjának 'örökségét'. nem tudja a nevét. Valami azt súgja, hogy ez nem egy átlagos papírdarab.";
			link.l1.go = "saga_18";
		break;
		
		case "saga_18":
			dialog.text = "Emlékszel, amikor azt mondtam neked, hogy van egy sejtésem, hogy ki volt Helen igazi anyja? Most már biztos vagyok benne. A neve Beatrice Sharp volt. A tanárom és barátom, Nicholas Sharp biológiai lánya volt, a testvéreink alapítójának, Blaze Sharpnak a bejelentett nôvére, és az Isla Tesoro résztulajdonosa. Jackman ezt a térképdarabot keresi.";
			link.l1 = "Nos, mit szólsz ehhez! De miért lenne szüksége egy fél sziget térképére?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "A szigetet Nicolas Sharp fedezte fel. Ô nevezte el Isla Tesorónak, feltérképezte, és a Providence-szigeti Társaságon keresztül vette birtokba, ahol jó kapcsolatai voltak.\nNicolas azt írta tanúvallomásában, hogy a szigetet csak az örökölheti, aki a térkép két részét elôállítja. Azért tette ezt, hogy elkerülje a viszályokat. A részeket Beatricének és mostohafiának, Blaze-nek adta át, mielôtt tragikus módon spanyol kéz által meghalt.";
			link.l1 = "Hát a fene egye meg! Milyen furcsa.";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "Igazad van. Nem volt a legjobb ötlet. Egy ravasz közjegyzô pedig hozzátette, hogy a sziget az angol koronára száll, ha az örökösök halálát követô egy éven belül senki nem állítja elô a térkép mindkét részét.\nSenki sem látta elôre akkoriban. És most megfizetjük az árát a hülyeségünknek. Beatrice húsz éve halt meg. Ennyi év eltelt, és még mindig nincs fogalmunk arról, hogy hol van a sírja a térkép egy részével együtt. Blaze Sharpot nemrég meggyilkolták. Az ô része is eltûnt.\nHa egy éven belül senki sem mutatja be a hatóságoknak Isla Tesoro teljes térképét, akkor Sharptownt Anglia követeli magának. Kormányzót küldenek oda egy helyôrséggel, és a Brethren-nek vége.";
			link.l1 = "Mit javasolsz, mit tegyünk?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "Nem hagyhatjuk, hogy ez megtörténjen. Szükségem van rád, Charles, szükségem van rád, hogy megakadályozd ezt az akciót. És csak azután tudok majd segíteni Levasseur likvidálásában, miután átvettük az irányítást Isla Tesoro felett, és Shark Dodsont választottuk meg a Testvériség új vezetôjének. Ô a legméltóbb közülünk. Szövetséget ajánlok nektek.\nApropó, beszéltem Helennel. Beleegyezett, hogy csatlakozik a csapatodhoz.";
			link.l1 = "Nem hagysz más választást, Jan. Nem térhetek vissza Franciaországba anélkül, hogy ne állítanám helyre a családom becsületét. És ehhez ki kell iktatnom Levasseur-t a segítségeddel vagy nélküled. Felesleges haláleseteket nem akarok, és remélem, hogy ki tudod találni, hogyan vegyük be Tortugát anélkül, hogy túl sok vért ontanánk. Bár be kell vallanom, hogy én magam is szeretném megfejteni a Sharps' örökséget övezô ködös múltat.";
			link.l1.go = "saga_22";
		break;
		
		case "saga_22":
			dialog.text = "Jó hallani hangzatos gondolatokat! Majd kitaláljuk a helyes utat Tortuga elfoglalására. Ezt megígérem neked. Szóval, menjünk?";
			link.l1 = "Gyerünk! Késôbb még beugrom. Egyelôre gondolkodjatok el azon, hogy hol kezdjetek hozzá a probléma kezeléséhez.";
			link.l1.go = "saga_23";
		break;
		
		case "saga_23":
			dialog.text = "Két-három nap múlva nézz be újra. Addigra szerintem a tervem beteljesedik. És ne felejtsd el Helent is magaddal vinni a hajódra. Szegény lány a tenger nélkül csak úgy sanyargatja magát. Hûséges asszisztens lesz, és nem kell majd kétszer meggondolnod, hogy számíthatsz-e rá.";
			link.l1 = "Rendben, Jan. Azonnal megyek érte.";
			link.l1.go = "saga_24";
		break;
		
		case "saga_24":
			DialogExit();
			pchar.questTemp.Saga = "helena1";
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);//закрыть выходы из города
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			AddQuestRecord("Saga", "23");
		break;
		
		case "saga_25":
			dialog.text = "Elôször is meg kell találnod a Cápát. Ô maga akart megszabadulni Levasseurtôl, és biztosíthatom, hogy van néhány ragyogó ötlete. Természetesen Marcust is rá tudjuk venni, hogy fogadja el a vezetést. Elvégre ô a kódex ôrzôje. De kétlem, hogy bármiben is segítene, szándékosan korlátozta a Levasseurrel és Tortugával való kapcsolattartást. A princípiumok embere.\nGôzöm sincs, hol rejtôzik Steven és az emberei, de a fregattját 'Fortune' Puerto Principe-nél látták. Talán Zachary Marlow, más néven a Fekete Pásztor el tudja nekünk mutatni, hol keressük a Cápát. Másodszor, meg kell nyernünk a többi báró támogatását, hogy megválasszuk Dodsont. Ehhez pedig össze kell gyûjtenünk az indiánszilánkjaikat - a szavazatokat. Az új vezetônek mind az ötöt meg kell szereznie. Ezt írja elô a Kódex abban az esetben, ha az elôzô vezetô meghalt.\nRöhelyes! Ideje lenne megváltoztatni a törvényeket, de ezt csak az új vezetô teheti meg. Az én szavazatom már megvan. Szerintem a fekete lelkésznek teljesen mindegy, hogy kinek a seggét ültetik el Sharptownban. Remélem, hogy Jackman nem vele beszélt elôször. Meg kell gyôznünk Tyrexet és Jacques Barbazont is, akik gyûlölik egymást. De ez mind lényegtelen, amíg nem tudjuk meg, mi történt a Cápával. Harmadszor, egy napon meg kell ölnünk Jackmant, és le kell cserélnünk valaki másra. Nem fog velünk tárgyalni.\nKár, hogy Sólyom meghalt! Az emberek bíztak benne, és hasznát vehettük volna a szavának. Nem fogunk jobb bárót találni Maroon Town számára. Lehetséges, hogy Jackmannek köze van Blaze meggyilkolásához, így ô a térkép második részének megtalálásához vezetô nyom is. Jacob senkiben sem bízik, és valószínûleg a térkép részét a 'Centurion'.\nHawk családja birtokolta a fregattot, de Jackman igényt tartott rá, akárcsak Hawk báróságára. Ha megtaláljuk a térkép második részét Jackman birtokában, az remek érv lenne Steven megválasztása mellett. Különösen Marcus Tyrex, a kódex ôrzôje és a becsület tekintetében túlzottan lelkiismeretes viselkedése miatt. Amint megszerezzük a térkép mindkét részét, visszamegyünk Helénához, és visszaadjuk neki az Isla Tesoro feletti jogait.\nVigyáznunk kell azonban, Jackman nem fog tétlenül nézni, ahogy keresgélünk.";
			link.l1 = "Nos... Én most meglátogatom a Fekete Pásztort. Mesélj róla.";
			link.l1.go = "shark_hunt";
			pchar.questTemp.Saga = "baronsquests_1";
		break;
		
		case "shark_hunt":
			dialog.text = "A pokolba is, ha tudom, mi jár a fejében. Néha úgy néz ki, mint egy totális csodabogár, de ettôl függetlenül szerintem ez csak okos színészi játék. Emellett az emberei készek magával az ördöggel is megküzdeni szeretett lelkipásztoruk tiszteletére.\nA spanyol inkvizícióhoz közel álló valamiféle protestáns szektát alapítottak Kubában. Szóval teológiai kérdésekrôl ott ne is kezdj el beszélni, nem fogják jóváhagyni.";
			link.l1 = "Ezt majd figyelembe veszem...";
			link.l1.go = "shark_hunt_0";
		break;
		
		case "shark_hunt_0":
			dialog.text = "És "+pchar.name+": egy percet se vesztegessen az idejébôl. Komolyan mondom. Ugye emlékszel a végrendeletben lévô aláírásról, amely szerint, ha az örökösök egy éven belül nem tartanak igényt a szigetre, akkor Isla Tesoro az angol koronára száll, ugye? Nos, az idô most nem a mi oldalunkon áll. Amikor legutóbb találkoztunk, már csak körülbelül tizenegy hónap volt hátra az idô lejártáig.";
			link.l1 = "Emlékszem, Jan. Igazad van, az idô pénz. Rajta vagyok!";
			link.l1.go = "shark_hunt_1";
		break;
		
		case "shark_hunt_1":
			DialogExit();
			AddQuestRecord("SharkHunt", "1");
			pchar.questTemp.Saga.SharkHunt = "begin";
			pchar.GenQuest.LigaAttack = "true"; // киллеры Лиги активированы
		break;
		
		case "shark_hunt_2":
			dialog.text = "Hm... Mit mondott neked Zachary?";
			link.l1 = "Az eltûnése elôtt Shark meglátogatta ôt, és Zacharyval együtt otthagyta a fregattját, mint biztosítékot egy briggért némi élelemmel, majd elhajózott valahol északnyugatra, Kubába.";
			link.l1.go = "shark_hunt_3";
		break;
		
		case "shark_hunt_3":
			dialog.text = "Ez tényleg gyanús. Folytassa.";
			link.l1 = "Egy hónappal késôbb Dodson nem tért vissza, és a pásztor a megállapodás értelmében magához vette a fregattot, és jó áron eladta valami Paterson nevû fickónak. Ami a mi ügyeinket illeti, Zachary megemlítette, hogy a Shark talán valami legendás Justice-szigetre indult, amely állítólag valahol nem messze, Kubától északnyugatra található.";
			link.l1.go = "shark_hunt_4";
		break;
		
		case "shark_hunt_4":
			dialog.text = "Hallottam már az Igazság Szigetérôl. Azt mondják, hogy van egy sziget, ahol fehérek és feketék békésen, egyenrangúként élnek együtt. Mindenféle álmodozók által terjesztett baromság. De fennáll a lehetôsége, hogy északnyugaton valamiféle csempészbázis létezik. Tíz évvel ezelôtt rendszeresen látták a bárkáikat a nyílt tengeren. Különféle árukat hoztak Kubába, élelemért cserébe.";
			link.l1 = "Kincsek élelemért? A lelkész mesélt nekem a marhahús-szállító kalózokról is. Eléggé két lábon járó ellentmondás.";
			link.l1.go = "shark_hunt_5";
		break;
		
		case "shark_hunt_5":
			dialog.text = "Ezeknek a pletykáknak biztos van forrása, azok a csempészek' vagy kalózok' bárkák valamiért arrafelé hajóznak. Emlékszem, a Cápa mesélt nekem a fiatalkoráról, valamiféle rabszolga volt valami furcsa, hajóroncsokból álló képzôdménynél a tenger közepén.\nTán az a mi helyünk? Fogalmam sincs. Mindenesetre a pásztornak igaza van, valami van odakint, vagy egy titkos bázis, vagy egy sziget, ahová Shark mehetett. Figyelj, hajózz el Santo Domingóba, és keress meg egy Jose Dios nevû tudóst.\nÔ egy spanyol térképész. Egyszer megmentettem ôt a mocskos söpredéktôl, tisztelem a mûvelt embereket. Segíteni fog neked, csak mondd meg neki a nevem. Menj Hispaniolára, keresd meg Diost, és beszélj vele.\nTökéletesen ismeri a vidékünk földrajzát, és ha ô nem tud segíteni neked - senki sem fog.";
			link.l1 = "Rendben, Jan. Jól hangzik a terv. Indulok!";
			link.l1.go = "shark_hunt_6";
		break;
		
		case "shark_hunt_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "dios";
			AddQuestRecord("SharkHunt", "3");
		break;
		
		case "shark_hunt_7":
			dialog.text = "Kár érte. Reméltem, hogy Jose segít nekünk.";
			link.l1 = "Én is számítottam rá, de sajnos... Nos, ne bízzuk el magunkat a szánalomban. Még eltöltök egy kis idôt, hogy átgondoljam ezt a dolgot. Igen, Jan, mondd csak, hogyan halt meg Hawk?";
			link.l1.go = "baron_return";
		break;
		
		case "baron_return":
			dialog.text = "Senki sem volt szemtanúja a halálának, ahogy a holttestét sem látta senki. Egyszerûen eltûnt néhány hónappal ezelôtt. Azóta ugyanolyan, mint Cápa esetében, se bôre, se szôre. De Steven-nel ellentétben Nathan-nek nem volt oka arra, hogy elrejtôzzön. Éppen ezért mindenki úgy gondolta, hogy a szelavában hunyt el. Ha nem ezért lett volna, akkor nem egyeztek volna bele, hogy Jackmant válasszák meg helyette.";
			link.l1 = "Mi a fenét keresett Sólyom a selva-ban?";
			link.l1.go = "baron_return_1";
		break;
		
		case "baron_return_1":
			dialog.text = "Az én hibám volt, egy vén bolond vagyok! Én beszéltem rá, hogy vigyázzon az újonnan érkezett banditákra. Fogalmam sincs, kik ôk, és ki a fônökük. Normális esetben nem érdekelne, de elkezdtek barátságos miskitókat elrabolni. A hadvezérük, Kumvana azzal fenyegetôzött, hogy meghirdeti a Hadiösvényt, és a segítségemet kérte. Nem volt más választásom, mint hogy közbelépjek.\nHawk egy kis egységgel leszállt a Mosquito Coaston, csapdába esett egy kiválóan megszervezett rajtaütés során, majd legyôzték. Úgy nézett ki, hogy ôt és az embereit ott várták partra. Hawk holttestét nem találták meg a többiek között a dzsungelben.";
			link.l1 = "Az orrod elôtt mindenféle cselvetés történt! Sólyom emberei közül senki sem próbált meg elbánni a banditákkal?";
			link.l1.go = "baron_return_2";
		break;
		
		case "baron_return_2":
			dialog.text = "Jackman mindenkit megelôzött. Ô maga hívta ki magát, hogy megoldja a kérdést a Testvérek Tanácsában, és meghozta a döntést. Miskitók már nem tûntek el, de a banditák ott maradtak, és viszonylag meghúzták magukat.\nJackman azt mondta, hogy nem tartanak túszként senkit azok közül, akik támadásra jöttek, és nincs okuk arra, hogy a Testvériség hadat üzenjen nekik. Hawk támadta meg ôket elôször, így a törvényeink szerint a banditáknak joguk volt megvédeni magukat. Mindenki egyetértett ezzel. Mindenki, kivéve...";
			link.l1 = "Mindenki, de ki?";
			link.l1.go = "baron_return_3";
		break;
		
		case "baron_return_3":
			dialog.text = "Nathannek volt egy felesége. A neve Danielle Hawk, és ô egy kemény szuka! Kétlem, hogy valaha is túltette volna magát a kapitánya elvesztésén, nem is beszélve arról, hogy már a kezdetektôl fogva gyanakodott valamire, és megpróbálta lebeszélni Hawkot. Emlékszem, hogy volt egy hatalmas vitájuk emiatt, de ez nem volt szokatlan tôlük.";
			link.l1 = "És hol van most Danielle?";
			link.l1.go = "baron_return_4";
		break;
		
		case "baron_return_4":
			dialog.text = "Ki tudja! Jackman gondoskodott róla, hogy elhagyja Maroon Townt. Nem látogat meg engem. Sosem kedveltük egymást, az évek során még ribancabb lett, és most már nagyon utálhat, mert valószínûleg azt hiszi, hogy én vagyok az oka a szerencsétlenségének.\nTalán egyedül keresi Hawkot, de mit tehet egy nô, még ha nadrágot és szablyát is visel! Egyébként a szablyát is elsajátította. Nem ajánlom, hogy teszteljétek, ha találkoztok vele. Igen, és a banditákkal sincs értelme beszélgetni. Nagyon impozáns tábort vertek ott, és állig fel vannak fegyverezve.\nÚgy tûnik, volt katonák, és jól ismerik a dolgukat. Nem engednek be senkit a területükre. Azt mondják, hogy a spanyolok aranyat bányásztak ott. De az arany kimerült, és felhagytak a bányával. Fogalmam sincs, mit keresnek ott azok a szemetek.";
			link.l1 = "Nos, mivel Sólyom holttestét senki sem látta, a remény, hogy élve megtaláljuk, megmarad. Isten tudja, talán még vissza is adhatnánk neki a báróságot.";
			link.l1.go = "baron_return_5";
		break;
		
		case "baron_return_5":
			dialog.text = "Igen, mit szólsz ehhez? Tessék, fogd ezt a levelet. Ha találkozol Steve Dodsonnal, azonnal add oda neki. A levél tartalma garantálja a biztonságát. Nos, csak a biztonság kedvéért.";
			link.l1 = "Köszönöm, Jan. Gondoskodom róla, hogy így legyen!";
			link.l1.go = "baron_return_6";
		break;
		
		case "baron_return_6":
			DialogExit();
			GiveItem2Character(pchar, "letter_svenson");
			AddQuestRecord("BaronReturn", "1");
			pchar.questTemp.Saga.BaronReturn = "begin";
			pchar.quest.Saga_DannyMeeting.win_condition.l1 = "location";
			pchar.quest.Saga_DannyMeeting.win_condition.l1.location = "SantaCatalina_town";
			pchar.quest.Saga_DannyMeeting.function = "Saga_DannyMeeting";
		break;
		
		case "return_LSC":
			dialog.text = "Miért vágsz ilyen hosszú arcot? Fáradt vagy? Talán egy pohár rumot?";
			link.l1 = "Nem bánnám...";
			link.l1.go = "return_LSC_1";
		break;
		
		case "return_LSC_1":
			LAi_AlcoholSetDrunk(pchar, 51, 5600);
			dialog.text = "Tessék, igyál egy pohárral. Most beszélj.";
			link.l1 = "(ivás) Ah, így már sokkal jobb... Nos, Jan, neked és a fekete lelkésznek is igaza volt. Az Igazság Szigete létezik. Ott voltam.";
			link.l1.go = "return_LSC_2";
		break;
		
		case "return_LSC_2":
			dialog.text = "Mondtam, hogy állítólag van ott egy csempészbázis!";
			link.l1 = "Valójában nincs ott semmiféle bázis. És a karibi pletykák nem hazudtak. Feketék és fehérek tényleg együtt élnek ott, persze nem feltétlenül békében, inkább mint kutya és macska. Maga a sziget pedig megszámlálhatatlanul sok hajóroncsból áll.";
			link.l1.go = "return_LSC_3";
		break;
		
		case "return_LSC_3":
			dialog.text = "El sem hiszem! Jose Dios nagyon kíváncsi lesz a történetedre, ebben biztos vagyok. Mellesleg látogasd meg ôt egyszer.";
			link.l1 = "Majd késôbb meglátogatom. Most nem a legjobb az idô erre. Jelenleg sokkal sürgôsebb dolgokkal kell foglalkoznom. Megtaláltam Nathaniel Hawkot a szigeten.";
			link.l1.go = "return_LSC_4";
		break;
		
		case "return_LSC_4":
			dialog.text = "Megtalálta Nathan-t? Ez figyelemre méltó! Hogy van?";
			link.l1 = "Hát... Beteg, állandóan részeg és mélyen depressziós.";
			link.l1.go = "return_LSC_5";
		break;
		
		case "return_LSC_5":
			dialog.text = "Az istenit, ez elkeserítô. Hol van? A hajódon?";
			link.l1 = "Nem, a saját hajóján. A szigeten.";
			link.l1.go = "return_LSC_6";
		break;
		
		case "return_LSC_6":
			dialog.text = "Mi az, nem te hoztad ide? Miért nem hoztátok ide?";
			link.l1 = "Mert nem volt semmi, amire felvehettük volna. Hajó nélkül jutottam el a szigetre.";
			link.l1.go = "return_LSC_7";
		break;
		
		case "return_LSC_7":
			dialog.text = "Az istenit, "+pchar.name+", alig ittál meg egy pohár rumot, máris olyan zagyvaságokat beszélsz, mintha a feledés homályába ittál volna. Mi az, átúsztad a Karib-tengeren? Vagy teknôsöket szíjaztál a lábadra?";
			link.l1 = "Nem, nem úsztam. Jan, én egyenesen a Main dzsungelbôl jutottam a Szigetre, ahogy Nathan is tette, egy varázslatos indián bálványon keresztül. Már annyi embernek elmondtam ezt a történetet, és már belefáradtam annak bizonygatásába, hogy nem ôrültem meg, úgyhogy csak annyit mondhatok: csak higgy nekem, rendben!?";
			link.l1.go = "return_LSC_8";
		break;
		
		case "return_LSC_8":
			dialog.text = "Indiai bálvány?";
			link.l1 = "A Karib-tengeren legalább három Kukulcan-szobornak nevezett bálvány létezik: egy a West Main nevû miskitó falu közelében, egy a Justice-sziget sekély vizének mélyén, egy pedig a Dominikai karib faluban. Ezek a bálványok az indián mágia segítségével képesek az embereket azonnal átvinni térben és idôben.";
			link.l1.go = "return_LSC_9";
		break;
		
		case "return_LSC_9":
			dialog.text = "";
			link.l1 = "Mindhárom szobron körbe-körbe haladtam át, és pont ott szálltam ki, ahol a miskitó faluban az utamat kezdtem. Ha nem hisznek nekem, akkor áthívhatom Danielle-t. Ô mindent a saját szemével látott!";
			link.l1.go = "return_LSC_10";
		break;
		
		case "return_LSC_10":
			dialog.text = "Danielle? Sólyom felesége? Veled volt?";
			link.l1 = "Részben igen. Ô maga talált rám Blueweldben, és elvitt a miskitó faluba, egy sámánhoz, aki elküldött a varázsszoborhoz. Most az egyik tisztemként szolgál, persze csak ideiglenesen.";
			link.l1.go = "return_LSC_11";
		break;
		
		case "return_LSC_11":
			dialog.text = "Teljesen elképedtem, "+pchar.name+"! Ahogy az angolok mondják. Téged ezüstkanállal etettek. Maga egy szerencsés kurafi! Rendben, elhiszem neked, bár nehéz. De a Nathan ügye nem változik, neki kell segíteni.";
			link.l1 = "Ezt fogom tenni. Egy expedíciót készítek elô az Igazság Szigetére. Most már mindenem megvan, amire szükségem van: a sziget koordinátái és a hajózási irányok.";
			link.l1.go = "return_LSC_12";
		break;
		
		case "return_LSC_12":
			dialog.text = "Fantasztikus. Segíthetek valamiben?";
			link.l1 = "Nem, köszönöm. De kihagytam egy apró részletet. Nathan mellett Shark Dodsont is megtaláltam a szigeten.";
			link.l1.go = "return_LSC_13";
		break;
		
		case "return_LSC_13":
			dialog.text = "Tehát tényleg odament! Nos, "+pchar.name+", kiváló munkát végeztél. Hogy van Dodson ott? Beszéltél vele, ugye?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				link.l1 = "Nem csak beszéltem vele. Barátok is lettünk. Ô volt az, aki megadta a vitorlázási irányt, amire szükségem lesz, hogy visszajussak a szigetre. Steven beleegyezett, hogy elcseréli a hadihajójának kabinját Sharptown rezidenciájára.";
				link.l1.go = "return_LSC_14";
			}
			else
			{
				link.l1 = "Beszélgettünk, igen, de végül kiderült, hogy haszontalan volt. Steven meghalt, miközben én a szigeten tartózkodtam, amikor a hajóskapitánya, Chad Kapper által szervezett összeesküvés akcióba lépett.";
				link.l1.go = "return_LSC_17";
			}
		break;
		
		case "return_LSC_14":
			dialog.text = "Hah! És hogy sikerült Sharknak egy hadihajó kapitányává válnia?";
			link.l1 = "A hajó már több mint fél évszázada véget nem érô 'nyugalom' ban van. Csapdába esett a népével a szigeten. Ezért nem mutatkozik már olyan régóta a Karib-tengeren. Mindenesetre hamarosan elhozom ide, és ô maga mesél majd a kalandjairól.";
			link.l1.go = "return_LSC_15";
		break;
		
		case "return_LSC_15":
			dialog.text = "Alig várom már! Most már kezdenek javulni a dolgok. Csak erôsebbek lettünk, "+pchar.name+". Mikor tervezed, hogy visszautazol a szigetre?";
			link.l1 = "Most rögtön. Csak egy percre jöttem ide, hogy elmondjam a híreket, míg Danielle az expedíció elôkészületeit végzi. Alig várja, hogy láthassa a Nathanját. És tudod mit, Jan, nem is olyan nagy ribanc.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_16":
			dialog.text = "Tényleg?  Nos, talán nem volt igazam vele kapcsolatban. Rendben, "+pchar.name+", nem tartalak vissza tovább. Menjetek, és legyen szerencsétek! Alig várom, hogy visszatérj.";
			link.l1 = "Viszlát, Jan.";
			link.l1.go = "return_LSC_19";
		break;
		
		case "return_LSC_17":
			dialog.text = "Chad Kapper? Basszus, ismertem ezt a fickót. Ô ölte meg Steven-t? Az a szemétláda...";
			link.l1 = "Kapper halott. De Steven-t nem tudjuk visszahozni, ezért ki kell találnunk, hogyan szervezzük tovább a politikánkat.";
			link.l1.go = "return_LSC_18";
		break;
		
		case "return_LSC_18":
			dialog.text = "Hah! Ez nagy kár... Min kell gondolkodni? Csak meg kell gyôznünk Tyrexet, hogy álljon a Testvériség élére. Különben is, Blaze után Tyrex, mint a Kódex ôrzôje, a legtekintélyesebb figuránk. De elôbb vissza kell hoznunk Hawkot, hogy legalább egy ászunk legyen. Mikor indulsz a Szigetre?";
			link.l1 = "Most rögtön. Csak egy percre jöttem ide, hogy elmondjam a híreket, míg Danielle az expedíció elôkészületeit végzi. Alig várja, hogy láthassa a Nathanját. És tudod mit, Jan, nem is olyan nagy ribanc.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_19":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "return_LSC";
			// LSC ждёт своего героя!
			i = FindIsland("LostShipsCity");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			pchar.quest.return_LSC.win_condition.l1 = "location";
			pchar.quest.return_LSC.win_condition.l1.location = "LostShipsCity";
			pchar.quest.return_LSC.function = "LSC_ReturnCheckShips"; // проверка типов кораблей
			pchar.quest.return_LSC_attack.win_condition.l1 = "location";
			pchar.quest.return_LSC_attack.win_condition.l1.location = "Beliz";
			pchar.quest.return_LSC_attack.function = "LSC_ReturnJackmanAttack"; // атака наймитов Джекмана
			pchar.quest.return_LSC_main.win_condition.l1 = "Ship_location";
			pchar.quest.return_LSC_main.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.return_LSC_main.function = "LSC_ReturnMain"; // основная функция возвращения
		break;
		
		case "nathaniel":
			dialog.text = "Hogy van? Azt mondtad, hogy nem érzi jól magát.";
			link.l1 = "Igen, pontosan így van. Magammal viszem, hogy Kígyószem, a sámán kezelje a miskitó faluban.";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "Akkor nincs vesztegetni való idô! Siess, "+pchar.name+"! Amint átadod Nathant a sámánodnak, azonnal gyere vissza hozzám.";
			link.l1 = "Rendben, Jan. Jól hangzik a terv.";
			link.l1.go = "exit";
			npchar.quest.shamane = "true";
		break;
		
		case "nathaniel_2":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				if (CheckAttribute(npchar, "quest.shark")) //и на месте
				{
					dialog.text = "Rendben. Steven már beugrott hozzám. Most végre folytathatjuk a terveink megbeszélését.";
					link.l1 = "Csupa fül vagyok, Jan.";
					link.l1.go = "barbazon";
				}
				else
				{
					dialog.text = "Ez persze szép, de miért nem jött még Dodson, hogy meglátogasson? Mi az, a szigeten hagytad?";
					link.l1 = "Hm... Sietve vittem Nathant Snake Eye-hoz...";
					link.l1.go = "nathaniel_wait";
				}
			}
			else
			{
				dialog.text = "Rendben. Sír a szívem Shark miatt. De ilyen az élet, úgyhogy Tyrex átveszi a helyét. Nos, most már végre folytathatjuk a terveink megbeszélését.";
				link.l1 = "Csupa fül vagyok, Jan.";
				link.l1.go = "barbazon";
			}
		break;
		
		case "nathaniel_wait":
			dialog.text = "...és elfelejtetted bevenni Sharkot? Nem hiszem el, "+pchar.name+"! Szállítsd le Steven-t Blueweld-nek most! Hallod, amit mondok? Gyerünk!";
			link.l1 = "Nyugodj meg, Jan. Mindent elintézek.";
			link.l1.go = "exit";
			NextDiag.TempNode = "nathaniel_wait_1";
		break;
		
		case "nathaniel_wait_1":
			if (CheckAttribute(npchar, "quest.shark"))
			{
				dialog.text = "Steven beugrott hozzám. Most végre folytathatjuk a terveink megbeszélését.";
				link.l1 = "Csupa fül vagyok, Jan.";
				link.l1.go = "barbazon";
			}
			else
			{
				dialog.text = "Ó, "+pchar.name+"... Nekem úgy tûnik, hogy mostanában túl sok rumot ittál. Látod, ennek sosincs jó vége. Elôször remegni kezd a kezed, aztán elkezded elveszíteni a memóriádat, aztán fekete foltot kapsz...";
				link.l1 = "Megértettem, Jan. Azonnal megyek Stevenért!";
				link.l1.go = "exit";
				NextDiag.TempNode = "nathaniel_wait_1";
			}
		break;
		
		case "barbazon":
			dialog.text = "A fekete lelkipásztor nagyon világosan fogalmazott, ôt csak ez a teológiai könyv érdekli. Elküldtem az embereimet, hogy keressék meg, talán valaki megtalálja. Marcus Tyrex nem kérdés, nem lesz gondunk meggyôzni ôt. Jackman nem sokkal azután hagyta el Maroon Townt, hogy meglátogattad. Elhajózott valahová a 'Centurion', a Hawks' fregatton.\nMár csak Barbazon maradt - ôt Jacques, a Kindman néven is ismerik. Meg kell találnunk a módját, hogy rávegyük, hogy együttmûködjön velünk. Egyelôre nem tudom, hogy ezt hogyan lehet végrehajtani. De egy dolog nyilvánvaló - meg kell látogatni ôt.";
			link.l1 = "Mesélj nekem Barbazonról."; // Addon 2016-1 Jason пиратская линейка патч 17/1
			link.l1.go = "barbazon_1";
		break;
		
		case "barbazon_1":
			dialog.text = "Titokzatos típus. Szegénynek tetteti magát, pedig ô a Karib-tenger leggazdagabb embere. Ô irányítja az összes keleti csempészetet. Ha Marcus nem állna ellene, ô irányítaná a Windward-szigetek teljes csempészforgalmát. Tyrex olyan, mint egy csont a torkán.\nA tanácsban mindig összevesznek, de Barbazon nem elég tökös ahhoz, hogy nyílt háborút üzenjen. Talán tényleg dunkerque-i kalóz volt valaha, ahogy állítja, de most inkább egy uzsorásra emlékeztet.";
			link.l1 = "Hogy a fenébe választották meg bárónak?";
			link.l1.go = "barbazon_2";
		break;
		
		case "barbazon_2":
			dialog.text = "Az arany, barátom, mindent és mindenhol az arany ural, akié az arany, az határozza meg a szabályokat. Különben is, Barbazon igazán jó abban, hogy mindenféle jövedelmezô és illegális mûveleteket találjon ki. Ô maga nem vesz részt bennük, de mindig kiveszi a részét. Így állandóan egy csomó bátor, többnyire fejben gyenge gengszter van körülötte. Nélküle mindannyian éhen halnának vagy a bitófán végeznék.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				link.l1 = "Engem Marcusra emlékeztet... Jan, az a helyzet... Fogalmam sincs, hogyan közelítsek Barbazonhoz. Van egy probléma, amivel nem vagy tisztában.";
				link.l1.go = "barbazon_5";
			}
			else
			{
				link.l1 = "Hogyan jutok el Barbazonhoz?";
				link.l1.go = "barbazon_3";
			}
		break;
		
		case "barbazon_3":
			dialog.text = "Egyszerûen tegyen úgy, mintha egyike lenne azoknak az idiótáknak, akiknek tippre van szükségük egy zsíros álláshoz. Eszedbe se jusson megpróbálni becsapni ôt a részesedésével kapcsolatban. A jótékony Barbazon nem bocsát meg.";
			link.l1 = "Ez magától értetôdô. Nem fogok vele összejönni a saját hasznomra. Mindenesetre itt az ideje, hogy meglátogassuk.";
			link.l1.go = "barbazon_4";
		break;
		
		case "barbazon_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "1");
			pchar.questTemp.Saga.BarbTemptation = "begin";
			pchar.questTemp.Saga.BaronReturn = "barbazon";
			NextDiag.CurrentNode = "First time";
			// тут вычищаем квестовый мусор от LSC
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
			if (CheckCharacterItem(pchar, "letter_chad_1")) RemoveItems(pchar, "letter_chad_1", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "barbazon_5":
			dialog.text = "Tényleg? - Igen. Lôdd le.";
			link.l1 = "Hallottál már Charlie Prince-rôl?"; 
			link.l1.go = "barbazon_6";
		break;
		
		case "barbazon_6":
			dialog.text = "Igen, hallottam a pletykákat. Ez a fickó nem is olyan régen Marcus Tyrexnek dolgozott. Elég sokat tett rövid idô alatt, Cartagena kifosztásával szerzett magának hírnevet. És?";
			link.l1 = "Ez a fickó én vagyok. Charlie Prince vagyok. Én voltam. Látod?"; 
			link.l1.go = "barbazon_7";
		break;
		
		case "barbazon_7":
			dialog.text = "Baszd meg! Te vagy Charlie Prince? Micsoda csavar! "+pchar.name+", le vagyok nyûgözve! Most már látom, honnan származik a fogásod... De mi köze van ehhez Barbazon-nak?";
			link.l1 = "Mi lenne, ha Prince meglátogatná Barbazont, Jan?"; 
			link.l1.go = "barbazon_8";
		break;
		
		case "barbazon_8":
			dialog.text = "Hm... ezt már értem. Volt már dolgod vele korábban?";
			link.l1 = "Nem igazán. Az egyik Ignacio Marco nevû zsiványa Barbazon közvetlen parancsára próbált meg kicseszni velem. A kis háborújuk része volt."; 
			link.l1.go = "barbazon_9";
		break;
		
		case "barbazon_9":
			dialog.text = "Látta az arcát? Bemutatkozott neki?";
			link.l1 = "Nem."; 
			link.l1.go = "barbazon_10";
		break;
		
		case "barbazon_10":
			dialog.text = "Akkor nem látok problémát. Én is hallottam a Charlie Prince nevû kalózról, de nem tudtam, hogy te vagy az, mielôtt elmondtad volna.";
			link.l1 = "Azt hiszed, Barbazon nem fog átlátni rajtam?"; 
			link.l1.go = "barbazon_11";
		break;
		
		case "barbazon_11":
			dialog.text = "Hogyan is tehetné, ha még sosem látta az arcodat? Csak parancsot adott, hogy szabaduljon meg Marcus' egyik alkalmazottjától.";
			link.l1 = "Hm... Lehet, hogy ebben igazad van."; 
			link.l1.go = "barbazon_12";
		break;
		
		case "barbazon_12":
			dialog.text = "Kizárt, hogy Barbazon nélkül túléljük ezt. Menjetek el hozzá, de legyetek óvatosak. Fuss, ha felismer téged, akkor majd kitalálunk egy másik módot, hogy hogyan közelítsük meg.";
			link.l1 = "Rendben. Nekem most mennem kell. Már alig vártam, hogy találkozzam a rohadékkal."; 
			link.l1.go = "barbazon_13";
		break;
		
		case "barbazon_13":
			dialog.text = "Ne játszd a hülyét, és ne próbáld meg átbaszni Jacques-ot. Sosem bocsát meg. Viselkedj úgy, mint egy idióta, aki könnyû pénzre vágyik.";
			link.l1 = "Úgy tûnik, a kedvenc szerepem... Viszlát, Jan!"; 
			link.l1.go = "barbazon_4";
		break;
		
		case "saga_26":
			dialog.text = "Igen. Az indián sámán mindent beleadott, amit tudott, Sólyom olyan, mint új korában. Állítólag már Maroon Townban van Dannie-vel, úgyhogy ha akarod, menj és köszönj neki. Nagyon örülnének, ha látnának.";
			link.l1 = "Mindenképpen beugrom megnézni, hogy vannak... Jan, sikerült megtalálnom Sharp térképének második részét! Jackman kabinjában volt. Most már nem lesz gondunk bizonyítani Helen jogait az Isla Tesoro-hoz.";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			dialog.text = "Remek, mutasd meg.\nIgazunk volt, Jacob volt az, aki megölte Blaze-t. Most a Shark nevén lévô foltot örökre eltüntetjük. Ami a bizonyítékot illeti, az már kényesebb kérdés. És csak nagyon alapos mérlegelés után szabad megközelíteni.";
			link.l1 = "Még valami, Jan. Nézd meg ezt a jegyzetet. Ez is Jackman dolgai között volt.";
			link.l1.go = "saga_28";
		break;
		
		case "saga_28":
			RemoveItems(pchar, "letter_parol", 1); // удалить записку
			dialog.text = "Nézzük csak meg... Ha, szóval ezért hallgattak a banditák Jackmanra és ezért hagyták abba Miskitos elrablását! Nem is alakulhatott volna másképp! Az a szemétláda mindent kitervelt, és több lépéssel elôrébb járt.";
			link.l1 = "Ja, és már értem, miért mészárolták le Sólyom embereit is. De két dolgot nem értek: elôször is, mit keresnek Jackman bûntársai a bányában, másodszor, miért reagálsz ilyen nyugodtan arra, hogy ez az egész balhé a te területeden zajlik?";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "Szégyellem magam... Igazad van. Jackman tényleg elszabadult. És a csatlósainak semmi keresnivalójuk az én területemen. Úgy tûnik, eljött az idô, hogy emlékeztessük a Karib-térséget, kivel van dolguk.";
			link.l1 = "Mire gondolsz, Jan?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_30":
			dialog.text = "A múlt felelevenítése... Szándékomban áll büntetô expedíciót szervezni, és minden banditát kiirtani a bányáknál. Most már bizonyítékunk van arra, hogy Jackman emberei, és kötelességem megtisztítani a területeimet ettôl a söpredéktôl.\n"+pchar.name+", kiváló munkát végeztél. Itt az ideje, hogy én is beinduljak. Most pihenj egy kicsit. Menj, látogasd meg a Sólymokat. Tíz nap múlva gyere vissza!";
			link.l1 = "Rendben, Jan. Megteszem. Pontosan akkor jövök vissza, amikor mondtad!";
			link.l1.go = "saga_31";
			link.l2 = "Ha! Én is részt akarok venni ebben a keresztes hadjáratban. Miért döntöttél úgy, hogy a pihenôidômre teszel?";
			link.l2.go = "saga_31_1";
		break;
		
		case "saga_31_1":
			dialog.text = "Bocsásson meg, öregem. Csak arra gondoltam, hogy végre itt az ideje, hogy én is dolgozzak, te pedig pihenj egy kicsit. De ha ez a kívánságod, akkor több mint boldog lennék! Csapjunk le együtt a viharra! És mindent, amit a bányában találunk, egyenlôen osztunk el a legénységünk között, ahogy a testvérek törvényeiben meg van írva.";
			link.l1 = "Megegyeztünk, Jan! Mikor indulunk?";
			link.l1.go = "saga_31_2";
		break;
		
		case "saga_31_2":
			dialog.text = "Gyere az embereiddel a Szúnyogpartra három nap múlva. Addigra összegyûjtöm a csapatom, és már ott leszek, és várok rád. Ne késs!";
			link.l1 = "Rendben, Erdei Ördög. Már alig várom, hogy hátulról hátulról harcba szálljak veled! Hamarosan találkozunk!";
			link.l1.go = "saga_31";
			npchar.quest.mine_tw = "true";
		break;
		
		case "saga_31": 
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if (CheckAttribute(npchar, "quest.mine_tw"))
			{
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1 = "location";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1.location = "Shore53";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2 = "Timer";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.hour  = sti(GetTime());
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.function = "Saga_MineBanditsPrepareAttack";
				SetFunctionTimerCondition("Saga_MineBanditsAttackOver", 0, 0, 4, false); // таймер
			}
			else SetFunctionTimerCondition("Saga_MineBanditsDestroyed", 0, 0, 10, false); // таймер
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
		break;
		
		case "saga_32a":
			dialog.text = "Remek. Kiderítettem valamit a bánya titokzatos tulajdonosáról, Lawrence Beltrope-ról.";
			link.l1 = "Szóval, ki ez a madár?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_32":
			dialog.text = "Legyôztem Jackman strómanjait a bányában. Végül is kemény diónak bizonyultak, de az én embereim sem tegnap születtek. Ráadásul le tudtuk tenni az éberségüket, miután megmondtuk nekik a jelszót a megtalált cetlirôl. Behatoltunk a bányába, és látványosan elbúcsúztattuk ôket.";
			link.l1 = "Elfoglaltátok a bányát? Kiváló!";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "Legyen ez lecke mindenkinek, aki azt hiszi, hogy az Erdei Ördög rozsdás. Tényleg túl sokat lustálkodtam az elmúlt években, és nézd meg, mi történt? Jackman az orrom elôtt bontogatta gonosz tervét!";
			link.l1 = "Mit láttál abban a bányában? Mesélj róla!";
			link.l1.go = "saga_34";
		break;
		
		case "saga_34":
			dialog.text = "A bányát a spanyolok tényleg elhagyták, azonban Lawrence Beltrope Port Royalból aprópénzért megvásárolta, és titokban folytatta a kitermelést. Úgy tûnik, a spanyolok túl korán dobták ki az aknát, mert bár mi magunk nem találtunk ott aranyat, több rabszolgát is találtunk, akik azt állították, hogy egészen a közelmúltig aranyat lehetett ott találni.";
			link.l1 = "Lawrence Beltrope? Soha nem hallottam róla. Ki ô?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_35":
			dialog.text = "Helybéli, Thomas Beltrope fia, aki régen Nicholas Sharp esküdt testvére és a Providence-szigeti Társaság magánhajósa volt. Én magam is jól ismertem Thomast. Egy évvel ezelôtt Lawrence ismét eljött a Karib-tengerre. Kiderült, hogy Jackman neki dolgozott. Ezt tartsák észben, és tartsák nyitva a szemüket!";
			link.l1 = "Tehát Jackman titokzatos 'boss', , akit a levélben említettek, Lawrence Beltrope... Rendben, megjegyzem ezt a nevet.";
			link.l1.go = "saga_36";
		break;
		
		case "saga_36":
			dialog.text = "Még egy dolog. Valami furcsa dologra emlékszem. Blaze egyszer említett valami elhagyott spanyol aranybányát, és azt, hogy az aranyat Sharptownba akarja fektetni. De a bánya térképe eltûnt, miután a nôvére megszökött Butcher kapitánnyal. Talán a mi bányánkról beszélt?\nAkárhogy is, túl régen volt, és nem sokat változtat... Neked és nekem a Tanáccsal kellene foglalkoznunk. Megvan mind az öt szilánk?";
			link.l1 = "Igen. Ez a négy: Nathaniel, Tyrex, Marlow és Barbazon. Mindegyikük igent mondott.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			sTemp = "Cápa";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			dialog.text = "Remek. Biztos vagyok benne, hogy nem lesz probléma a "+sTemp+" megválasztása a Partiumi Testvérek vezetôjének. Azonnal azon leszek, hogy összehívjam a Tanács ülését.";
			link.l1 = "Tehát Jan, egyelôre minden problémát kézben tarthatunk? Nathaniel Maroon Townban van, Jackman halott, és a Testvériségnek új feje van... Talán itt az ideje, hogy visszatérjünk oda, ahonnan indultunk, vagyis Tortuga elfoglalásához?";
			link.l1.go = "saga_38";
		break;
		
		case "saga_38":
			dialog.text = "Emlékszem, "+pchar.name+", de egy kicsit ki kell várnunk az idôt. Ráadásul az idô Sharp örökségének rendezésére is fogytán van, és ezt a kérdést, mint tudják, komolyan kezelni kell.";
			link.l1 = "Mi a baj az örökléssel? Megvan a térkép mindkét része. Már csak be kell mutatnunk ôket, és kész...";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = ""+pchar.name+", biztosíthatom önöket, hogy manapság nem csak úgy egyszerûen adnak szigeteket az embereknek. Még a törvényes örökösöknek sem a tanúvallomás minden paragrafusának teljesítésével. Az angol hatóságok nagyon akarják ezt a szigetet, ezzel tisztában vagyok.\nNem hiszem, hogy Doyle ezredes tétlenül fogja nézni, hogy elvesszük tôlünk a szigetet, amit már most is angol tulajdonnak tekint. Továbbá, mi ketten maradjunk az árnyékban.";
			link.l1 = "És mit javasolsz?";
			link.l1.go = "saga_40";
		break;
		
		case "saga_40":
			dialog.text = "Menjetek Port Royalba, és keressetek ott egy Albert Loxley nevû embert. Ô a legjobb ügyvéd az egész Karib-térségben. Jelentôsen jártas mindenféle kétes ügyekben, így bármilyen munkát elvállal, ha túlzó díjat ajánlanak neki érte. Királyi étvágya van, de megéri.";
			link.l1 = "Gondolod, hogy Sharp végrendelete tartalmazhat néhány buktatót?";
			link.l1.go = "saga_41";
		break;
		
		case "saga_41":
			dialog.text = "Nem csak hiszem, hanem biztos vagyok benne. Volt már dolga hivatalnokokkal? Tudd meg, hogy ha akarnak tôled valamit, akkor kihúzzák a lelkedet, orrba-szájjal mutogatnak egy rosszul elhelyezett vesszôre, mindent úgy értelmeznek, ahogy nekik kell, és úgy hagynak meztelenül, mint egy vak cicát.\nEzért hozták létre a rétegeket. A hivatalnokok ellen a saját fegyvereikkel - a szóvirágokkal, a tintapénzzel és a sikkasztással - harcolnak. Ezért meg kellene látogatnod Loxley-t, és fel kellene bíznod, hogy védje meg az érdekeinket, amíg én a választásokkal foglalkozom.";
			link.l1 = "Rendben. Elmegyek Port Royalba. Mennyi idôbe telik, amíg a Tanács összeül és megtartja a választást?";
			link.l1.go = "saga_42";
		break;
		
		case "saga_42":
			dialog.text = "Tíz nap. Szóval ne fáradj azzal, hogy korábban keresel Blueweldben.";
			link.l1 = "Megvan. Nos, Jan. Ebben az esetben, majd találkozunk!";
			link.l1.go = "saga_43";
		break;
		
		case "saga_43":
			DialogExit();
			AddQuestRecord("Testament", "1");
			pchar.questTemp.Saga = "loxly"; // обновляем флаг
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			SetFunctionTimerCondition("Saga_GoldForLoxly", 0, 0, 10, false); // таймер
		break;
		
		case "saga_44":
			sTemp = "Steven Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = ""+sTemp+" a legmelegebb üdvözletét küldi. Mindig szívesen látja Önöket az Isla Tesoro-i rezidenciáján. Látogassátok meg, ha alkalom adódik rá.";
			link.l1 = "Ahhoz, hogy a "+sTemp+" ne hagyja el az új lakhelyét, neked és nekem, Jan, van egy kis munkánk.";
			link.l1.go = "saga_45";
		break;
		
		case "saga_45":
			sTemp = "Négyszázötven.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "Ezer...";
			dialog.text = "Gondolom, már jártál Loxley-ban...";
			link.l1 = "Igen, én igen. Elvállalja az ügyünket, de egy halom aranyat követelt a szolgálataiért. "+sTemp+" dublont elôre. Elôleg! És még többet is kell majd fizetnünk neki, attól függôen, hogy Helen jogbizonyítványa mennyire fog sikerülni. Az összeg megduplázódik vagy megháromszorozódik, ahogy mondta.";
			link.l1.go = "saga_46";
		break;
		
		case "saga_46":
			dialog.text = "Ha! Nos, nem gondoltam, hogy egy ilyen vén csavargótól, mint ô, kevesebbet várnék. Már messzirôl kiszagolja a zsákmányt, akár egy hiéna. Persze itt egy egész szigetrôl van szó. Nevetséges azt gondolni, hogy Albert nem kérne pár százast. Tehát a teljes összeg valahol ezerötszáz arany körül lehet...";
			link.l1 = "Jan, az egy tonna pénz!";
			link.l1.go = "saga_47";
		break;
		
		case "saga_47":
			dialog.text = "Tudom, mire akarsz kilyukadni. Egyetértek azzal, hogy nem vagy valami hülye gorilla, aki ezt mind a saját zsebbôl fizeti. De sajnos jelenleg nincs ennyi aranyam elrejtve. Terveztem ilyen kiadásokra, azonban egy feketelakó beavatkozása mindent tönkretett.";
			link.l1 = "Mirôl beszélsz?";
			link.l1.go = "saga_48";
		break;
		
		case "saga_48":
			dialog.text = "Hallgassa meg. Talán már tudod, hogy a megállapodásunk csak félig törvényes. Az angolok helyôrséget tartanak itt, és mi jó áron ellátjuk ôket mahagónival. De van egy nagyon nehéz és tartós fafajta - a Lignum Vitae, amit vasfaként kell ismerned.\nEz ritka és még edzett acéllal is nehezen megmunkálható. Azt mondják, hogy réges-régen a maják-itzák ebbôl készítették rettentô bunkósbotjaikat. A nyílt piacon nem lehet vasfát venni, és csempészve a súlya ezüstjébe kerül.\nDoyle emberei idônként eljönnek, és olcsón felvásárolják az egész mennyiséget, amit feldolgoztunk. De nekem mindig sikerül félretennem egy keveset a saját szükségleteimre.";
			link.l1 = "Hallottam errôl a fáról. Azt mondják, hogy a muskétagolyók úgy süllyednek bele az olajos fába, mint a kátrány! Elég erôs ahhoz, hogy acélszerkezetek fogaskerekeit készítsék belôle.";
			link.l1.go = "saga_49";
		break;
		
		case "saga_49":
			dialog.text = "A fogaskerekekrôl egy kicsit hazudnak, de a többi igaz. Szóval, a kiadásokat megjósolva, készítettem egy nagy tétel vasfát, de valami szemétláda pár napja kiürítette a raktáramat. Valaki közülünk, ezt tudom. Van egy gyanúm, de biztosat nem tudok mondani.";
			link.l1 = "A patkányokat el kell taposni! Kire gyanakszik?";
			link.l1.go = "saga_50";
		break;
		
		case "saga_50":
			dialog.text = "Paul Molligan. A kelet-indiai 'Oyster' tegnap Barbadosra hajózott. Nem volt alkalmam ellenôrizni a rakterét. De a vasfát amúgy sem hozná Bridgetownba, lord Willoughbynak ott komoly vámosai vannak, a vasfa pedig stratégiai fontosságú nyersanyag az angol haditengerészet számára.\nHa tényleg nála van a vasfám, akkor eladja, mielôtt Bridgetownba ér. Bárcsak elfoghatnád Molligant, és átvizsgálhatnád a rakterét!...";
			link.l1 = "Azt mondja, hogy tegnap indult Bridgetownba? Még nincs minden veszve. Megpróbálom utolérni.";
			link.l1.go = "saga_51";
		break;
		
		case "saga_51":
			dialog.text = "Tudod, mit kell tenned, ha Molligan a patkány. De elôbb próbáld meg megtudni az ügyfele nevét. Aztán vagy te magad szállítod el a rakományt a megbízónak, vagy visszaadod nekem.\nHozd el a 'Oyster' Blueweldnek is, az egy szép hajó, szeretném magamhoz venni, és a saját igényeimre átrakni. Neked is szabad elvinni, amit csak akarsz nyereményként... És ha esetleg nem Molligan a hibás... nem, biztos vagyok benne, hogy ô a patkány, aki ellopta a vasfámat.";
			link.l1 = "Jól fogom kihasználni az idômet!";
			link.l1.go = "saga_52";
		break;
		
		case "saga_52":
			dialog.text = "Ha maga adja el a vasfát, tegyen félre ezerötszáz aranydublont Loxley-nak, a többit pedig felezzük el. Megbízhatok benned, ugye?";
			link.l1 = "Persze, hogy bízhatok. Nem vagyok patkány.";
			link.l1.go = "saga_53";
		break;
		
		case "saga_53":
			dialog.text = "Nincs kétségem. Sok szerencsét, "+pchar.name+"! Remélem ezúttal rád mosolyog.";
			link.l1 = "Köszönöm. Köszönöm. Viszlát késôbb!";
			link.l1.go = "saga_54";
		break;
		
		case "saga_54":
			DialogExit();
			pchar.questTemp.Saga = "molligan"; // обновляем флаг
			AddQuestRecord("Testament", "3");
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			Saga_CreateMolliganInWorld(); // ставим корабль Моллигана на карту
		break;
		
		case "saga_55":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Tudtam. Mennyi volt a rakodótérben?";
			link.l1 = "Megtaláltam a "+FindRussianQtyString(sti(npchar.quest.bakaut))+" a 'Oyster oldalon.'.";
			link.l1.go = "saga_56";
		break;
		
		case "saga_56":
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp > 100)
			{
				dialog.text = "Hûha! Soha nem volt még ennyi a raktáramban. Nézd csak, kinek a saját boldog kezébe került egy vagyon. Köszönöm, "+pchar.name+", soha nem hagytál cserben. Azonnal eladom a terméket, már van is vevônk. Holnapra meglesz a pénz.";
				link.l1 = "Rendben. Akkor nem zavarlak tovább. Holnap találkozunk.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 90 && iTemp < 101)
			{
				dialog.text = "Igen, nagyjából ennyit ittam. Kis patkány! Köszönöm, "+pchar.name+", soha nem hagysz cserben. Azonnal eladom a terméket, már van is vevônk. Holnapra meglesz a pénz.";
				link.l1 = "Rendben. Akkor nem zavarlak tovább. Holnap találkozunk.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Valószínûleg már sikerült eladnia valakinek a szállítmány egy részét, mert többnek kellett volna lennie. De nem nagy ügy, a nagy részét visszakaptuk. Köszönöm, "+pchar.name+", azonnal eladom a terméket, már van vevônk. Holnapra meglesz a pénz.";
				link.l1 = "Rendben. Akkor nem zavarlak tovább. Holnap találkozunk.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 50 && iTemp < 70)
			{
				dialog.text = "Az isten verje meg, az a szemétláda máris képes volt eladni a szállítmány tisztességes részét... Ah, ez nagy kár. Hát igen. Eladom, ami van, már van rá vevôm. Holnapra meglesz a pénz.";
				link.l1 = "Rendben. Akkor nem zavarlak tovább. Holnap találkozunk.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 20 && iTemp < 50)
			{
				dialog.text = "Az istenit, ez siralmas! Az a szemétláda már így is el tudta adni a szállítmány több mint felét... Ah, ez nagyon rossz. Hát igen. Eladom, ami van, már találtam is rá vevôt. Holnapra meglesz a pénz.";
				link.l1 = "Rendben. Akkor nem zavarlak tovább. Holnap találkozunk.";
				link.l1.go = "saga_oust";
				break;
			}
			dialog.text = "Ember, szarul jártam. Szinte mindent eladott... Tessék, tartsd meg magadnak ezt a vasfát, "+pchar.name+", csinálj vele, amit akarsz. Te vagy az egyetlen reményem, hogy pénzt keressek vele.";
			link.l1 = "Megvan. Rendben, megnézem magam. Nem ez az elsô rodeóm... Szia, Jan.";
			link.l1.go = "saga_oust";
		break;
		
		case "saga_oust":
			if (CheckAttribute(npchar, "quest.bakaut"))
			{
				if (sti(npchar.quest.bakaut) < 20) DeleteAttribute(npchar, "quest.bakaut");
				else 
				{
					SaveCurrentNpcQuestDateParam(npchar, "bakaut_date");
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(npchar.quest.bakaut));
				}
				pchar.questTemp.Saga = "removebakaut";
			}
			int iUst = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN && sld.ship.name == "Oyster") iUst = 1;
				}
			} // есть ли у нас Устрица
			dialog.text = "Várj! Megkaptad a 'Oyster'?";
			if (iUst == 1)
			{
				link.l1 = "Igen. Most is a kikötôben van. Lehorgonyoztam neked, ahogy kérted.";
				link.l1.go = "saga_oust_yes";
			}
			else
			{	
				link.l1 = "Nem. A hajó annyira megsérült a csatában, hogy el kellett süllyesztenem.";
				link.l1.go = "saga_oust_no";
			}
		break;
		
		case "saga_oust_no":
			dialog.text = "Milyen kár. De ez van, ami van. Viszlát késôbb, "+pchar.name+"!";
			link.l1 = "Szia, Jan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_oust_yes":
			dialog.text = "Figyelemre méltó! Felszerelem ezt a szépséget, ahogy megérdemli. És késôbb bármikor kölcsönveheted egy idôre, ahogy megbeszéltük. Azt hiszem, két hónap múlva készen lesz.";
			link.l1 = "Szia, Jan! Szia, Jan! Egy ilyen hajó néha nagyon jól jöhet... Viszlát késôbb, Jan!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_RemoveOuster");
			npchar.quest.ouster = "true";
			SaveCurrentNpcQuestDateParam(npchar, "ouster_date"); // через 2 месяца
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_57":
			int idlt;
			iTemp = sti(npchar.quest.bakaut)*30; // Ян за 1 шт бакаута даёт 30 дублонов
			if (iTemp > 1600)
			{
				idlt = makeint(iTemp-1500)/2; // доля Бонса :)
				dialog.text = "Kaptam érte "+iTemp+" érméket. Ezerötszáz az ügyvédért, plusz a te részed a dublonokból - "+idlt+". Tessék.";
				link.l1 = "Dicséretes! Most már könnyedén el tudok indulni Loxley-ba.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500+idlt);
				break;
			}
			if (iTemp > 1450 && iTemp <= 1600)
			{
				dialog.text = "Ezerötszáz dublont kaptam érte. Ez éppen elég az ügyvédnek. Tessék.";
				link.l1 = "Fantasztikus. Most már el tudok menni Loxley-ba.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500);
				break;
			}
			dialog.text = "Kaptam érte "+iTemp+" dublont. Tessék. A többit magadnak kell elôásnod.";
			link.l1 = "Nos, ha egyedül, akkor egyedül. Rendben, úton vagyok Loxley felé.";
			link.l1.go = "saga_58";
			TakeNItems(pchar, "gold_dublon", iTemp);
		break;
		
		case "saga_58":
			DialogExit();
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.bakaut");
		break;
		
		case "saga_59":
			dialog.text = "Mit szólsz hozzá? Ez érdekes. És mennyit hajlandó fizetni érte a holland fickó?";
			link.l1 = "Negyven dublont darabonként.";
			link.l1.go = "saga_60";
		break;
		
		case "saga_60":
			dialog.text = "Hûha! Az én vevôim kevesebbet fizetnek...";
			link.l1 = "Összességében kétezer aranyat kaptam Loxley-ért és "+sti(npchar.quest.bakaut_sum)*2+" dublont ráadásul.";
			link.l1.go = "saga_61";
		break;
		
		case "saga_61":
			dialog.text = "Teljesen jól. Akkor majd felezzük el.";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.bakaut_pay = func_min(sti(npchar.quest.bakaut_sum), PCharDublonsTotal()); // дублоны в кармане
				link.l1 = "Tessék. Van egy "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "A dublonokat a hajón hagytam. Gyorsan odarohanok, és mindjárt jövök.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "saga_61_1":
			dialog.text = "Remek. Mennyit hoztál?";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.bakaut_pay = func_min(sti(npchar.quest.bakaut_sum), PCharDublonsTotal()); // дублоны в кармане
				link.l1 = "Tessék. Van egy "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "Mi van a memóriámmal! Itt az ideje, hogy abbahagyjuk a rummal való szórakozást. Megint a ládámban hagytam a dublont. Gyorsan odarohanok és elhozom ôket.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay": // оплата
			if (sti(npchar.quest.bakaut_sum) < sti(npchar.quest.bakaut_pay)) // полная сумма
			{
				npchar.quest.bakaut_pay = sti(npchar.quest.bakaut_sum);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.bakaut_sum)-sti(npchar.quest.bakaut_pay);
			npchar.quest.bakaut_sum = iTemp; // запоминаем остаток
			RemoveDublonsFromPCharTotal(sti(npchar.quest.bakaut_pay));
			Log_Info("Adtál "+sti(npchar.quest.bakaut_pay)+" dublont.");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "Szép munka, "+pchar.name+"! Ismét eszembe jutott, hogy jó veled foglalkozni.";
				link.l1 = "Megpróbálom, Jan...";
				link.l1.go = "bakaut_done";
			}
			else
			{
				dialog.text = "Remek. Késôbb elhozza a maradék "+FindRussianQtyString(sti(npchar.quest.bakaut_sum))+" dublont?";
				link.l1 = "Igen. Csak nem tudnék egy ekkora halom aranyat egyszerre elhozni.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay_wait":
			dialog.text = "Szóval, "+pchar.name+", hogy állnak a dublonjaim?";
			link.l1 = "Hajlandó vagyok adni neked még egy kis aranyat.";
			link.l1.go = "saga_61_1";
		break;
		
		case "bakaut_done": // рассчитались
			dialog.text = "Van egy ajánlatom számodra. Mivel sikerült találnod egy jövedelmezô vevôt, akkor eladhatnék neked egy kis vasfát. Régebben harminc dublont kaptam darabonként. Ha akarod, megveheted tôlem ennyiért. Inkább neked adom el, mint másnak.";
			link.l1 = "Mennyi vasfát tudsz eladni?";
			link.l1.go = "bakaut_done_1";
		break;
		
		case "bakaut_done_1":
			dialog.text = "Kerülöm a nagy tételek megtakarítását. A Molligan's kivétel volt. A hatóságoknak nem fog tetszeni a helyi feketepiac híre. Szóval, itt az alku: minden hónap 14-én és 24-én 25 darab vasfát teszek félre neked.\nHa meg akarod venni, hozz hétszázötven dublont, és vidd el az egész tételt. Ha nem jelensz meg aznap, akkor eladom egy másik vásárlónak. Így havonta 50 darabot kaphatsz. Megegyeztünk?";
			link.l1 = "Megegyeztünk, Jan! Csináljuk meg. Itt az ideje, hogy én is elinduljak...";
			link.l1.go = "saga_oust";
			DeleteAttribute(npchar, "quest.bakaut_sum");
			npchar.quest.trade_bakaut = "true"; // генератор купли-продажи бакаута
			AddQuestRecordInfo("Unique_Goods", "1");
		break;
		
		case "saga_59_1": // укрысил у Яна - нет генератора на бакаут, потерял больше
			dialog.text = "Ah, szóval vagy nem ô volt, vagy már korábban eladta a vasfát... Milyen kár. Nos, most már csak te vagy az egyetlen reményem, hogy megkapjam a pénzt az ügyvédre.";
			link.l1 = "Hajlandó vagyok vállalni ezt a felelôsséget. Nem ez az elsô rodeóm.";
			link.l1.go = "exit";
			// Ян расстроен и забыл про Устрицу - так что и Устрицы тоже не будет
			DeleteAttribute(npchar, "quest.bakaut_sum");
		break;
		
		case "saga_62":
			dialog.text = "Tényleg? Ez érdekes. Gyerünk, kérdezzen. Kirôl akarsz beszélni?";
			link.l1 = "Egy lányról. A neve... Jessica Rose.";
			link.l1.go = "saga_63";
		break;
		
		case "saga_63":
			dialog.text = "A neve Jessica Rose Rose. A testvéreink új vezetôje mesélt róla?";
			link.l1 = "Ô is mesélt. De én Baker-tôl, a régi Szent János hóhértól tudtam meg róla. Ugyanaz az ember, aki Mészáros kapitányt halálra ítélte.";
			link.l1.go = "saga_64";
		break;
		
		case "saga_64":
			dialog.text = "Rendben. Hm. Nos, már több mint húsz éve, hogy utoljára láttam Jessicát. Mit tudsz róla?";
			link.l1 = "Nos, tudom, hogy került Butcher kapitányhoz, és hogy együtt kalózkodtak. Tudom, hogy elhagyta ôt Beatrice-ért. Késôbb bosszút állt érte valami Joshua Leadbeater, más néven a Maszk segítségével...";
			link.l1.go = "saga_65";
		break;
		
		case "saga_65":
			dialog.text = "";
			link.l1 = "Azt is tudom, Jan, bocsássa meg az ôszinteségemet, hogy maga is érdeklôdött Jessica iránt. Ez az oka annak, hogy eljöttem hozzád. Jessica fontos szereplôje a kereséseimnek. Ô volt az, aki féltékenységbôl meggyilkolta Beatrice Sharpot, ha jól tudom.";
			link.l1.go = "saga_66";
		break;
		
		case "saga_66":
			dialog.text = "Nos, nagyon sokat tudsz. Igen, tényleg udvaroltam Jessnek, de ez nem volt meglepô, Isla Tesoro összes kalóza két különbözô csoportra oszlott akkoriban: azokra, akik Beatrice-t akarták megdugni, és azokra, akik Jessicát akarták.\nJól emlékszem rá... Gyönyörû volt, nagyon szép!...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Jess");
			NextDiag.TempNode = "saga_66a";
		break;
		
		case "saga_66a":
			dialog.text = "Különleges volt... Az is elég valószínû, hogy Jess ölte meg Beatricét. Miután Butcher kirúgta a seggét a 'Neptune', valószínûleg semmi másra nem gondolt, csak arra, hogy bosszút álljon rajta és Beatrice-on. Egyébként tudod, hogyan szabadult meg Butcher Jessicától?";
			link.l1 = "Nem. Vagy csak úgy elengedte Barbadoson, vagy váltságdíjat követelt érte.";
			link.l1.go = "saga_67";
		break;
		
		case "saga_67":
			dialog.text = "A második. Hihetetlenül lealacsonyította ôt. Egyszerûen bezárta a kunyhóba, Barbadosra vitte, tárgyalni kezdett az apjával, Oliver Rose-zal, és tulajdonképpen eladta egy rakás dublonnáért... azok után, amit a lány tett érte.";
			link.l1 = "Hm. Azt hittem, Butcher megvédte a becsületét, amikor a kalózok elrabolták a 'Neptun' Joshua Leadbeatertôl...";
			link.l1.go = "saga_68";
		break;
		
		case "saga_68":
			dialog.text = "Ez is igaz. De jutalmul drágán megfizetett neki. Jessica többször is megmentette annak a söpredéknek a szánalmas életét, felemelve ôt a szögágyból, amelyet rendszeresen rendezett magának a háborgó és heves vérmérséklete miatt. Tulajdonképpen csak neki köszönhette, hogy elérte a virágzó kalóz dicsôségét.";
			link.l1 = "Igen, igen, a 'vörös talizmánja'. hallottam róla. Azt mondják, hogy amint Mészáros kirúgta Jess-t, a szerencséje is ugyanezt tette vele...";
			link.l1.go = "saga_69";
		break;
		
		case "saga_69":
			dialog.text = "De természetesen. Jessica nélkül ô is csak egy közönséges tengeri fosztogató lett, még ha vakmerôen bátor is. De Jessica nem volt mellette, ô volt az, aki segített neki megtervezni minden kockázatos akcióját, és az ô pengéjére mindig számíthatott.\nS persze, Beatrice sem volt egy jó lány, de ô sem érhetett fel Jesshez, Bea bájai egészen mások voltak... Elkövette azt a hibát, hogy kikezdett Mészárossal.";
			link.l1 = "Ezt már hallottam valahol...";
			link.l1.go = "saga_70";
		break;
		
		case "saga_70":
			dialog.text = "Minden kalóz így gondolta, beleértve Blaze Sharpot, a bátyját is. Ki nem állhatta Mészárost... De térjünk vissza Jessicához. Még csak gondolni sem mertem rá, amíg a 'Neptun', volt, soha nem hagyta volna el szeretett kapitányát. De amikor Butcher ilyen aljas módon megszabadult tôle...\nmegérkeztem Barbadosra, és összebarátkoztam vele. Nem volt könnyû neki, imádta a tengert és a veszélyes kalandokat. Az az unalmas kolóniai élet megölte. Ráadásul a 'Neptun' n szolgálata alatt igencsak hírhedt lett a Karib-tengeren, és Bridgetown népe okkal tekintette ôt a Mészáros bûntársának...";
			link.l1 = "De szart sem tudtak bizonyítani...";
			link.l1.go = "saga_71";
		break;
		
		case "saga_71":
			dialog.text = "Nem. De senki sem akart vele semmit kezdeni. Bridgetownban betöltött státusza ellenére elátkozottnak tartották. Azt hiszem, én voltam az egyetlen férfi, aki fél óránál többet töltött ott Jessicával.\nFelajánlottam neki, hogy jöjjön velem a West Mainbe, és kezdjen ott új életet. Azt az életet, amire mindig is vágyott - a tenger, a hajók, az utazások, a kalandok. Addigra már egy nagyszabású mûveletet hoztam létre Blueweldben, és százszor többet tudtam neki ajánlani, mint az a söpredék Mészáros. De Jess nagyon megsérült. Nem bocsátotta meg Butchernek az árulását, és azt, ahogy utána bánt vele. És azt hiszem, még akkor is érzéseket táplált iránta... Minden erôfeszítésem ellenére sem tudtam elfeledtetni vele a múltat, a bosszú gondolatai megszállottan foglalkoztatták.";
			link.l1 = "Igen, nem irigylem ôt. Szegény lány...";
			link.l1.go = "saga_72";
		break;
		
		case "saga_72":
			dialog.text = "Én is így éreztem vele kapcsolatban. Késôbb pedig elkezdte megszeretni az ôsi indiai kultuszokat és rituálékat. Ez azután történt, hogy elfogtak valami indián mágust, és Yucatán dzsungeleibôl' deeps a helyi ültetvényre vitték. Jessica megvásárolta ôt, és házat adott neki az ültetvényén.\nSok idôt töltött a mágussal. Azt mondta, hogy mindezt a mágikus indián rituálék iránti történelmi érdeklôdése miatt. A bridgetowniak aggódni kezdtek, különösen a helyi lelkész. Tulajdonképpen ô volt azon kevesek egyike, aki jó volt Jessicához.\nA pap gyakran beszélt hozzá, gyôzködte, hogy szabaduljon meg a mágustól, veszélyekkel és az inkvizícióval fenyegette, de Jessicát hiába próbálta megijeszteni. Egyik éjjel néhány idegen betört a mágus házába, és meggyilkolta ôt.\nAznap éjjel két férfi megtámadta Jessicát a saját hálószobájában, de nem jártak jól - Bridgetownban senki sem tudta, milyen jól forgatja Jess a lángpengés kardját. Szó szerint szeletekre vágta ôket.";
			link.l1 = "Igen, persze... az a vakmerô viharzsák!";
			link.l1.go = "saga_73";
		break;
		
		case "saga_73":
			dialog.text = "Ezután az egész város félni kezdett tôle. Aztán jött a Maszk. Elég gyorsan egymásra találtak.";
			link.l1 = "Az írások szerint a Maszk Joshua Leadbeater, a 'Neptun'.egykori kapitánya...";
			link.l1.go = "saga_74";
		break;
		
		case "saga_74":
			dialog.text = "Errôl csak sokkal késôbb szereztem tudomást. Egy héttel a Maszk érkezése után Jess összeszedte a holmiját, elbúcsúzott tôlem, és egy katonai fregatton elhajózott ismeretlen irányba. Soha nem tért vissza... ahogy Beatrice sem tért vissza Isla Tesoróra.\nNem sokkal azután, hogy St. John's-ban felakasztották Mészárost, maga a Maszk szállította oda. De csak egy nappal élte túl Mészárost.";
			link.l1 = "Igen... A mi Steven Dodsonunk megmutatta a stílusát...";
			link.l1.go = "saga_75";
		break;
		
		case "saga_75":
			dialog.text = "Igen, ezt mondták nekem. Megbosszulta Beatrice-t... És így végzôdik Jessica története, valahol egy lakatlan szigeten hunyt el, a Mészáros kalózokkal folytatott csetepatéban. Senki sem tudja, hol van ez a hely. Butcher halott, ahogy Jackman és Hangman is.";
			link.l1 = "Ebben tévedsz, Jan. Butcher él.";
			link.l1.go = "saga_76";
		break;
		
		case "saga_76":
			dialog.text = " Micsoda?! Az nem lehet! Felakasztották!";
			link.l1 = "Olvassa el Raymond Baker vallomását. Jobb, mint bármelyik történet.";
			link.l1.go = "saga_77";
		break;
		
		case "saga_77":
			PlaySound("interface\important_item.wav");
			dialog.text = "Mutasd meg, hogy...(olvasás) Hm. Hihetetlen! Kiderült, hogy a kivégzését megrendezték!";
			link.l1 = "Ravasz, mi? De ez még nem minden. Ismered Mészárost. Csak azt nem tudod, hogy most ki ô.";
			link.l1.go = "saga_78";
		break;
		
		case "saga_78":
			dialog.text = "De most már nem tudod, ki ô. És ki ô?";
			link.l1 = "Lawrence Beltrope Port Royalból. A bánya tulajdonosa, az a nagyon titokzatos árnyék, aki Jackman mögött áll. Én Baker révén jöttem rá, Baker pedig a Maszkból tudta meg.";
			link.l1.go = "saga_79";
		break;
		
		case "saga_79":
			dialog.text = "Szent szar! Szóval kiderült, hogy ô az, aki az egészet megszervezte? Nos, rendben... Mi is eljutunk Mészároshoz. Majd elgondolkodom, hogy miként lehet lejutni errôl a rossz penny-rôl. Bár nem lesz könnyû, az angol hatóságok fenntartható védelme alatt áll.";
			link.l1 = "Eljön az ô ideje, Jan. Hamarosan találkozik a hajóskapitánnyal és a szállásmesterrel. Rendben, köszönöm a történetet. Ideje mennem.";
			link.l1.go = "saga_80";
		break;
		
		case "saga_80":
			dialog.text = "Hová tartasz most?";
			link.l1 = "Valami szigetre. Azt hiszem, ez ugyanaz a hely, ahol Jess és Beatrice elhunyt, és ahol a Maszk lecsapott Mészáros-Beltrope-ra. Bizonyítékra van szükségem, hogy Helen a Sharp családhoz tartozik, és remélem, hogy ott ki tudom ásni.";
			link.l1.go = "saga_81";
		break;
		
		case "saga_81":
			dialog.text = "Jól van, rendben. Szóval, "+pchar.name+", sok szerencsét neked. Ha visszajöttél, mesélj a részletekrôl.";
			link.l1 = "Persze. Késôbb találkozunk, Jan!";
			link.l1.go = "saga_81a";
		break;
		
		case "saga_81a":
			DialogExit();
			LAi_SetHuberType(npchar);
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(npchar, "quest.jessika");
			npchar.quest.jessika_peace = "true"; // атрибут на мирное разрешение после боя
		break;
		
		case "saga_82":
			dialog.text = "Nagyszerû munka, "+pchar.name+". Megvalósítottad a lehetetlent. Mi, a Parti Testvérek bárói mindannyian hálásak vagyunk neked.";
			link.l1 = "Igen, a gyôzelemhez vezetô út keskeny volt. Bárcsak tudtam volna elôre, hogy ennyi mindent ki kell állnom...";
			link.l1.go = "saga_83";
		break;
		
		case "saga_83":
			dialog.text = "Hogy van Helen? Mit tervez?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Velem marad a hajón. Ô már nem csak egy egyszerû tiszt többé. A sziget feletti irányítást a Testvériség vezetôje kapja, és ô csak bérleti díjat kap. Helen ezt egyedül döntötte el.";
				link.l1.go = "saga_84";
			}
			else
			{
				link.l1 = "Elindult Isla Tesoróra, hogy a saját kezébe vegye a báróságot.";
				link.l1.go = "saga_85";
			}
		break;
		
		case "saga_84":
			dialog.text = "Nos, "+pchar.name+"... Gratulálok! Sok férfi álmodott már arról, hogy a te cipôdben járjon. Örülök, hogy Helen olyan férfit választott, aki megérdemli ôt. Nálad jobb jelölt nem is lehetne arra, hogy élete párja legyen.";
			link.l1 = "Köszönöm, Jan! Most pedig szeretnék visszatérni a Tortugáról és Levasseurrôl szóló beszélgetésünkhöz.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "Köszönöm, Jan!";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_85":
			dialog.text = "Csodálatos. Megérdemli ezt. Azt hiszem, a Testvériség új vezetôje segíteni fog neki az ügyei intézésében. Ô egy tehetséges és okos fiatal lány, aki gyorsan felzárkózik és bármit megtanul. Köszönöm, "+pchar.name+"! Helen olyan nekem, mintha a lányom lenne, és nagyon örülök, hogy ilyen csodálatos jövô nyílt meg elôtte.";
			link.l1 = "Szívesen, Jan... Mindenesetre szeretnék visszatérni a Tortugáról és Levasseur-rôl szóló beszélgetésünkhöz.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "Szívesen, Jan.";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_86":
			sTemp = "Shark Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = "Amíg távol voltál, "+sTemp+" és én már megbeszéltük a dolgot, és közös véleményre jutottunk Levasseur elidegenítésével kapcsolatban. Vitorlázz el Isla Tesoróra, és beszélj az új vezetônkkel, ô majd elmondja neked a tervünk részleteit, és minden segítséget megad neked, amit csak tud.";
			link.l1 = "Végre érzem a puskapor illatát! Nincs vesztegetni való idônk, elindulok Isla Tesoróra!";
			link.l1.go = "saga_87";
		break;
		
		case "saga_87":
			dialog.text = ""+pchar.name+", Várj egy percet. Van néhány ajándékom számodra a segítségedért Helen és a Testvérek ügyében. Az elsô a távol-keleti szaracénok elvarázsolt amulettje. A varázsa megerôsíti a fegyelmet a hajón, amit én személyesen ellenôriztem. Tessék.";
			link.l1 = "Köszönöm!";
			link.l1.go = "saga_88";
		break;
		
		case "saga_88":
			GiveItem2Character(pchar, "talisman4");
			Log_Info("Megkaptad a 'Janicsár' amulettet.");
			PlaySound("interface\important_item.wav");
			dialog.text = "A második csak egy emléktárgy a múltbeli kalandokból. Meggyôztem a Tanácsot, hogy dobják a szélnek ezt a nevetséges maradványt, a kôdarabok használatát. Már nincs rájuk szükség. Neked adom ôket. Talán valahogyan hasznát veszed majd.";
			link.l1 = "A szilánkok felhasználása? Hm. Nem tudom... de mint szuvenír, nagyon lekötelez!";
			link.l1.go = "saga_89";
		break;
		
		case "saga_89":
			GiveItem2Character(pchar, "splinter_js"); 
			GiveItem2Character(pchar, "splinter_nh"); 
			GiveItem2Character(pchar, "splinter_mt"); 
			GiveItem2Character(pchar, "splinter_zm"); 
			GiveItem2Character(pchar, "splinter_jb"); 
			Log_Info("Kaptál öt díszes mintadarabot");
			dialog.text = "Nos, ne feledkezz meg a barátodról, "+pchar.name+". Ugorj be hozzám, ha Blueweldben horgonyozol. Leülünk és iszunk egy kis rumot. Mindig örülök, ha látlak.";
			link.l1 = "Mindenképpen, Jan. Most már van mire emlékeznünk, nem igaz? Ha-ha! Mindegy, mennem kell.";
			link.l1.go = "saga_90";
		break;
		
		case "saga_90":
			dialog.text = "Sok sikert, "+pchar.name+"!";
			link.l1 = "Viszlát...";
			link.l1.go = "saga_91";
		break;
		
		case "saga_91":
			DialogExit();
			pchar.questTemp.Saga = "end";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock")) AddQuestRecord("Saga", "26_1");
			else 
			{
				AddQuestRecord("Saga", "26");
				pchar.questTemp.Terrapin = "islatesoro";
			}
			CloseQuestHeader("Saga");
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
	// --> провалы Саги
		case "saga_f_1":
			dialog.text = "Igen... Úgy tûnik, hogy a tervünk összeomlott. Most már nem tudjuk azt tenni, akit akartunk a Testvériség élére. Jackman halott, ez szép és jó. De sajnos, a tervem most nem fog mûködni. A szokásos módon kell megválasztanunk a Testvériség vezetôjét, és Isten tudja, milyen fordulatot fog ez venni...";
			link.l1 = "Ez sajnálatos. Nagyon sajnálatos. És úgy tûnik, Helen az öröksége nélkül marad.";
			link.l1.go = "saga_f_2";
		break;
		
		case "saga_f_2":
			dialog.text = "Igen, "+pchar.name+". És szeretnék segíteni neked Tortuga elfoglalásában, tényleg szeretnék, de most már nem is tudom, hogyan. Valószínûleg semmit sem tudok tenni, hogy segítsek. Úgy néz ki, hogy csak a saját erôdre és a harci képességedre kell támaszkodnod.";
			link.l1 = "Úgy tûnik, nem maradt más lehetôség... Rendben, Jan, megyek és átgondolom, mit tegyek. Késôbb találkozunk...";
			link.l1.go = "saga_f_3";
		break;
		
		case "saga_f_3":
			dialog.text = "Ugorj be, "+pchar.name+". Mindig örülök, ha látlak.";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			CloseQuestHeader("Testament");
		break;
		
		case "saga_l1": // проход первый - отбираем Элен и закрываем вход к Свенсону
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l1";
			pchar.quest.Saga_Late_1.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_1.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_1.function = "Saga_HelenaTalk";
			pchar.questTemp.Saga.Jackman = "true";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
		break;
		
		case "saga_l2": // проход второй - отбираем Элен, Натана и Данни в Марун-Таун, чистим квестовый лут
			dialog.text = "De sajnos már túl késô bármit is tenni. Isla Tesoro hivatalosan is az angol korona fennhatósága alá került. Most már van ott egy helyôrség. Ez súlyos csapás a Testvéreknek, amit, attól tartok, nem fogunk tudni kiheverni.";
			link.l1 = "Milyen szörnyû... Ah, gyorsabban kellett volna cselekednem. Akkor, látod, minden rendben lett volna. Rendben, Jan, megyek és átgondolom, mit tegyek. Késôbb találkozunk...";
			link.l1.go = "saga_l2_1";
		break;
		
		case "saga_l2_1":
			dialog.text = "Ugorj be, "+pchar.name+". Mindig örülök, ha látlak.";
			link.l1 = "...";
			link.l1.go = "saga_l2_2";
		break;
		
		case "saga_l2_2":
			DialogExit();
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "letter_parol", 1);
			RemoveItems(pchar, "map_sharp_full", 1);
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l2";
			pchar.quest.Saga_Late_2.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_2.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_2.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
		
		case "saga_l3":
			dialog.text = "Igen... Tényleg csak elszenvedtünk egy kemény vereséget. És a legrosszabb az egészben, hogy szó szerint egy lépésre voltunk a gyôzelemtôl. Caramba! Hogy történhetett ez, huh, "+pchar.name+"? Olyan keményen próbálkoztatok, olyan sokat tettetek, és... ekkora pech!";
			link.l1 = "Én vagyok a hülye, aki ezért felelôs. Gyorsabbnak kellett volna lennem. És hála nekem, Helen el fogja veszíteni az örökségét. És a Tortuga terv soha nem fog megvalósulni.";
			link.l1.go = "saga_f_2";
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
	// <-- провалы Саги
		
	//-----------------------------------генератор торговли бакаутом--------------------------------------------
		case "trade_bakaut":
			if (CheckAttribute(pchar, "questTemp.UpgradeBakaut"))
			{
				dialog.text = "Rendben, nem bánom. Van 125 darab a raktáramban. Az ár, ahogy emlékszik, 3150 darabonként.";
				if (PCharDublonsTotal() >= 3150)
				{
					link.l1 = "Rendben, megegyeztünk. Tessék, tessék. Itt van 3150 dublon.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "Ez aztán a rohadt szerencse. A hajón felejtettem a pénzem. Mindjárt hozom.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Rendben, nem bánom. Van huszonöt egység a raktáramban. Az ár, mint emlékszel, harminc dublon darabonként.";
				if (PCharDublonsTotal() >= 750)
				{
					link.l1 = "Rendben, megegyeztünk. Tessék, tessék. Itt van hétszázötven dublon.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "Ez aztán a rohadt szerencse. A hajón felejtettem a pénzem. Mindjárt hozom.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && !CheckAttribute(pchar, "questTemp.SvensonBakautBlock")) // увеличить объём поставок бакаута
			{
				link.l4 = "Jan, lehetséges lenne növelni a vasfa szállítmányok méretét?";
				link.l4.go = "UpgradeBakaut";
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && CheckAttribute(pchar, "questTemp.SvensonBakautPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок бакаута, если в первый раз не принесли
			{
				link.l4 = "Jan, összegyûjtöttem háromezer aranyat. Tessék, ezt az ajándékot átadhatod az élôsködôinknek. Gondolom, ma boldog napjuk lesz.";
				link.l4.go = "UpgradeBakaut_Agreed";
			}
		break;
		
		case "trade_bakaut_1":
			RemoveDublonsFromPCharTotal(750);
			Log_Info("750 dublont adtál.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Dicséretes. Megparancsolom az embereimnek, hogy vigyék át a vasfát a hajójára.";
			link.l1 = "Köszönöm!";
			link.l1.go = "trade_bakaut_2";
		break;
		
		case "trade_bakaut_2":
			dialog.text = "Ha többet akarsz venni, gyere vissza két hét múlva. Addigra összeállítok egy újabb adagot.";
			link.l1 = "Rendben, Jan. Viszlát legközelebb!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SANDAL, 25);
			DeleteAttribute(npchar, "quest.trade_bakaut");
			SetFunctionTimerCondition("Bakaut_SvensonAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "UpgradeBakaut": //
			if (startHeroType == 1) sStr = "öreg barátom.";
			if (startHeroType == 2) sStr = "öreg barátom.";
			if (startHeroType == 3) sStr = "öreg barátom.";
			if (startHeroType == 4) sStr = "Helen";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Örülök, hogy megkedvelted a vasfát, " + sStr + ". A szállítmányok növelése nem probléma, de van egy bökkenô, ahogy érted. A nagyobb mennyiséggel együtt jár egy olyan nyomvonal, ami nem kívánt figyelmet kelthet, különösen az angol hatóságok részérôl. De ha megbízható kezeket, megbízható füleket és olyan embereket adunk hozzá a rezidencián, akik segítenek nekünk az árnyékban maradni, minden megoldható. Bár nem lesz olcsó - háromezer dublont, hogy megkerüljük a város kincstárát és Anglia igényeit. Akkor én ötször ennyivel többet tudok neked adni. Mit szólsz hozzá?";
				link.l1 = "Háromezer dublont? Jan, ez rablás! Nem tudnánk kevesebb kiadással is boldogulni? Talán van rá mód, hogy ilyen mesés összegek nélkül rendezzük az ügyet?";
				link.l1.go = "UpgradeBakaut_1";
				Notification_Skill(true, 60, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Jó ötlet, de azt kell mondanom, hogy a kereskedelmi ügyek ilyen volumenéhez egy kicsit több tapasztalatra és ügyességre van szükség. Ha sietsz, több a kockázat, mint a haszon. Csináljuk így: szerezzünk még egy kis tapasztalatot, és ha készen állsz a nagyobb tételekre, gyere vissza. Akkor majd mindent megbeszélünk rendesen.";
				link.l1 = "Hmm... Rendben. Térjünk vissza erre a beszélgetésre késôbb.";
				link.l1.go = "exit";
				notification("Képességpróba Sikertelen (80)", SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeBakaut_1":
			dialog.text = "Sajnos, "+pchar.name+", ez a béke ára manapság - a parókás és egyenruhás urak étvágya napról napra nô. Semmi sem csábítja ôket jobban, mint a mellkasukban csilingelô dublónok. Tizenöt százalék kedvezményt garantálok minden további szállítmányra, ha ez megnyugtatja.";
			link.l1 = "A fenébe velük! Ilyen összegeket kérni! Ilyen kapzsisággal királyokat' kincseket kellene venniük, nem pedig csendre alkudozniuk! Jan, talán meg kéne... mutatnunk nekik, hogy ki az igazi hatalom a szigetvilágban, nem?";
			link.l1.go = "UpgradeBakaut_2";
		break;
		
		case "UpgradeBakaut_2":
			if (startHeroType == 1) sStr = "barátom.";
			if (startHeroType == 2) sStr = "barátom.";
			if (startHeroType == 3) sStr = "barátom.";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "Ha! Micsoda szellem van benned, " + sStr + "! De egész Anglia ellen menni most nem érdekel, és már nem vagyok olyan fiatal, mint régen. Fizessük ki ezeket a vérszívókat, és hagyjuk ôket csendben ülni - nekünk dolgunk van. Gyûjtsük össze a szükséges összeget, és szabad lesz az utunk, felesleges kérdések nélkül!";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Nos, rendben, Jan, meggyôztél. Legyen így, hiszen nincs más megoldás. Itt van a háromezer dublonod. Csak ne feledd: nem szándékozom örökké etetni ezeket a nyomorultakat.";
				link.l1.go = "UpgradeBakaut_Agreed";
			}
			link.l2 = "Az ördög vigye ôket, Jan! Tényleg azt hiszed, hogy nincs más kiút? Jól van, rendben. Megkeresem ezeket a dublonokat. De most nincs annyi pénzem.";
			link.l2.go = "UpgradeBakaut_4";
			link.l3 = "A fenébe is, Jan, tényleg azt akarod, hogy etessem ezeket a hivatalnokokat a kényeztetett hölgyeikkel? Ülnek a székükben, nem csinálnak semmit, és csak pénzt követelnek! Nem, ez nekem nem tetszik! Nem fogom a verejtékemmel és a véremmel tömni a zsebüket! Térjünk vissza az elôzô kifejezésekhez. Nekem ennyi elég lesz.";
			link.l3.go = "UpgradeBakaut_3";
		break;
		
		case "UpgradeBakaut_Agreed":
			dialog.text = "Ez már sokkal jobban tetszik! A te hozzájárulásoddal az üzletünk zökkenômentesen fog mûködni, és ezek a nyomorultak megkapják, ami jár nekik - és már nem is néznek a vasfa irányába. Biztosíthatlak, hamarosan százszorosan megtérül minden befektetésünk.";
			link.l1 = "Remélem, Jan, remélem, remélem.";
			link.l1.go = "UpgradeBakaut_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "1_1");
			pchar.questTemp.UpgradeBakaut = true;
			pchar.questTemp.SvensonBakautBlock = true;
			DeleteAttribute(pchar, "questTemp.SvensonBakautPotom");
		break;
		
		case "UpgradeBakaut_Agreed_1":
			dialog.text = "Az üzlet úgy fog menni, ahogy kell, nem kell aggódnod. És most, ami a jövôbeni üzleteket illeti: Minden hónap 14-én és 28-án 125 rönk vasfát tartok készenlétben, ahogy eddig is. Az egész szállítmányt 3150 dublonnáért viheti el.";
			link.l1 = "Ezek a beszélgetések sokkal jobban tetszenek! Akkor százhuszonöt rönk? Kitûnô, Jan. Nos, hamarosan találkozunk, várom a szállítmányt!";
			link.l1.go = "exit";
		break;
		
		case "UpgradeBakaut_3":
			if (startHeroType == 1) sStr = "öreg barátom.";
			if (startHeroType == 2) sStr = "öreg barátom.";
			if (startHeroType == 3) sStr = "öreg barátom.";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "Ahogy kívánja, " + sStr + ". És ne izgasd fel magad annyira. Ez a világ már csak így van elrendezve.";
			link.l1 = "Igen, Jan, tudom, hogy van ez a világ. De ez nem jelenti azt, hogy el kell tûrnöm. Rendben, mennem kell.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
		break;
		
		case "UpgradeBakaut_4":
			dialog.text = "Megvárom, amíg összegyûjti a pénzt. Tudom, hogy megtalálod a módját. Amint készen állsz - várlak a pénzzel, és folytatjuk.";
			link.l1 = "Rendben.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
			pchar.questTemp.SvensonBakautPotom = true;
		break;
		// <-- генератор бакаута
		
	//----------------------------------- штурм рудника --------------------------------------------
		case "mine_attack":
			dialog.text = "Örülök, hogy látlak, "+pchar.name+". Az embereim készen állnak. Elmegyünk a Selva-ba?";
			link.l1 = "Igen, Jan. A csapatom készen áll a csatára.";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			dialog.text = "Akkor induljunk. Az akna a dzsungel mélyén van, pont ezen az ösvényen. Maradjatok az elágazásnál. Gyerünk!";
			link.l1 = "Elôre!";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_attack_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("shore53", "boat", true);
			LocatorReloadEnterDisable("mine_03", "reload3_back", true);
			LocatorReloadEnterDisable("mine_02", "reload3_back", true);
			pchar.quest.Saga_MineAttack_01.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_01.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_01.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_3":
			dialog.text = "Tehát, "+pchar.name+", itt az ideje, hogy megbeszéljük, hogyan fogjuk végrehajtani ezt a mûveletet. Már elôre kiküldtem néhány miskitó indiánt, hogy mérjék fel a területet, és a megfigyeléseik alapján összeállítottam egy akciótervet.";
			link.l1 = "Tájékoztassanak!";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "A gödör a dzsungelben lévô hegyek alatti bányát jelképezi. A bánya bejáratához közel van egy tábor. Néhány ház és egy palánk. A palánkhoz egy ösvény vezet. Nézzétek, egy kis, tisztásnyira innen a dzsungelben lévô kis helyre vezet. Ott található a bánya fôbejárata\nEz egy magas kôfalat jelent két meredek domb között, amely megakadályozza, hogy bárki besurranjon. A kapukat hatfôs ôrség védi. Nem nagy dolog, de két ágyút is felállítottak oda. Ez a legnagyobb probléma.\nKét sortûznyi grapeshot a csapatunk felét leterítheti, ami katasztrófa lenne, így a frontális támadás nem opció...";
			link.l1 = "Ha! De van egy aduászunk, tudjuk a jelszót, amivel bejuthatunk...";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			dialog.text = "Így van. Ezt majd kihasználjuk, de most hadd ismertessem meg veletek a teljes tervemet a végéig.";
			link.l1 = "Persze, Jan. Csupa fül vagyok.";
			link.l1.go = "mine_attack_6";
		break;
		
		case "mine_attack_6":
			dialog.text = "Van egy másik bejárat is a gödörbe - azon az ösvényen keresztül a dzsungelben. Ez megkerüli a bányát védô dombokat, és egy kis keskeny üregbe vezet, amelyen keresztül be lehet jutni. De a banditák magas kerítést emeltek és ôröket állítottak oda. A kerítésnek kis kapui vannak, de a másik oldalról el vannak barikádozva.\nNost figyeljetek, mit fogunk csinálni. Megszabadulunk azoktól, akik a bánya második bejáratát ôrzik. Az osztagunk egy része ott marad, és keres valami fatörzset, amit faltörônek használhatunk.\nMajd visszatérünk a fôbejárathoz, és megöljük az ágyúsokat. A nálunk lévô jelszó kétszeresen is segíteni fog nekünk. Ezután két oldalról támadjuk meg az aknát. Én vezetem az elsô rohamosztagot, te pedig a másodikat.";
			link.l1 = "Nos, ez logikus. Két fronton fogunk harcolni ellenük. Gyerünk!";
			link.l1.go = "mine_attack_7";
		break;
		
		case "mine_attack_7":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.quest.mine01 = "true";
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_02.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_02.win_condition.l1.location = "Mine_04";
			pchar.quest.Saga_MineAttack_02.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_8":
			dialog.text = "Rendben, itt vagyunk... Ez az út a bandita kerítéshez vezet. Most el kell döntenünk, hogyan bánjunk el velük. Ha az egész osztagot odaküldjük, az túl gyanús lesz, és riadót fognak fújni.\nEgy kis, háromfôs csoportot kell küldenünk, nem többet, ez a csapat elég közel tud majd kerülni anélkül, hogy gyanút keltene, és meglepetésszerûen támadhat. Én nem vezethetem a csoportot, az arcom túl ismert errefelé.\nSzóval rajtad múlik, "+pchar.name+", mert te vagy az egyetlen, akire rábízhatom a parancsnokságot anélkül, hogy kockáztatnám az egész akciót. Megadom neked Gregoryt és egy muskétást, hogy segítsenek...";
			link.l1 = "Hány ôr van a kerítésnél?";
			link.l1.go = "mine_attack_9";
		break;
		
		case "mine_attack_9":
			dialog.text = "Négyen. Két muskétás és két katona.";
			link.l1 = "Elvisszük ôket...";
			link.l1.go = "mine_attack_10";
		break;
		
		case "mine_attack_10":
			dialog.text = "Ismerve téged, egy pillanatig sem kételkedem ebben. Menj oda hozzájuk, és mondd meg nekik, hogy Jackman küldött. Mondd meg nekik a jelszót. És miután megnyugodtak... cselekedj a körülményeknek megfelelôen.";
			link.l1 = "Rendben. Legyenek résen.";
			link.l1.go = "mine_attack_11";
		break;
		
		case "mine_attack_11":
			dialog.text = "Sok sikert, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "mine_attack_12";
		break;
		
		case "mine_attack_12":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 2)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 12)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				LAi_CharacterDisableDialog(sld);//запрет диалога
			}
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(npchar, "quest.mine01");
			npchar.quest.mine02 = "true";
			pchar.questTemp.Saga.MineAttack = "true";
			pchar.quest.Saga_MineAttack_03.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_03.win_condition.l1.location = "Mine_01";
			pchar.quest.Saga_MineAttack_03.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_13":
			dialog.text = "Nagyszerû munka, "+pchar.name+"! Mint mindig, most is a csúcsra jutottál. Most a fiaim felkészülnek arra, hogy vihart indítsanak a bánya ezen oldaláról, mi pedig megtisztítjuk a fôbejáratot.";
			link.l1 = "Gondolom, megint az ôrökhöz kell sétálnom?";
			if (GetCharacterIndex("Svensons_off_2") != -1 && GetCharacterIndex("Svensons_sold_12") != -1) link.l1.go = "mine_attack_14";
			else link.l1.go = "mine_attack_14a";
		break;
		
		case "mine_attack_14a":
			dialog.text = "Igen, "+pchar.name+", még egyszer. Szívesen mennék én is, de biztosan felismernének, és az egész mûvelet felborulna. Veszélyesebb lesz, mivel több az ellenség, és ne feledkezzünk meg a fegyverekrôl sem.";
			link.l1 = "A tisztjeimet is magammal viszem.";
			link.l1.go = "mine_attack_14_1";
		break;
		
		case "mine_attack_14":
			dialog.text = "Igen, "+pchar.name+", még egyszer. Szívesen mennék én is, de biztosan felismernének, és az egész mûvelet felborulna. Veszélyesebb lesz, mivel több az ellenség, és ne feledkezzünk meg a fegyverekrôl sem. Kit fogsz magaddal vinni, hogy segítsen neked? A tisztjeidet vagy Gregoryt és a muskétást, mint legutóbb?";
			link.l1 = "A tisztjeimet viszem.";
			link.l1.go = "mine_attack_14_1";
			link.l2 = "Én Gergelyt és a muskétást viszem.";
			link.l2.go = "mine_attack_14_2";
		break;
		
		case "mine_attack_14_1":
			dialog.text = "Rendben. A saját embereid a legjobb erôsítés. Most pedig visszamegyünk a fôbejárathoz. Emlékszel az útra?";
			link.l1 = "Persze, hogy emlékszem. Vissza arra, amerre jöttünk, aztán balra, majd a dombot megkerülô ösvényen.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "officer";
		break;
		
		case "mine_attack_14_2":
			dialog.text = "Rendben. Egyszer már sikerült megcsinálnod, úgyhogy másodszorra már gyerekjáték lesz. Most visszamegyünk a fôbejárathoz. Emlékszel az útra?";
			link.l1 = "Persze, hogy emlékszem. Vissza arra, amerre jöttünk, aztán balra, és a dombot megkerülô ösvényen.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "soldiers";
		break;
		
		case "mine_attack_15":
			dialog.text = "Nincs vesztegetni való idônk. Menjünk!";
			link.l1 = "Elôre!";
			link.l1.go = "mine_attack_16";
		break;
		
		case "mine_attack_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 12) LAi_ActorFollowEverywhere(sld, "", -1);
				else LAi_ActorRunToLocation(sld, "reload", "reload3_back", "mine_01", "goto", "goto"+i, "", 5);
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			if (pchar.questTemp.Saga.MineAttack == "soldiers") LAi_LocationDisableOfficersGen("mine_exit", true);//офицеров не пускать
			LocatorReloadEnterDisable("mine_03", "reload3_back", false);
			LocatorReloadEnterDisable("mine_02", "reload3_back", false);
			DeleteAttribute(npchar, "quest.mine02");
			npchar.quest.mine03 = "true";
			pchar.quest.Saga_MineAttack_05.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_05.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_05.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_17":
			dialog.text = "Rendben, "+pchar.name+", figyeljetek az utolsó utasításokra. Ezek a kapukat ôrzô ördögök kemények, így nem lesz könnyû dolgod. A fô célod, hogy megöld a kapuk mellett álló ágyúsokat, mert ha még lélegzik, akkor nem tudunk majd segíteni neked.\nHa mindketten halottak, és nincs esély az ágyúlövésre, akkor mindannyian jövünk, és pillanatok alatt megöljük ôket. Megértetted, "+pchar.name+"? Ne játszd a hôst, öld meg az ágyúsokat, a többit hagyd ránk.";
			link.l1 = "Rendben, Jan. Megpróbálok mindent úgy csinálni, ahogy terveztük. És ha valami rosszul sül el, akkor majd a fülemmel játszom.";
			link.l1.go = "mine_attack_18";
		break;
		
		case "mine_attack_18":
			dialog.text = "Jól hangzik. Isten legyen veled!";
			link.l1 = "Köszönjük...";
			link.l1.go = "mine_attack_19";
		break;
		
		case "mine_attack_19":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 2)
					{
						LAi_SetActorType(sld);
						LAi_ActorFollowEverywhere(sld, "", -1);
					}
					else LAi_SetStayTypeNoGroup(sld);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			DeleteAttribute(npchar, "quest.mine03");
			pchar.quest.Saga_MineAttack_06.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_06.win_condition.l1.location = "Mine_exit";
			pchar.quest.Saga_MineAttack_06.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_20":
			dialog.text = "Fúúú! Lenyírtuk azokat a rohadékokat... Élelmes kis gorillák voltak. Elmondhatom, hogy ezek a zsoldosok a reguláris csapatokban szolgáltak. Nagy zajt csaptunk itt, attól tartok, hogy meghallottak minket. Egy percet se vesztegessünk! "+pchar.name+", itt az ideje, hogy megtámadjuk a bányát.\nvisszatérek a csoportomhoz a második bejáratnál - már biztosan találtak és elôkészítettek egy farönköt, amivel megdönthetik a kerítést. Te és az embereid a központi kapun át fogtok menni. Várjatok ránk fél órát, ne támadjatok azonnal...";
			link.l1 = "Jan, ha hallották a tüzelést a bányánál, akkor nincs fél óránk. Azok a banditák felállíthatnak egy védelmi vonalat, vagy valószínûleg egyenesen a központi kapuhoz jönnek, és mindenükkel megtámadhatják a csoportomat...";
			link.l1.go = "mine_attack_21";
		break;
		
		case "mine_attack_21":
			dialog.text = "Bassza meg! Ez nagyon is lehetséges. Mit javasolsz, mit tegyünk?";
			link.l1 = "Hm... Ha! Van egy ötletem! Ágyúk! Nézzetek körül. Nem csak grapeshot, hanem bombák is találhatók! Most már ezeknek a banditáknak vége! Miért nem gondoltam erre korábban?!";
			link.l1.go = "mine_attack_22";
		break;
		
		case "mine_attack_22":
			dialog.text = "Mit gondolsz, mit kellene tennünk?";
			link.l1 = "Elviszünk egy ágyút. Azzal sokkal gyorsabban és hatékonyabban tudunk majd mozogni. Befelé gurítjuk, a kapukon túlra, a bányához, és a helyére állítjuk. Ha ôk maguk is támadásba lendülnek, akkor nagy robaj lesz, ha pedig hátradôlnek, akkor mi csak a táborukat bombázzuk. Meg tudod mondani, hogy pontosan hol van a tábor a kapuk mögött?";
			link.l1.go = "mine_attack_23";
		break;
		
		case "mine_attack_23":
			dialog.text = "A tábor alacsonyan van egy hegy mellett. Van egy ösvény közvetlenül a kapukon túl, ami lefelé vezet, és a hegy körül kanyarog. A tábor közvetlenül a domb mögött van.";
			link.l1 = "Pompás! Felállunk az ösvény tetején, és a dombon át kilövünk néhány bombát a fészkükbe! Ó, majd táncra perdülnek körülöttünk!";
			link.l1.go = "mine_attack_24";
		break;
		
		case "mine_attack_24":
			dialog.text = "Az istenit, "+pchar.name+", jól csináltad! Minden sebességgel elôre! Randolfot a te parancsnokságod alatt hagyom, ô a legjobb ágyútüzérem. Tedd ôt a lövészeddé, és nem fog cserbenhagyni. Én most azonnal indulok az egységemhez.";
			link.l1 = "Rendben. Fél órán át pokolian fogom bombázni az állásaikat, amíg át nem törik a kapukat.";
			link.l1.go = "mine_attack_25";
		break;
		
		case "mine_attack_25":
			dialog.text = "Megpróbálok idôben odaérni. Találkozunk a táborban!";
			link.l1 = "Megegyeztünk... Osztag! Hallgassatok a parancsomra! Készüljetek fel az ágyú áthelyezésére! Vigyetek magatokkal puskaport, bombákat és grapeshotot! A bányába a kapukon keresztül. Elôre menet!";
			link.l1.go = "mine_attack_26";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 5);
			if (GetCharacterIndex("Svensons_off_2") != -1)
			{
				sld = characterFromId("Svensons_off_2");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 5);
			}
		break;
		
		case "mine_attack_26":
			DialogExit();
			int n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "mine_bandits");
			LocatorReloadEnterDisable("mine_exit", "reload1_back", false);
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.location = "Mine";
			pchar.quest.Saga_MineAttack_07.function = "Saga_MineGunAttack";
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine_exit", "reload2_back", true);
			LAi_LocationDisableOfficersGen("mine_exit", false); // офицеров пускать
			n = Findlocation("mine");
			locations[n].models.always.Gun = "mortair";
			Locations[n].models.always.Gun.locator.group = "goto";
			Locations[n].models.always.Gun.locator.name = "fire"; // орудие - к бою!
			Locations[n].hidden_sound = true;
		break;
		
		case "mine_attack_27":
			dialog.text = "Hú, nem késtünk el, "+pchar.name+"?";
			link.l1 = "Jan, szent szar! Mi tartott ilyen sokáig? Az osztagom most kapott egy hatalmas csapást!";
			link.l1.go = "mine_attack_28";
		break;
		
		case "mine_attack_28":
			dialog.text = "Az a kibaszott fakerítés nagyon erôsnek bizonyult. Erôvel törtük át... Hallottuk a dübörgésedet. Úgy tûnik, szépen kitakarítottátok ezt a helyet! A földig ég!";
			link.l1 = "Randolf tettei... Bárcsak láthattad volna, hány fattyút temettünk el, mielôtt végre közelharcba bocsátkoztunk!";
			link.l1.go = "mine_attack_29";
		break;
		
		case "mine_attack_29":
			dialog.text = "Caramba! Le a kalappal elôtted, "+pchar.name+". Szép munka! Nos, ami a veszteségeket illeti... mindig vannak, amikor háborúban vagy.";
			link.l1 = "Most már csak a bányát kell feltakarítanunk. Lehetséges, hogy néhány túlélô rejtôzik ott.";
			link.l1.go = "mine_attack_30";
		break;
		
		case "mine_attack_30":
			dialog.text = "Menjünk csak mi ketten. Vizsgáljuk meg a helyzetet.";
			link.l1 = "Jól hangzik!";
			link.l1.go = "mine_attack_31";
		break;
		
		case "mine_attack_31":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, "");
			TakeNItems(npchar, "potion2", 8); 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "Mine_mines", "reload", "reload1", "", -1);
			LAi_LocationDisableOfficersGen("Mine_mines", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_08.win_condition.l1 = "locator";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.location = "mine";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator_group = "reload";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator = "reload4";
			pchar.quest.Saga_MineAttack_08.function = "Saga_MineAttackMines";
		break;
		
		case "mine_attack_32a":
			dialog.text = "Még nem kutattuk át az egész bányát! Garantálom neked, hogy még több ilyen gazember rejtôzik itt!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_32a";
		break;
		
		case "mine_attack_32":
			dialog.text = "Nem hiszem, hogy maradt még egy szemétláda...";
			link.l1 = "Jan, azt hittem, hogy csak azért jöttünk ide, hogy feltérképezzük a helyzetet...";
			link.l1.go = "mine_attack_33";
		break;
		
		case "mine_attack_33":
			dialog.text = "Ha-ha, nos, nem mondtam neked, hogy ez egy különleges felfedezés lesz, egy véres felfedezés... Ilyen bemelegítésre már rég nem volt alkalmam! Most már mindenki biztos lehet benne, hogy egyetlen szemétláda sem szökött meg ebbôl a bányából!";
			link.l1 = "És most mihez kezdünk, Jan?";
			link.l1.go = "mine_attack_34";
		break;
		
		case "mine_attack_34":
			dialog.text = "Hogy érted, hogy mit fogunk csinálni? Aranyat és ezüstöt fogunk keresni. Nem hiszem, hogy Jackman unalomûzésbôl tartott itt ilyen bástyát. Egy egész helyôrséget helyezett ide. Láttad a rabszolgákat a bányában? Meg kellene kérdezned, hogy hol tárolják a kivonatok.";
			link.l1 = "Rendben. Rendben. Akkor te menj és kérdezd ki a rabszolgákat, én pedig felmászom és átkutatom a tábor összes házát, hátha találok valamit.";
			link.l1.go = "mine_attack_35";
		break;
		
		case "mine_attack_35":
			dialog.text = "Megvagy! Ideje indulni!";
			link.l1 = "...";
			link.l1.go = "mine_attack_36";
		break;
		
		case "mine_attack_36":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine", "reload1", true);
			LocatorReloadEnterDisable("mine", "reload6", true);//закрыть выходы с рудника
			pchar.quest.Saga_Mine_letter.win_condition.l1 = "item";
			pchar.quest.Saga_Mine_letter.win_condition.l1.item = "letter_mine";
			pchar.quest.Saga_Mine_letter.function = "Saga_FindMineLetter";
			NextDiag.CurrentNode = "mine_attack_36a";
		break;
		
		case "mine_attack_36a":
			dialog.text = "Gyerünk, haver. És fordítsátok ki ezeket a szánalmas viskókat!";
			link.l1 = "Máris indulok!";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_36a";
		break;
		
		case "mine_attack_37":
			dialog.text = "Ha-ha! "+pchar.name+", nagyszerû, hogy önként jelentkeztél, hogy eljössz velem feltépni ezt a bányát! Ez egy újabb egyértelmû jele annak, hogy szerencsés csillagzat alatt születtél.";
			link.l1 = "Találtál már aranyat?";
			link.l1.go = "mine_attack_38";
		break;
		
		case "mine_attack_38":
			dialog.text = "Igen, a fenébe is! Nem arany, hanem ezüst, egy jó nagy halom. Egy nap múlva már elszállították volna a táborból. Ezért volt itt annyi gengszter - ôk voltak a kísérôcsapat.\nHála neked, idôben ideértünk, nélküled még mindig gyûjtenék embereket. Gratulálok partner!";
			link.l1 = "Ha! Értem... Mennyi ezüstünk van?";
			link.l1.go = "mine_attack_39";
		break;
		
		case "mine_attack_39":
			dialog.text = "Körülbelül négyezer egységünk van. Két részre osztjuk - fele nekem, fele neked, ahogy megbeszéltük.";
			link.l1 = "Kiváló! Egy rakás pénzt kaphatunk ezért a cuccért!";
			link.l1.go = "mine_attack_40";
		break;
		
		case "mine_attack_40":
			dialog.text = "Az biztos... Találtál valami értékeset?";
			link.l1 = "Nem. Egyetlen dublont sem találtunk ezekben a viskókban. Bár találtam néhány papírt. Elolvastam ôket, és megtudtam, hogy a bánya tulajdonosa egy bizonyos Lawrence Beltrope Port Royalból.";
			link.l1.go = "mine_attack_41";
		break;
		
		case "mine_attack_41":
			dialog.text = "Ó, tényleg? Hadd lássam azokat az iratokat...";
			link.l1 = "Tessék, tessék.";
			link.l1.go = "mine_attack_42";
		break;
		
		case "mine_attack_42":
			RemoveItems(pchar, "letter_mine", 1);
			dialog.text = "(olvasás)... Jól van... Beltrope? Ezt a vezetéknevet ismerem valahonnan. Ó, igen! Thomas Beltrope! Ez érdekes... Rendben, utánanézek, ha visszatérek Blueweldbe. Ezeket az iratokat magamnál tartom, ha nem bánja.";
			link.l1 = "Egyáltalán nem. Nincs szükségem rájuk.";
			link.l1.go = "mine_attack_43";
		break;
		
		case "mine_attack_43":
			dialog.text = "Jól van. Most már csak a legjobb rész van hátra, elszállítom az ezüstöt a hajókra. A Miskitók segítenek majd nekünk ebben. Összeállítunk egy szekeret... Addig te csak menj elôre és pihenj egy kicsit, "+pchar.name+". Jobban megérdemelted, mint bárki más!";
			link.l1 = "Köszönöm, Jan. Tábort verünk azon a dombon, túl sok a hamuzsírszag. Ja, és el kell oltani a tüzet ezeken a viskókon, ki tudja, talán még jól jöhetnek nekünk valamikor a jövôben...";
			link.l1.go = "mine_attack_44";
		break;
		
		case "mine_attack_44":
			dialog.text = "A bánya igénybevételén gondolkodik? Ha-ha! Már gondolkodtam az ötleten, de a fosztogatás egy dolog, a tulajdonba vétel egy másik. Barátom, már van gazdája. Lehet, hogy bajba kerülünk az angol hatóságokkal.\nMellesleg a rabszolgák, akikkel beszéltem, azt mondták, hogy az összes itteni ér alapvetôen elfogyott - nagy tétel ezüstöt már többször elszállítottak innen. Attól tartok, ennek a bányának vége.";
			link.l1 = "Hm... majd meglátjuk. Talán nem minden kimerült. Rendben, tényleg pihennem kellene egy kicsit. Késôbb találkozunk, Jan.";
			link.l1.go = "mine_attack_45";
		break;
		
		case "mine_attack_45":
			dialog.text = "Menj csak. És ne aggódj semmi miatt. Minden másról magunk gondoskodunk.";
			link.l1 = "...";
			link.l1.go = "mine_attack_46";
		break;
		
		case "mine_attack_46":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "attack1", "Saga_MineWaitTime", -1);
			n = Findlocation("mine");
			DeleteAttribute(&locations[n], "hidden_sound");
			DeleteAttribute(&locations[n], "hidden_fire");
			n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "models.always.Gun1");
		break;
		
		case "mine_attack_47":
			dialog.text = "Jól kipihentem magam, "+pchar.name+"?";
			link.l1 = "Nem volt rossz... Bár, ôszintén szólva, ölni tudnék, hogy találjak egy kocsmát, igyak egyet, és aludjak egy tiszta ágyban.";
			link.l1.go = "mine_attack_48";
		break;
		
		case "mine_attack_48":
			dialog.text = "Az indiánok leszállították az ezüstöt a partra, és a tisztjeim' felügyelete alatt felpakolják a hajójukra. Már indulhatnak is vissza. A rumra, a kocsmára és az ágyra vonatkozó kívánságod hamarosan teljesül. És szeretném, ha öt nap múlva benéznél hozzám, még sok dolgunk van.";
			link.l1 = "Rendben, Jan, öt nap múlva találkozunk Blueweldben! Sok szerencsét!";
			link.l1.go = "mine_attack_49";
		break;
		
		case "mine_attack_49":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4", "none", "", "", "", 15.0);
			LocatorReloadEnterDisable("shore53", "boat", false);
			LocatorReloadEnterDisable("mine", "reload1", false);
			LocatorReloadEnterDisable("mine", "reload6", false);
			LocatorReloadEnterDisable("mine_01", "reload3_back", false);
			LocatorReloadEnterDisable("mine_exit", "reload2_back", false); //открыть выходы с рудника
			LAi_LocationDisableOfficersGen("mine_mines", false); // офицеров пускать
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			SetFunctionTimerCondition("Saga_ReturnFromMine", 0, 0, 5, false); // таймер
			pchar.questTemp.Saga.Mines = "true"; // после Саги рудник будет разрабатываться
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			DoQuestReloadToLocation("Shore53", "goto", "goto6", "");
		break;
		// <-- штурм рудника
		
		case "helensleep":
			dialog.text = "";
			link.l1 = "Jan, ne kiabálj velem. Rendezzük el a dolgokat, mint értelmes emberek - ne feledd, üzletet kell kötnünk!";
			link.l1.go = "helensleep_1";
		break;
		
		case "helensleep_1":
			dialog.text = "Most rögtön rád uszítom a kutyáimat, te varangy! Felejtsd el Levasseur-t, és tûnj el!";
			link.l1 = "Jan! Figyelj rám...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenSleep_SvensonThrowOut");
		break;
		
		case "after_drinking":
			dialog.text = "Milyen hordó? Ami Helent illeti, biztos vagyok benne, hogy jól megverem... Csak vicceltem, Charles, csak vicceltem! Tudom, hogy megy ez, és ami Joannát illeti - ez a történet remélhetôleg elgondolkodtatja egy kicsit - mostanában különösen nyûgös, tudod... Hát, ilyen az élet. Mindenesetre sok szerencsét Cartagenában!";
			link.l1 = "A viszontlátásig, Jan.";
			link.l1.go = "exit";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
