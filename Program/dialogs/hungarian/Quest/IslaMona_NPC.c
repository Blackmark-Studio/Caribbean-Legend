void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Mire van szükséged?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;
		
		// Родриго Хименес
		case "Himenes_exit":
			dialog.text = "Még valami, kapitány?";
			link.l1 = "Egyelôre semmi...";
			link.l1.go = "Himenes_exit_1";
		break;
		
		case "Himenes_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
		break;
		
		case "Himenes":
			dialog.text = "Ha-ha-ha-ha! Senor Hesucristo! Dicsôség Santiagónak, a Védelmezônek! Dicsôség Szûz Máriának! Megmenekültünk! Ha-ha-ha!";
			link.l1 = "Spanyolok! Fegyverbe!";
			link.l1.go = "Himenes_1_1";
			link.l2 = "Hahó! Úgy hallottam, gondjaik vannak. Kik vagytok ti?";
			link.l2.go = "Himenes_2";
		break;
		
		case "Himenes_1_1":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Ha-ha-ha-ha-ha-ha-ha-ha-ha!";
			link.l1 = "Jól van, rendben, nyugodj meg. Ez csak egy szokás.";
			link.l1.go = "Himenes_2";
		break;
		
		case "Himenes_2":
			dialog.text = "Ha-ha! Senor, a nevem Rodrigo Jimenez. Földmérô vagyok, és a sors akaratából e szerencsétlen emberek el jefe-je.";
			link.l1.go = "Himenes_3";
		break;
		
		case "Himenes_3":
			dialog.text = "Mi... itt kötöttünk ki. De, senor, mi nem vagyunk bûnözôk! Ha-ha-ha-ha-ha-ha!";
			link.l1 = "Mi olyan vicces?";
			link.l1.go = "Himenes_4";
		break;
		
		case "Himenes_4":
			dialog.text = "Ah... Elnézést kérek, senor! Ez az én bajom, gyerekkorom óta nevetek, ha nagyon ideges vagyok. Ha.";
			link.l1 = "És téged választottak vezetônek?... Jól van. Az emberek nem szállnak le csak úgy ok nélkül lakatlan szigetekre, senor. Megmagyarázná? Csak egy esélyt adok neked.";
			link.l1.go = "Himenes_5";
		break;
		
		case "Himenes_5":
			string nationManName[4];
			nationManName[0] = "English";
			nationManName[1] = "Francia";
			nationManName[2] = "Ha ezt látod, az egy hiba.";
			nationManName[3] = "Spanyol";
			dialog.text = "Sajnálom, attól tartok, nem értettem a nevét, uram. Ön angol?";
			link.l1 = nationManName[sti(pchar.BaseNation)] + ". Ez olyan fontos? Egyelôre ne aggódjunk a nevem miatt.";
			link.l1.go = "Himenes_6";
		break;
		
		case "Himenes_6":
			dialog.text = "Valóban, mivel a katolikus spanyol egyház eretneknek ismer el minket, meg kell jelennünk a Szent Inkvizíció igazságos bírósága elôtt. Ezért olyan fontos számunkra a nemzetiséged. Egy spanyol kapitány köteles lenne átadni minket a helyi hatóságoknak. Ilyesmit nem élnénk túl még egyszer! Ha-ha!";
			if (sti(pchar.BaseNation) == SPAIN) dialog.text = "Ha-ha-ha-ha-ha-ha-ha-ha-ha-ha! Ilyen a szerencsénk, hát, amúgy sincs vesztenivalónk. " + dialog.text;
			link.l1 = "Nos, szerencsédre az inkvizíció ügyei nem tartoznak rám. És akkor mi van? Ti pogányok vagytok?";
			link.l1.go = "Himenes_7";
		break;
		
		case "Himenes_7":
			dialog.text = "Nem, esküszöm neked! A mi közösségünk ötven évig foglalkozott kézmûvességgel és kereskedelemmel a dicsô Cadiz városában. Minden jól ment, még egy hajót is szereztünk, és engedélyt a birodalmunk gyarmataival való kereskedelemre. Most már értem, hogy akkoriban átléptünk valamilyen határt, és teljesen felkészületlenek voltunk az új versenytársainkra... és a módszereikre.";
			link.l1 = "Nem osztották meg a kereskedelmet valakivel Európában, és ennek következtében az egész közösség egy lakatlan karibi szigeten ragadt? És én még azt hittem, hogy nekem vannak életproblémáim...";
			link.l1.go = "Himenes_8";
		break;
		
		case "Himenes_8":
			dialog.text = "Sajnos ez a helyzet. A közösségünket olyan zsidók alapították, akik áttértek az új hitre, és lehetôséget kaptak arra, hogy hazatérjenek Spanyolországba. Ez az ôsi történelem elég volt a vádaskodásokhoz és a hivatalos vizsgálatokhoz.";
			link.l1 = "És így menekültél...";
			link.l1.go = "Himenes_9";
		break;
		
		case "Himenes_9":
			dialog.text = "Igen! Ha-ha-ha-ha! A saját hajónkon! Curacaóba tartottunk, hogy új otthont és új üzletet építsünk. Azonban alábecsültük az inkvizíció kitartását, és drágán megfizettünk érte. A futárjuk nem messze innen elfogott minket, és utasította a kapitányt, hogy küldjön haza minket...";
			link.l1 = "A fenébe!";
			link.l1.go = "Himenes_10";
		break;
		
		case "Himenes_10":
			dialog.text = "És ez még nem minden! Ha! A kapitányunk nem akart veszôdni azzal, hogy visszavigyen minket az Atlanti-óceánon át, vagy hogy a felelôssége alatt elengedjen minket a legközelebbi kikötôben. És egy igazán salamoni döntést hozva, ételt adott nekünk, itt kötött ki minket, és kész.";
			link.l1 = "Valóban tragikus történet, semmi kétség. Foglaljuk össze: nem mehetsz haza, a baráti kolóniák feljelentenek, és a külföldi kikötôk sem fogadnak be - a háborúnak ebben a térségben nincs vége. Mik a terveitek?";
			link.l1.go = "Himenes_11";
		break;
		
		case "Himenes_11":
			dialog.text = "Olyan sivár képet festett, uram, hogy nem találom a szavakat. Mintha nem lenne jobb hely számunkra, mint ez a sziget.";
			link.l1 = "Nem hiszem, hogy van jobb sziget.";
			link.l1.go = "Himenes_12";
		break;
		
		case "Himenes_12":
			dialog.text = "Tényleg? Spanyol?";
			link.l1 = "Az enyém. A sors úgy hozta, hogy örököltem egy lakatlan szigeten lévô egykori kalózok rejtekhelyét. Most ez a bázisom, és szeretném kibôvíteni, felfedezni a szigetet, és ha lehet, gyárat építeni oda...";
			link.l1.go = "Himenes_13";
		break;
		
		case "Himenes_13":
			dialog.text = "Kalóz vagy?";
			link.l1 = "Igen.";
			link.l1.go = "Himenes_14_1";
			link.l2 = "Nem.";
			link.l2.go = "Himenes_14_2";
		break;
		
		case "Himenes_14_1":
			dialog.text = "Új világ! Valóban, itt vagyunk. Otthon azt mondják, hogy a kalózok igazi démonok, és nem is emberek. Gyerekeket esznek, megerôszakolják a nôket, és lehúzzák a jó katolikusok bôrét. Ez igaz?";
			link.l1 = "A hét napjától függ. Ezt majd máskor megbeszéljük. Embereket keresek. Szorgalmas és rátermett embereket, akik hajlandóak néhány évig távol élni a civilizációtól. Érdekelné önt valami ilyesmi?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_14_2":
			dialog.text = "Kár, mivel már bûnözô vagyok, legalább egy kalózt szeretnék látni.";
			link.l1 = "Talán lesz még ilyen lehetôséged. Beszéljük meg máskor. Szorgalmas és rátermett egyéneket keresek, akik hajlandóak lennének néhány évig távol élni a civilizációtól. Érdekelné önt valami ilyesmi?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_15":
			dialog.text = "Nincs más kiút. De ez valójában nem is rossz lehetôség. Elfogadjuk, ha megengeded, hogy békében éljünk és dolgozzunk. És ígérjétek meg, hogy egy nap hazaküldtek minket! Adja a szavát, uram, és mondja meg a nevét...";
			link.l1 = "Én, kapitány "+GetFullName(pchar)+", a szavamat adom. ?";
			link.l1.go = "Himenes_16";
		break;
		
		case "Himenes_16":
			dialog.text = "Ha-ha! Megmenekültünk! Úgy legyen! Több család vagyunk, körülbelül harmincan. Mindannyian írástudók, kézmûves és kereskedelmi képzettséggel.";
			link.l1 = "A sors úgy döntött... Kérem, jöjjenek a fedélzetre!";
			link.l1.go = "Himenes_17";
		break;
		
		case "Himenes_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto1", "none", "", "", "", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			IslaMona_TerksHimenesOnBoard();
		break;
		
		case "Himenes_18":
			dialog.text = "Örülök, hogy megismerhetem, Senor Rodgar. Úgy tûnik, sokáig kell együtt élnünk és dolgoznunk... Te jó ég, hogy bírja ezt a hôséget?";
			link.l1 = "";
			link.l1.go = "Himenes_19";
		break;
		
		case "Himenes_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_14";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_20":
			dialog.text = "Ha nem bánja, beugrom: Kapitány, adjon nekünk egy napot, hogy berendezkedjünk, és gyorsan megvizsgáljuk a leltárt és a földet. Biztos vagyok benne, hogy Senor Rodgarnak rengeteg ötlete van, hogy mit kezdjünk ezzel a földdarabbal. Szerintem jó csapat leszünk.";
			link.l1 = "Nincs más választásod, Hymenese. Ha-ha.!";
			link.l1.go = "Himenes_21";
		break;
		
		case "Himenes_21":
			dialog.text = "Ha-ha-ha-ha-ha-ha!";
			link.l1 = "";
			link.l1.go = "Himenes_22";
		break;
		
		case "Himenes_22":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_23":
			dialog.text = "Igen, kapitány?";
			link.l1 = "Hymenese, van valami jó hír számomra?";
			link.l1.go = "Himenes_24";
		break;
		
		case "Himenes_24":
			dialog.text = "Kapitány, ez egy rémálom. A házad persze nem rossz. De egyébként... Lehetetlen ezekben a kunyhókban élni, körülvéve túlburjánzással, és Senor Rodgar azt sem tudja, mi történik a sziget másik végén!!! Hihetetlen! Ha-ha!";
			link.l1 = "Ideges vagy most tényleg nevetsz ezen?";
			link.l1.go = "Himenes_25";
		break;
		
		case "Himenes_25":
			dialog.text = "Persze, hogy vicces! Mit csináltak ennyi éven át? Elôször is be kell fejeznünk néhány ház építését, és elfogadható állapotba kell hoznunk ezeket a kunyhókat. Az embereknek tisztességesen kell élniük, hogy szorgalmasan dolgozhassanak. Továbbá megkérem a kalózokat, hogy végezzenek teljes felderítést a szigeten. Talán ez a hely nemcsak sziklákban és homokban gazdag. Ha minden elkészült, pontosan meg tudom majd mondani, hogy mihez kezdjünk ezzel a földdel.";
			link.l1 = "Remekül hangzik! Mit kell tennem?";
			link.l1.go = "Himenes_26";
		break;
		
		case "Himenes_26":
			AddQuestRecordInfo("IslaMonaData", "1");
			dialog.text = "Házakhoz, bútorokhoz és ideiglenes menedékhelyekhez szükséges anyagok. Mindent kiszámoltam. Tessék, itt a lista.";
			link.l1 = "Lenyûgözô...";
			link.l1.go = "Himenes_27";
		break;
		
		case "Himenes_27":
			dialog.text = "Tényleg? Uram, mi katedrálisokat építettünk! Ez lenyûgözô....";
			link.l1 = "Hajlamos vagyok hinni önnek! Csak véletlenül se építsen ide katedrálist. Minden alkalommal sok anyagot kell majd idehoznom?";
			link.l1.go = "Himenes_28";
		break;
		
		case "Himenes_28":
			dialog.text = "Nem, ezek az anyagok egy ideig el fognak tartani minket, de késôbb még mindig szükségünk lesz néhány dologra. Ha meg akarod próbálni elkerülni az ilyen gondokat a jövôben, hozz kétszer annyi anyagot.";
			link.l1 = "Nos, meggyôztél. Meglátom, mit tehetek. Van valami határidô?";
			link.l1.go = "Himenes_29";
		break;
		
		case "Himenes_29":
			dialog.text = "Nem, uram. De kérem, hogy ne késlekedjen - ez az a munka, amit el kell végezni, hogy a dolgok elôrehaladjanak. És az embereknek is kell egy hely, ahol lakhatnak. Pakolja be az anyagokat a raktárba, és ne felejtsen el értesíteni, ha minden készen van. Ó, majdnem elfelejtettem! Beszélj Rodgar úrral a sziget felfedezésérôl.";
			link.l1 = "Egyetértek!";
			link.l1.go = "Himenes_30";
		break;
		
		case "Himenes_30":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			pchar.questTemp.IslaMona = "stalk";
			AddQuestRecord("IslaMona", "6");
		break;
		
		case "Himenes_31":
			dialog.text = "Igen, kapitány?";
			if (IslaMona_CheckBuild()) // привез товары на стройку
			{
				link.l1 = "Helló, Hymenez. Ellenôrizd a raktárat.";
				link.l1.go = "Himenes_32_1";
			}
			else // не привез товары на стройку
			{
				link.l1 = "Hello, Hymenez. Az embereim átfésülték az egész szigetet. Mit szólsz hozzá?";
				if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_32_2"; // привез еду и лекарства
				else link.l1.go = "Himenes_32_3";
			}
		break;
		
		case "Himenes_32_1":
			IslaMona_RemoveBuild(); // сразу удаляем товары со склада
			dialog.text = "Remekül megoldottad ezt a feladatot! Ha valaha is Cadizban jársz, gyere hozzám dolgozni raktárosként!";
			link.l1 = "Máris megyek! Mondd, compadre, mit fogsz most csinálni?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_34_1"; // привез еду и лекарства
			else link.l1.go = "Himenes_34_2";
		break;
		
		case "Himenes_32_2":
			dialog.text = "Kapitány Úr, elôször a lakhatással és az ellátással foglalkozzunk. Majd utána tervezünk. A raktárban várom az árut a listájáról.";
			link.l1 = "Rendben, értem. Elôször is, házakat kell építenünk és rendbe kell tennünk ezt a helyet. Az áruk hamarosan megérkeznek.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_32_3":
			dialog.text = "Kapitány, elôször a házakkal és a készletekkel foglalkozzunk. Késôbb is készíthetünk terveket. A raktárban várom az árut a listádról. És a kalóz barátod is várja az ellátmányt és az orvosságot.";
			link.l1 = "Rendben, értem. Elôször is, házakat kell építenünk és rendbe kell tennünk ezt a helyet. Az áru hamarosan itt lesz. És a kalóz barátomnak is.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_33":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_31";
		break;
		
		case "Himenes_34_1":
			dialog.text = "Adjon nekünk hat hónapot, kapitány, és nem fog ráismerni erre a helyre.";
			link.l1 = "Azt mondod, hogy hat hónap múlva nem leszel itt sem te, sem a település, sem az anyagok? Viszlát késôbb!";
			link.l1.go = "Himenes_37"; // все выполнил
		break;
		
		case "Himenes_34_2":
			dialog.text = "Amint elintézed az ügyedet ezzel a banditával, elkezdünk dolgozni. Élelmiszert és gyógyszert kért tôletek, és én egyetértek vele - ez egy ésszerû követelés.";
			link.l1 = "Átadom neki a szavaidat.";
			link.l1.go = "Himenes_35";
			AddQuestRecord("IslaMona", "11");
		break;
		
		case "Himenes_35":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_36";
		break;
		
		case "Himenes_36":
			dialog.text = "Nos, kapitány? Mindent megtettél, amit a kalózod kért?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food"))
			{
				link.l1 = "Minden kérdést megoldottam Rodgarral. A sziget felderítése megkezdôdött, az ellátmány és a gyógyszerek a raktárban vannak. Most te jössz.";
				link.l1.go = "Himenes_34_1";
			}
			else
			{
				link.l1 = "Ne aggódj, megoldjuk. Én ezt elintézem.";
				link.l1.go = "Himenes_35";
			}
		break;
		
		case "Himenes_37":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			DeleteAttribute(pchar, "questTemp.IslaMona.Food");
			pchar.questTemp.IslaMona = "build";
			AddQuestRecord("IslaMona", "12");
			SetFunctionTimerCondition("IslaMona_BuildDone", 0, 0, 180, false);
		break;
		
		case "Himenes_38":
			dialog.text = "Kapitány Úr! Mit gondol? Ha-ha-ha?";
			link.l1 = "Ez sokkal szebb. Jelentést, Himenes!";
			link.l1.go = "Himenes_39";
		break;
		
		case "Himenes_39":
			dialog.text = "Most már tényleg itt élhetsz! Kitakarítottuk és újjáépítettük az összes házat, kivéve persze a tiédet. Nem túl fényûzô, de nem rosszabb, mint a mi Belize-ünk.";
			link.l1 = "Belize már régóta Angliához tartozik, Himenes.";
			link.l1.go = "Himenes_40";
		break;
		
		case "Himenes_40":
			dialog.text = "Nem biztos, hogy a házak tudnak róla, kapitány, ha-ha!";
			link.l1 = "Most már van hol laknod, és a település emberinek tûnik. Mi a következô lépés?";
			link.l1.go = "Himenes_41";
		break;
		
		case "Himenes_41":
			dialog.text = "Nézzen körül, beszéljen idôsebb Janssennel, és jöjjön vissza hozzám. Megbeszéljük a sziget felderítésének eredményeit és a terveinket.";
			link.l1 = "Mióta hívod így Rodgart? Nem voltak állandóan nézeteltéréseitek?";
			link.l1.go = "Himenes_42";
		break;
		
		case "Himenes_42":
			dialog.text = "És még mindig megvannak. De valahogy ki kell építenünk a munkakapcsolatokat.";
			link.l1 = "Köszönöm, Rodrigo. Hamarosan visszajövök.";
			link.l1.go = "Himenes_43";
		break;
		
		case "Himenes_43":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload6", "none", "", "", "", 10.0); // возможно будет иной локатор в новой локации
			pchar.questTemp.IslaMona = "village";
		break;
		
		case "Himenes_44":
			dialog.text = "Kapitány. Senor Janssen.";
			link.l1 = "Gyerünk, meséljen a sziget felderítésének eredményeirôl.";
			link.l1.go = "Himenes_45";
		break;
		
		case "Himenes_45":
			dialog.text = "Igen, kapitány. Néhány helyet személyesen vizsgáltam meg a kutatóval. Nos, mit is mondhatnék... Isla Mona egy szegény, apró, és elég érdektelen sziget. Nagyon kevés hely van építkezésre, a táj nehéz, meredek, és szinte nincs is termôföld. Három strand, egy elárasztott barlang, sûrû bozótos, néhány papagáj, egy kecskecsorda és mi...";
			link.l1 = "Ez most komoly? Azt mondja, hogy a sziget legértékesebb vagyona egy kecskecsorda?";
			link.l1.go = "Himenes_46";
		break;
		
		case "Himenes_46":
			dialog.text = "Ha-ha-ha-ha-ha-ha! Megkérdezném, Senor! Ha-ha! Nem hagyta, hogy befejezzem!";
			link.l1 = "";
			link.l1.go = "Himenes_47";
		break;
		
		case "Himenes_47":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_38";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_48":
			dialog.text = "";
			link.l1 = "Rendben, rendben, nyugodjon meg és folytassa. Tudod, sokat fektettem ebbe a helybe.";
			link.l1.go = "Himenes_49";
		break;
		
		case "Himenes_49":
			dialog.text = "És nem hiába! Van elég friss víz a barlangban, van elég talaj, hogy gyümölcstermô fákat termesszünk, és kecskéket is lehet tenyészteni. A halászattal és a bajtársaid erôfeszítéseivel az élelemkérdés nagyon gyorsan megoldódik.";
			link.l1 = "Tehát nem kell több élelmet hozni ide? Nem rossz. Reméltem, hogy ez a hely meg tud élni az állandó gondoskodásom nélkül is. Folytassuk.";
			link.l1.go = "Himenes_50";
		break;
		
		case "Himenes_50":
			dialog.text = "Mindenben igaza van, Senor. De ez még nem minden hír! Elôször is, Senor Rodgar elôállt egy kocsma építésének ötletével. Nem tudom, mit fog adni, de ez a gazember készül valamire.";
			link.l1 = "Le akarja rúgni magát, ez az!";
			link.l1.go = "Himenes_51";
		break;
		
		case "Himenes_51":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_40";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_52":
			dialog.text = "Másodszor, a Kormányzó-öbölrôl kiderült, hogy sokkal mélyebb, mint eredetileg gondoltuk. Építhetünk egy teljes értékû mólót.";
			link.l1 = "Nem egészen értem, mi hasznom lesz belôle, de ez már jó hír. Remélem, ez még nem minden?";
			link.l1.go = "Himenes_53";
		break;
		
		case "Himenes_53":
			dialog.text = "Találtunk egy bacote fákból álló ligetet. Ideális hely egy gyárnak.";
			link.l1 = "Boldoggá teszel, Rodrigo! Valóban, kiváló hírek!";
			link.l1.go = "Himenes_54";
		break;
		
		case "Himenes_54":
			dialog.text = "Egyelôre ennyi, senor. A jövôben talán több ötletünk is lesz. Tudja, a legjobb ötletek munka közben jönnek! Mirôl szeretnél kérdezni?";
			link.l1 = "Meséljen nekem Bacote-ról. Ígéretesnek hangzik.";
			link.l1.go = "Himenes_55";
		break;
		
		case "Himenes_55":
			dialog.text = "Becslésem szerint egy kis gyár több évig képes lesz kitermelni ezt az értékes fát. A tartalékok szerények, de az erôforrás stratégiai jelentôségû. A sziget közepén kitermelhetünk egy területet, és ott felépíthetünk egy házat egy raktárral. Ez már egy kezdet. Az építôanyagokon kívül szükségünk lesz még körülbelül 15 készlet bilincsre és muskétára.";
			link.l1 = "És miért van szükségünk bilincsekre? És miért pont tizenötre?";
			link.l1.go = "Himenes_56";
		break;
		
		case "Himenes_56":
			dialog.text = "Ez kemény munka, senor. Azt is mondhatnám, hogy rabszolgamunka.";
			link.l1 = "Megértem. Ô...";
			link.l1.go = "Himenes_57_1";
			link.l2 = "Megôrültél? Nem leszek rabszolgatartó!";
			link.l2.go = "Himenes_57_2";
		break;
		
		case "Himenes_57_1":
			dialog.text = "";
			link.l1 = "És miért van szükségünk muskétára? És miért csak egy?";
			link.l1.go = "Himenes_59";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Himenes_57_2":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_42";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Himenes_58":
			dialog.text = "Egyetértek a kalózzal, senor. Nem értem magát, kapitány. Ennek a térségnek az egész gazdasága a rabszolgamunkán alapul, és ez még sokáig így is marad. Mi mitôl lennénk jobbak?";
			link.l1 = "Dönteni fogok. Addig is, mondja meg, miért van szüksége muskétára? És miért pont egy?";
			link.l1.go = "Himenes_59";
		break;
		
		case "Himenes_59":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_60":
			dialog.text = "Természetesen a gyár karbantartást igényel. Az építésével ez a sziget olyan gazdasággal fog rendelkezni, ahol önök lesznek a fô kereskedelmi partnerek. A rabszolgákat mi magunk fogjuk etetni, de a biztonságot és a termelést a saját zsebükbôl kell majd fizetniük. A telepesek száz dublont és öt üveg bort vesznek minden egyes tételért. A biztonsági kérdésekben tárgyaljatok Senor Janssennel.";
			link.l1 = "";
			link.l1.go = "Himenes_61";
		break;
		
		case "Himenes_61":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_46";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_62":
			dialog.text = "havonta negyven intézkedés. Az arany pedig a jövôre szól. Egy nap majd elviszel minket innen, emlékszel az ígéretedre? Minden munkát meg kell fizetni, és a ti dubloonjaitokkal fizetjük ki a vadászokat és a mesterembereket a településen végzett munkájukért. Így lesz kereskedelmünk, és ezzel együtt - civilizációnk!";
			link.l1 = "Ez a szellem! Rendben van! Egyelôre minden elég meggyôzôen hangzik...";
			link.l1.go = "Himenes_63";
		break;
		
		case "Himenes_63":
			dialog.text = "Mi érdekel még titeket?";
			link.l1 = "Szóval, mi a helyzet a kocsmával? Miért nem építesz színházat?";
			link.l1.go = "Himenes_64";
		break;
		
		case "Himenes_64":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_65":
			dialog.text = "Kapitány, figyelmeztettem, hogy nem tetszene a ház ötlete. De ez az egyetlen lehetôség. Magának van a legnagyobb háza a... khm, a városban, az elsô emeletet átépítjük hallá, felállítjuk az asztalokat és a konyhát. A ház alatti barlangokban tároljuk az italokat és az ételt. Vannak embereink, akik fôznek és zenélnek. A második emelet a tiétek marad, és nem nyúlunk hozzá. Az elsô emeletrôl minden holmidat mi magunk visszük fel az emeletre.";
			link.l1 = "Rendben. Szóval, mit fog nekünk adni a kocsma?";
			link.l1.go = "Himenes_66";
		break;
		
		case "Himenes_66":
			dialog.text = "Kapunk némi kulturális életet, és lehetôséged lesz arra, hogy körülbelül háromszáz embernek legyen tartalékod a Karib-tenger szívében.";
			link.l1 = "Érdekes... Majd átgondolom.";
			link.l1.go = "Himenes_67";
		break;
		
		case "Himenes_67":
			dialog.text = "Mi érdekel még titeket?";
			link.l1 = "És mi a helyzet a mólóval?";
			link.l1.go = "Himenes_68";
		break;
		
		case "Himenes_68":
			dialog.text = "Ez egyszerû. Megtisztítjuk a Kormányzó-öblöt a zátonyoktól, jelzôfényeket szerelünk fel, és mólót építünk. Senor Janssen azt állítja, hogy három hajónak, vagy egy elsô osztályú hajónak tudtok majd menedéket nyújtani az öbölben. És kellemesebb lesz ide visszatérni, nem kell majd minden alkalommal a csónakot a parton végigvonszolni.";
			link.l1 = "Az jó lenne.";
			link.l1.go = "Himenes_69";
		break;
		
		case "Himenes_69":
			dialog.text = "Mit szeretnél tudni?";
			link.l1 = "Egyelôre ennyi. Visszatérek, ha eldöntöttem, mit építek.";
			link.l1.go = "Himenes_70";
		break;
		
		case "Himenes_70":
			dialog.text = "Senor kapitány, vegye át ezt a dokumentumot. Vettem a bátorságot, és leírtam az összes részletet, hogy ne kelljen tucatszor megismételnem ôket. Tanulmányozza át, hozza magával az anyagokat, és állítsa össze a feladatot.";
			link.l1 = "Köszönöm, Rodrigo.";
			link.l1.go = "Himenes_71";
		break;
		
		case "Himenes_71":
			DialogExit();
			IslaMona_HouseDialogFin();
		break;
		
		case "Himenes_72": // нода Хименеса строителя и управляющего факторией
			if (CheckAttribute(pchar, "questTemp.IslaMona.RecordPart")) // после защиты Исла Моны - нужно ещё 10 рабов
			{
				dialog.text = "Kapitány Úr, tíz rabszolgára van szükségünk, akik a gyárban dolgoznak - mondtam, nem felejtetted el?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 10)
				{
					link.l1 = "Már el is szállítottuk. Pakold ki ôket és kezdd el a termelést.";
					link.l1.go = "Himenes_plantation_12";
				}
				else
				{
					link.l1 = "A memóriám sértetlen. Hamarosan hozom ôket.";
					link.l1.go = "Himenes_plantation_14";
				}
				break;
			}
			dialog.text = "Szóval, Kapitány Úr, mit szól hozzá?";
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Harbour"))
			{
				link.l1 = "Tiszta öblöt és biztonságos mólót akarok. Ez lesz a flottám bázisa.";
				link.l1.go = "Himenes_harbour";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Tavern"))
			{
				link.l2 = "Menjetek és építsétek meg a kocsmát. Mindenki értékelni fogja, én pedig tarthatok itt tartalékot.";
				link.l2.go = "Himenes_tavern";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Plantation"))
			{
				link.l3 = "Kezdjétek el építeni az ültetvényt. Itt az ideje, hogy megtérüljenek a befektetések.";
				link.l3.go = "Himenes_plantation";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Slave") && IslaMona_CheckSlave())
			{
				link.l4 = "Rodrigo, a különösen értékes szakembereket és felszereléseket a gyárba szállították. Elkezdheted a munkát.";
				link.l4.go = "Himenes_plantation_7";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Factory.Part") && sti(pchar.questTemp.IslaMona.Factory.Part) > 0)
			{
				link.l4 = "Rodrigo, a vasfámért jöttem.";
				link.l4.go = "Himenes_bacaut";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Tavern") && pchar.questTemp.IslaMona.Tavern == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Factory") && !CheckAttribute(pchar, "questTemp.IslaMona.Church"))
			{
				link.l5 = "Rodrigo, befejeztük a nagyszerû építkezésünket?";
				link.l5.go = "Himenes_church";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "start" && IslaMona_CheckChurch())
			{
				link.l5 = "Rodrigo, építsük fel a templomodat.";
				link.l5.go = "Himenes_church_10";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "Wait_candles" && IslaMona_CheckCandles())
			{
				link.l5 = "Rodrigo, elhoztam a templomod tárgyait.";
				link.l5.go = "Himenes_church_10_3";
			}
			link.l10 = "Egyelôre semmi...";
			link.l10.go = "Himenes_73";
		break;
		
		case "Himenes_harbour":
			if (IslaMona_CheckHarbour())
			{
				dialog.text = "Az anyagok rendelkezésre állnak, minden készen áll. Az építkezés 4 hónapig fog tartani.";
				link.l1 = "Nem sietsz, ugye! Nos, sok szerencsét, Rodrigo.";
				link.l1.go = "Himenes_harbour_1";
			}
			else
			{
				dialog.text = "Attól tartok, nincs elég anyag a raktárban. Kérem, nézze meg még egyszer a listát.";
				link.l1 = "Majd én gondoskodom róla.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_tavern":
			if (IslaMona_CheckTavern())
			{
				dialog.text = "Az anyagok rendelkezésre állnak, minden készen áll. Az építkezés 3 hónapig fog tartani.";
				link.l1 = "Nem sietsz, ugye! Nos, sok szerencsét, Rodrigo.";
				link.l1.go = "Himenes_tavern_1";
			}
			else
			{
				dialog.text = "Attól tartok, nincs elég anyag a raktárban. Kérem, nézze meg még egyszer a listát.";
				link.l1 = "Majd én gondoskodom róla.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_plantation":
			if (IslaMona_CheckPlantation())
			{
				dialog.text = "Az anyagok rendelkezésre állnak, minden készen áll. Az építkezés 6 hónapig tart.";
				link.l1 = "Nem sietsz, ugye! Sok szerencsét, Rodrigo.";
				link.l1.go = "Himenes_plantation_1";
			}
			else
			{
				dialog.text = "Attól tartok, nincs elég anyag a raktárban. Kérem, nézze meg még egyszer a listát.";
				link.l1 = "Majd én gondoskodom róla.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_73":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_harbour_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveHarbour();
			pchar.questTemp.IslaMona.Harbour = "true";
			SetFunctionTimerCondition("IslaMona_BuildHarbour", 0, 0, 120, false);
		break;
		
		case "Himenes_harbour_2":
			dialog.text = "Üdvözlöm, kapitány. Hogy tetszik az új kikötô?";
			if (stf(environment.time) > 22.0 || stf(environment.time) < 5.0)
			{
				link.l1 = "Sötét van, Rodrigo! Majdnem összetörtük a dicsért mólódat! Jó, hogy legalább kivilágítottad!";
				link.l1.go = "Himenes_harbour_3";
			}
			else
			{
				link.l1 = "Nem rossz, Rodrigo! Apróságnak tûnik, de jó ezeken a deszkákon sétálni a partig. És az öbölben is könnyebbé vált a navigálás. Szóval, azt hiszem, most már több hajót is el tudok helyezni ebben a kis öbölben?";
				link.l1.go = "Himenes_harbour_4";
			}
		break;
		
		case "Himenes_harbour_3":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_51";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_harbour_4":
			sld = characterFromId("Islamona_carpenter");
			sld.portman.info = "true"; // если вдруг до сих пор не говорил об условиях стоянки
			pchar.questTemp.IslaMona.Harbour = "done"; // флаг - пристань построена и сдана
			dialog.text = "Igen, kapitány. Meg kell mondanom, van benne némi büszkeség. Nyugodtan szóljon, hogy hogyan szeretné folytatni a nagy építkezési projektünket.";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && pchar.questTemp.IslaMona.Plantation == "complete") // если пересеклось со сдачей фактории
			{
				link.l1 = "Ha már az építkezésnél tartunk. Mostanra a gyáramnak is el kellene készülnie. Igaz, Rodrigo?";
				link.l1.go = "Himenes_plantation_2";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Himenes_harbour_5";
			}
		break;
		
		case "Himenes_harbour_5":
			DialogExit();
			IslaMona_HarbourClear();
		break;
		
		case "Himenes_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveTavern();
			pchar.questTemp.IslaMona.Tavern = "true";
			SetFunctionTimerCondition("IslaMona_BuildTavern", 0, 0, 90, false);
		break;
		
		case "Himenes_tavern_2":
			dialog.text = "H-hic! Cap! Itt ünnepelünk!";
			link.l1 = "Rodgar. Rodrigo. Ó, a fenébe!";
			link.l1.go = "Himenes_tavern_3";
		break;
		
		case "Himenes_tavern_3":
			dialog.text = "Mi a baj, k-k-kapitány? Nem tetszik a falak színe?";
			link.l1 = "Csak most vettem észre, hogy ti ketten ugyanazt a nevet viselitek! Ha-ha-ha-ha! Egy spanyol és egy kalóz, akiknek ugyanaz a nevük, kocsmát építettek egy lakatlan szigeten, és együtt iszogatnak, mintha az indián istenek mindenkit felfalnának, és napfelkeltére vége lenne a világnak! Ha-ha! Én is veled vagyok!";
			link.l1.go = "Himenes_tavern_4";
		break;
		
		case "Himenes_tavern_4":
			dialog.text = "Ha-ha-ha! Annyira igaz! Gól!";
			link.l1 = "Pont!";
			link.l1.go = "Himenes_tavern_5";
		break;
		
		case "Himenes_tavern_5":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_ReloadTavern();
		break;
		
		case "Himenes_plantation_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemovePlantation();
			pchar.questTemp.IslaMona.Plantation = "true";
			SetFunctionTimerCondition("IslaMona_BuildPlantation", 0, 0, 180, false);
		break;
		
		case "Himenes_plantation_2":
			dialog.text = "Minden készen áll. Mehetünk? Hadd mutassam meg a gyárat.";
			link.l1 = "Vezessenek.";
			link.l1.go = "Himenes_plantation_3";
		break;
		
		case "Himenes_plantation_3":
			DialogExit();
			pchar.questTemp.IslaMona.Plantation.Harbour = "true"; // наложилась сдача пристани и фактории
			IslaMona_PlantationGo();
		break;
		
		case "Himenes_plantation_4":
			dialog.text = "Kapitány, majdnem minden készen áll a mûködés megkezdésére. Lakások a munkásoknak, raktár a nyersanyagoknak, feldolgozó terület - egy méltó gyár épült. A dzsungelben már kijelöltük a legígéretesebb fákat a fakitermeléshez. Hozzatok tizenöt munkást és a megbeszélt készletet - 15 bilincset és muskétát, és máris kezdhetjük a munkát.";
			link.l1 = "Mi? A rabszolgákra gondolsz?";
			link.l1.go = "Himenes_plantation_5";
		break;
		
		case "Himenes_plantation_5":
			dialog.text = "Ha! Szláv... Rabszolgák vágnak, telepesek dolgoznak, kalózok ôrködnek. Mindenkinek lesz munkája - komoly vállalkozásba kezdett, kapitány.";
			link.l1 = "Majdnem olyan, mint az ígéret földje, huh. Várjátok meg az árut, itt az ideje, hogy vadászni menjek.";
			link.l1.go = "Himenes_plantation_6";
		break;
		
		case "Himenes_plantation_6":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Plantation.Slave = "true"; // привезти рабов, кандалы и мушкет для запуска фактории
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "IslaMona_factoria_residence", "sit", "sit1", "IslaMona_PlantationHouse", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5);
			pchar.questTemp.IslaMona.Plantation = "done"; // флаг - фактория построена и сдана
		break;
		
		case "Himenes_plantation_7":
			dialog.text = "Szomorú sors... Soha nem hagyják el ezt a helyet.";
			link.l1 = "Rodgar... Úgy értem, Rodrigo! Elôször is, lehet, hogy elmennek. Másodszor pedig, ha valaki mással találkoznál Terks-en, a sorsod sem lenne jobb.";
			link.l1.go = "Himenes_plantation_8";
		break;
		
		case "Himenes_plantation_8":
			dialog.text = "Ezt nagyon jól tudom, kapitány. És nem felejtem el. Hadd meséljek neked ennek a gyárnak a mûködésérôl. Jövô hónaptól kezdve, a tizenötödik napon negyven rönknyi feldolgozott bacoutot szállítunk. Természetesen nem kell minden hónapban eljönnie minden egyes szállításért - minden tételt itt, a gyárban tárolunk és várunk önre.";
			link.l1 = "Tehát egyszerre több tételt is átvehetek?";
			link.l1.go = "Himenes_plantation_9";
		break;
		
		case "Himenes_plantation_9":
			dialog.text = "Az ésszerûség határain belül természetesen - ne maradjon távol túl sokáig. Az emberek nem fognak évekig fizetés nélkül dolgozni, nem tudván, hogy egyetlen vevôjük még él-e vagy sem. Azt hiszem, hat adagot szállítunk, mielôtt felfüggesztjük a mûködést.";
			link.l1 = "Az összes árut egyszerre kell átvennem? Mi a helyzet az árral, emlékeztessen rá?";
			link.l1.go = "Himenes_plantation_10";
		break;
		
		case "Himenes_plantation_10":
			dialog.text = "Igen, egyszerre. Egy normál bacout napló ára tíz dublón. Ezen kívül minden egyes tételért öt üveg jó rumot és ugyanennyi borosüveget kell adnod. Rodgar azt állítja, hogy ilyen árakat sehol máshol a világon nem találsz.";
			link.l1 = "Valóban, ezzel egyetértek! Köszönöm, Rodrigo. Lássunk munkához!";
			link.l1.go = "Himenes_plantation_11";
		break;
		
		case "Himenes_plantation_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			DeleteAttribute(pchar, "questTemp.IslaMona.Plantation.Slave");
			AddQuestRecordInfo("Unique_Goods", "5");
			IslaMona_RemoveSlave();
		break;
		
		case "Himenes_plantation_12":
			dialog.text = "Kitûnô! Most pedig kezdjük újra a munkát!";
			link.l1 = "Jó.";
			link.l1.go = "Himenes_plantation_13";
		break;
		
		case "Himenes_plantation_13":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_FactoryReActivar(); // запустить факторию
		break;
		
		case "Himenes_plantation_14":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_bacaut":
			dialog.text = "Persze, kapitány, vegye el. A következô idôpontra a következô tételek állnak készen: "+sti(pchar.questTemp.IslaMona.Factory.Part)+", azaz "+sti(pchar.questTemp.IslaMona.Factory.Goods)+" naplók. Ezért tartozik nekünk "+sti(pchar.questTemp.IslaMona.Factory.Dublon)+" dublonnal, "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" üveg rummal és "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" üveg borral, mindezek megvannak?";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.IslaMona.Factory.Dublon) && PCharItemsTotal("potionrum") >= sti(pchar.questTemp.IslaMona.Factory.Bottle) && PCharItemsTotal("potionwine") >= sti(pchar.questTemp.IslaMona.Factory.Bottle))
			{
				link.l1 = "Persze, hogy megvan. Itt a fizetség.";
				link.l1.go = "Himenes_bacaut_1";
			}
			else
			{
				link.l1 = "Úgy tûnik, nincs meg mindenem. Azonnal hozom.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_1":
			if (IslaMona_CheckBacautSpace())
			{
				dialog.text = "Remek. A gyárból a raktárba szállítjuk a bacoutot, ahonnan bármikor átveheti, amikor csak akarja.";
				link.l1 = "Remek. Készítsd elô a következô adagot.";
				link.l1.go = "Himenes_bacaut_2";
			}
			else
			{
				dialog.text = "Várjon, kapitány! A raktáruk tele van - nem fogjuk tudni az összes betakarított bacoutot odatölteni. Takarítson fel egy kis helyet a raktárban - aztán jöjjön vissza hozzám.";
				link.l1 = "Rendben, majd én elintézem.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_2":
			dialog.text = "Természetesen, kapitány!";
			link.l1 = "...";
			link.l1.go = "Himenes_73";
			IslaMona_FactoryTrade();
		break;
		
		case "Himenes_church":
			dialog.text = "Ha! Kapitány, attól tartok, bármi mást építeni felesleges butaság és túlzás lenne. Hacsak...";
			link.l1 = "Hacsak mi?";
			link.l1.go = "Himenes_church_1";
		break;
		
		case "Himenes_church_1":
			dialog.text = "Kapitány, kínos nekem errôl kérdeznem... Már így is hatalmas összeget fektetett ebbe a helyre!";
			link.l1 = "Egy bordélyház?";
			link.l1.go = "Himenes_church_2_1";
			link.l2 = "Egy templom?";
			link.l2.go = "Himenes_church_2_2";
		break;
		
		case "Himenes_church_2_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Szent Santiagra esküszöm, nem lenne rossz! De az elsô éjszakán a mi asszonyaink felgyújtanák. Velünk együtt. Nem, kapitány, én egy templomról beszélek. Igen, van tisztességes lakásunk és fizetésünk, tenger és szórakozás, család és barátok. De valami mégis hiányzik, érted?";
			link.l1 = "El tudom képzelni.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_2_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			AddCharacterExpToSkill(pchar, "Defence", 500);
			dialog.text = "Átlát rajtam, kapitány. Igen, van tisztességes lakásunk és fizetésünk, tenger és szórakozás, családok és barátok. De valami mégis hiányzik, érted?";
			link.l1 = "El tudom képzelni.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_3":
			dialog.text = "Pontosan. Nem tudjuk felépíteni Isten házát a segítséged nélkül. Egy ilyen helynek különlegesnek kell lennie, a világból valónak. És ezért drágának kell lennie. Szükségünk lesz gyertyákra, aranyrudakra, borostyánra, és persze építôanyagokra, és nem olcsóakra. Ez nem hozna hasznot, ezért nem merem kérni.";
			link.l1 = "Szóval, kell ide egy pap?";
			link.l1.go = "Himenes_church_4";
		break;
		
		case "Himenes_church_4":
			dialog.text = "Nem.";
			link.l1 = "Van már köztetek pap?";
			link.l1.go = "Himenes_church_5";
		break;
		
		case "Himenes_church_5":
			dialog.text = "Nem, kapitány. És azt hiszem, már mindent megértettél.";
			link.l1 = "Szóval, az inkvizíció szent atyáinak volt oka arra, hogy üldözzenek téged? Eretnekek vagytok?";
			link.l1.go = "Himenes_church_6";
		break;
		
		case "Himenes_church_6":
			dialog.text = "A kánoni törvények szerint mi vagyunk a legrosszabb eretnekek. Nem hisszük, hogy az Istennel való kommunikációhoz szükségszerûen szükség van egy evilági közvetítôre.";
			link.l1 = "E világból?";
			link.l1.go = "Himenes_church_7";
		break;
		
		case "Himenes_church_7":
			dialog.text = "Kapitány, mi nem vagyunk sátánisták, és a közösségünk nem szekta. Keresztények vagyunk, mint önök, de mi nagyon tágan látjuk a dolgokat. Túl tágan, néhány nagyon mûvelt és értékes ember szerint. Ha valaha is helyet találsz a szívedben a nyitottságnak és a megértésnek, akkor többet fogok mondani. De egyelôre csak ezt a listát fogadd el. Csak a biztonság kedvéért.";
			link.l1 = "Errôl korábban kellett volna szólnod, Rodrigo. Nem akarok egy szép napon hazatérve egy boszorkányszombatot vagy egy új hit születését látni a földemen! Amíg te vársz - én döntést hozok.";
			link.l1.go = "Himenes_church_8_1";
			link.l2 = "Lenyûgözô lista. Kezdem érteni, miért van szükségük a szentatyáknak annyi pénzre! Átgondolom az ajánlatodat, Rodrigo, és döntést hozok.";
			link.l2.go = "Himenes_church_8_2";
		break;
		
		case "Himenes_church_8_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "";
			link.l1 = "Ha pozitív a döntés, akkor a listádról minden árut elhozok a raktárba, és a kincseket az asztalra terítem neked.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_8_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			dialog.text = "";
			link.l1 = "Ha pozitív a döntés, akkor a listádról minden árut elhozok a raktárba, és a kincseket az asztalra terítem neked.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_9":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "start";
			AddQuestRecord("IslaMona", "14");
			AddQuestRecordInfo("IslaMonaData", "3");
		break;
		
		case "Himenes_church_10":
			dialog.text = "Az egész közösségünk nevében köszönöm, kapitány. Ezt nem fogja megbánni, esküszöm!";
			link.l1 = "Csak akkor fogom megbánni, ha valami teljesen silányat építesz.";
			link.l1.go = "Himenes_church_10_1";
		break;
		
		case "Himenes_church_10_1":
			dialog.text = "Kapitány, az összes építôanyag raktáron van! Elkezdjük az építkezést, amint elhozza a felsorolt luxuscikkeket. Ékszereket és rituális eszközöket fogunk belôlük készíteni. Még egyszer, köszönöm szépen, kapitány! Muchas gracias!";
			link.l1 = "Szívesen!";
			link.l1.go = "Himenes_church_10_2";
		break;
		
		case "Himenes_church_10_2":
			DialogExit();
			IslaMona_RemoveChurch();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "Wait_candles";
			pchar.questTemp.IslamonaChurch.GoldNugget = 50;
			pchar.questTemp.IslamonaChurch.Candle = 100;
			pchar.questTemp.IslamonaChurch.Amber = 30;
			pchar.questTemp.IslamonaChurch.BlueAmber = 1;
		break;
		
		case "Himenes_church_10_3":
			IslaMona_RemoveCandles();
			string sAdd = "";
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Candle"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Candle)+ " candles,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Amber"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Amber)+ " amber,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.GoldNugget"))
			{
				sAdd += " "+ sti(pchar.questTemp.IslamonaChurch.GoldNugget) + " ingots,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.BlueAmber"))
			{
				sAdd += " and one blue amber"
			}
			if(sAdd == "")
			{
				dialog.text = "Muchisimas gracias, kapitány! Minden készen áll, megkezdjük az építkezést. Jöjjenek vissza néhány hónap múlva az elsô szertartásra. Ó, és még valami, a szôlô megérett! Házi bort készítünk, ünnepséget tartunk, és lakomát rendezünk a tiszteletedre!";
				link.l1 = "Azt hiszem, mindannyian megérdemlünk egy ünneplést. Két hónap múlva visszajövök.";
				link.l1.go = "Himenes_church_12";
			}
			else
			{
				dialog.text = "Kapitány, még mindig van "+sAdd+" .";
				link.l1 = "Persze, csak adjon még egy kis idôt, kérem. Ôszintén szólva, ha nem lennének a gyertyák, azt hinném, hogy egy kincset akarsz elásni.";
				link.l1.go = "Himenes_church_11";
			}
		break;
		
		case "Himenes_church_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_church_12":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "build";
			AddQuestRecord("IslaMona", "15");
			//IslaMona_RemoveChurch();
			SetFunctionTimerCondition("IslaMona_ChurchComplete", 0, 0, 60, false);
		break;
		
		case "Himenes_church_13":
			dialog.text = "Ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha!";
			link.l1 = "És én még azt hittem, hogy megszabadultál ettôl az idióta szokástól.";
			link.l1.go = "Himenes_church_14";
		break;
		
		case "Himenes_church_14":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "hogy ne kelljen hetekig itt ülnünk és várnunk az események alakulására.";
			else sTemp = "hogy nem mindenkinek kell részt vennie a csatában.";
			dialog.text = "Ha-ha-ha-ha-ha-ha-ha-ha... ha. Én is így gondoltam, kapitány! Rodgarnak igaza van, a jelenléted már most is azt jelenti, "+sTemp+"";
			link.l1 = "Már tudom, mi történt. Vannak veszteségek?";
			if (GetCharacterIndex("Mirabella") != -1) link.l1.go = "Himenes_church_15";
			else link.l1.go = "Himenes_church_16";
		break;
		
		case "Himenes_church_15":
			DialogExit();
			sld = characterFromId("Mirabella"); 
			sld.dialog.currentnode = "mirabelle_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_16":
			dialog.text = "Ne aggódj annyira, Rodgar. Nem a te hibád, a lövészek túl gyorsan érkeztek. Úgysem tudtuk volna ôket a vonalaink mögött tartani, és nem volt idônk mindet kardélre hányni.";
			link.l1 = "Mi van a spanyolokkal?";
			link.l1.go = "Himenes_church_17";
		break;
		
		case "Himenes_church_17":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) // решил проблему самостоятельно
			{
				dialog.text = "Csak hárman jutottak el hozzánk, és csak egy élte túl. Maga a kapitány! Nyilvánvalóan egy nagyon komoly katonai tengerész. De ô még nem segíthet rajtunk - még legalább néhány napig ágyban kell maradnia. Egyébként, kapitány úr, mi is hallottunk lövéseket, és a kinézetébôl ítélve ön is.";
				link.l1 = "Mondhatni. A hívatlan vendégek láthatóan nem számítottak ilyen váratlan látogatásra, és visszadobták ôket a tengerbe.";
				link.l1.go = "Himenes_church_20";
			}
			else
			{
				dialog.text = "Csak hárman jutottak el hozzánk, és csak egy élte túl. Maga a kapitány! Nyilvánvalóan egy nagyon komoly katonai tengerész. De ô még nem tud segíteni nekünk - még legalább néhány napig ágyban kell maradnia.";
				if (i >= 50) 
				{
					link.l1 = "Legutóbb elég sok emberemet hagytam itt ôrségben, úgyhogy sokkal többnek kell lenniük, mint a fuziliásoknak. Miért nem dobtad vissza ôket egyszerre a tengerbe?";
					link.l1.go = "Himenes_church_17_1";
				}
				else 
				{
					link.l1 = "Rendben, oldjuk meg ezt a problémát. A terv a következô: Kicsalom ôket egy nyílt támadásra, méghozzá most azonnal. Nincs értelme késlekedni. Készüljetek sörétekkel és muskétákkal, kalózok a kapuknál, a többiek maradjanak otthon - és várjatok.";
					link.l1.go = "Himenes_church_18";
				}
			}
		break;
		
		case "Himenes_church_17_1":
			dialog.text = "Kapitány, ôk mind hivatásos katonák, egy parancsnokkal. És még csak megfelelô fegyvereink sincsenek. Igen, persze, létszámban le tudtuk volna gyôzni ôket, de akkor legalább kétszer annyi embert veszítettünk volna, és itt minden ember értékes és szükséges.";
			link.l1 = "Rendben, oldjuk meg ezt a problémát. A terv a következô: Kicsalom ôket egy nyílt támadásra, méghozzá most azonnal. Nincs értelme késlekedni. Készüljetek sörétekkel és muskétákkal, kalózok a kapuknál, a többiek maradjanak otthon - és várjatok.";
			link.l1.go = "Himenes_church_18";
		break;
		
		case "Himenes_church_18":
			dialog.text = "Kapitány, készen állunk a harcra!";
			link.l1 = "Tudom, Rodrigo. De nem hagytad, hogy befejezzem: ha akár csak egy ellenségnek is sikerül áttörnie a kapukon, nektek minden oldalról neki kell rohannotok. És a csatában egyre kisebb az esélyetek, hogy egy golyót vagy egy szilánkot kapjatok. Van még kérdés?";
			link.l1.go = "Himenes_church_19";
		break;
		
		case "Himenes_church_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_68";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_20":
			dialog.text = "Szép munka! Természetesen kellemetlen, hogy ilyen szerencsétlen sors érte honfitársaitokat. De hálás vagyok, hogy ismét a mi oldalunkra álltatok.";
			link.l1 = "Nem volt könnyû, Rodrigo. A normális emberek árulásnak fogják nevezni, és igazuk lesz.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "Ez az én földem, Rodrigo. Mindig meg kell védeni, és nem számít, kitôl.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20a":
			dialog.text = "Igen, az öreg Rodrigo nem gondolta, amikor elhagyta Cádizt, hogy ilyen kalandok várnak rá az Újvilágban.";
			link.l1 = "Ne is mondd. Néha még mindig ugyanezek a gondolatok járnak a fejemben.";
			link.l1.go = "Himenes_church_20b";
		break;
		
		case "Himenes_church_20b":
			dialog.text = "Kellemetlen persze, hogy ilyen szerencsétlen sors érte honfitársait. De hálás vagyok, hogy ismét a mi oldalunkra állt.";
			link.l1 = "Nem volt könnyû, Rodrigo. A normális emberek árulásnak fogják nevezni, és igazuk lesz.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "Ez az én földem, Rodrigo. Mindig meg kell védeni, és nem számít, kitôl.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Megértem, kapitány. Engedje meg, hogy röviden ismertessem a településünkön a távolléte alatt kialakult helyzetet.";
			link.l1 = "Tényleg? Igen, uram. Várjunk csak... Kapitány?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_20_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			dialog.text = "Megértem, kapitány. Engedje meg, hogy röviden ismertessem a településünkön a távolléte alatt kialakult helyzetet.";
			link.l1 = "Tényleg? Igen, uram. Várjunk csak... Kapitány?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_21":
			dialog.text = "Nem akart megbántani. Csak Rodgar olyan finoman mondja ezt a szót, hogy én is ki akartam próbálni. Nagyon... kalózos.";
			link.l1 = "Semmi gond, csak meglepôdtem. Szóval, mi történt itt?";
			link.l1.go = "Himenes_church_22";
		break;
		
		case "Himenes_church_22":
			dialog.text = "Elôször is, felépítettük a templomot. Egy perc az egész, gyere be. Van itt valami látnivaló. Nagy tettet hajtott végre, kapitány. Lehet, hogy nektek nem úgy tûnik, de az, hogy Istennel kommunikálni tudunk, nagyon-nagyon fontos számunkra. Ettôl a naptól fogva az Isla Monát a hogarunknak hívjuk.";
			link.l1 = "Hogar, dulce hogar? Mindenképpen megnézem. A semmiért cipeltem azt a sok gyertyát?";
			link.l1.go = "Himenes_church_23";
		break;
		
		case "Himenes_church_23":
			dialog.text = "Nem a semmiért! Másodszor, a gyár tönkrement - elvesztettük az összes munkaerôt. Új rabszolgákat kell hoznod. Szerencsére a munka hatékonyságának újraértékelése után arra a következtetésre jutottunk, hogy tíz rabszolga több mint elég lesz. Így kevesebb gondotok lesz.";
			link.l1 = "Rendben. Még valami?";
			link.l1.go = "Himenes_church_24";
		break;
		
		case "Himenes_church_24":
			dialog.text = "Minden készen áll az ünnepségre. Nos, majdnem: itt még ki kell takarítanunk, el kell temetnünk a szerencsétlen lelkek testét... Szóval gyertek holnap a templomba, és elkezdjük.";
			link.l1 = "A templomba? Furcsa hely a buli kezdetére. Meg akarod kérni a kezem, Rodrigo?";
			link.l1.go = "Himenes_church_25";
		break;
		
		case "Himenes_church_25":
			dialog.text = "Ha-ha! Nem, kapitány, bár néhány lányunk nem bánná. Nem bánjuk, ha megteszed.";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && IsOfficer(characterFromId("Mary")))
			{
				link.l1 = "";
				link.l1.go = "Himenes_church_25_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && IsOfficer(characterFromId("Helena")))
				{
					link.l1 = "";
					link.l1.go = "Himenes_church_25_2";
				}
				else
				{
					link.l1 = "Megegyeztünk, holnap eljövünk a templomba. Imádkozni, természetesen.";
					if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common") || CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) link.l1.go = "Himenes_church_28";
					else link.l1.go = "Himenes_church_26";
				}
			}
		break;
		
		case "Himenes_church_25_1":
			DialogExit();
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_25_2":
			DialogExit();
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_26":
			dialog.text = "És még valami, kapitány. Az ünnepség elôtt, menjetek és foglalkozzatok elôször a fogollyal. A döntést meg kell hozni, és úgy tudom, hogy amúgy is kellemetlen lesz.";
			link.l1 = "Rendben van. Azonnal megyek.";
			link.l1.go = "Himenes_church_27";
		break;
		
		case "Himenes_church_27":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_factoria", "reload", "reload1", "IslaMona_DefFraPrisoner"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_28":
			DialogExit();
			WaitDate("", 0, 0, 0, 3, 5); //крутим время
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			IslaMona_DefBattleLightClear();
			DoQuestReloadToLocation("IslaMona_town", "quest", "detector1", "");
		break;
		
		case "Himenes_church_29":
			dialog.text = "Mindenki itt van! Senor, nem tudjuk, mit akart eredetileg ettôl a helytôl, és hogyan látja most magának. Számunkra ez elôször kényszerû menedék volt, most pedig igazi otthonná vált. Itt élnek az önök tengerészei, kalózai és szökött spanyol eretnekek. A világ bármely más helyén már elvágtuk volna egymás torkát. De itt barátok vagyunk, dolgozunk és élvezzük az életet. Az Isla Mona egyikünk számára sem a végsô pont a világ térképén, de talán itt töltjük majd életünk legboldogabb és legtermékenyebb éveit. És ez a ti érdemetek, a ti földetek és a ti népetek. Muchas gracias, "+pchar.name+"!";
			link.l1 = "";
			link.l1.go = "Himenes_church_30";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_30":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_86";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		case "Himenes_church_31":
			dialog.text = "Rendben, rendben. Kapitány, ajándékokat gyûjtöttünk neked - rengeteg hasznos és egyszerûen kellemes dolgot. Néhányat magunkkal hoztunk, néhányat pedig magunk készítettünk. Fogadd el ezt az ajándékot tiszta szívvel, a többit pedig a mi kemény munkánkkal adjuk neked.";
			link.l1 = "Köszönjük... Erre nem számítottam. Ilyen kevés fényes pillanat és egyszerû emberség az odüsszeiámon... Ez sokat jelent nekem, higgyétek el.";
			link.l1.go = "Himenes_church_32";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_32":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "GunEchin", 10);
			TakeNItems(pchar, "slave_01", 10);
			TakeNItems(pchar, "grenade", 10);
			TakeNItems(pchar, "obereg_7", 1);
			TakeNItems(pchar, "purse3", 1);
			TakeNItems(pchar, "jewelry47", 1);
			TakeNItems(pchar, "jewelry52", 1);
			TakeNItems(pchar, "berserker_potion", 1);
			TakeNItems(pchar, "potion5", 10);
			TakeNItems(pchar, "cannabis7", 1);
			dialog.text = "És most - vissza a munkához!";
			link.l1 = "Nem, most már - a kocsmába! Rodrigo, menjünk!";
			link.l1.go = "Himenes_church_33_1";
			link.l2 = "Igen, élvezzük ki még egy kicsit ezt a csodálatos pillanatot.";
			link.l2.go = "Himenes_church_33_2";
		break;
		
		case "Himenes_church_33_1":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_Town", "sit", "sit_base2", "IslaMona_ChurchToTavern"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_33_2":
			DialogExit();
			LAi_SetActorType(pchar);
			ChangeShowIntarface();
			ResetSound();
			SetMusic("music_terrain");
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;
			pchar.GenQuest.FrameLockEsc = true;
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("IslaMona_ChurchTavernExit", 45.0);
		break;
		
		case "Himenes_74":
			dialog.text = "Ha-ha! Hic!";
			link.l1 = "Egyébként látom, hogy már majdnem abbahagytad a vad nevetést mindenen és semmin. A Karib-tenger friss levegôje?";
			link.l1.go = "Himenes_75";
		break;
		
		case "Himenes_75":
			dialog.text = "Inkább Rodgar romboló hatása. Ôt figyelve megtanultam, hogy mandar todo al carajo.";
			link.l1 = "";
			link.l1.go = "Himenes_76";
		break;
		
		case "Himenes_76":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_90";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_77":
			dialog.text = "Sok tiszteletreméltó embert ismerek onnan.";
			link.l1 = "";
			link.l1.go = "Himenes_78";
		break;
		
		case "Himenes_78":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_93";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_79":
			dialog.text = "Nem, inkább iszom a rumot és bámulom magát.";
			link.l1 = "";
			link.l1.go = "Himenes_80";
		break;
		
		case "Himenes_80":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_96";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_81":
			dialog.text = "Kapitány! Hic!";
			link.l1 = "Üdvözlöm magát is, Rodrigo. Látom, eseménydús estéd volt.";
			link.l1.go = "Himenes_82";
		break;
		
		case "Himenes_82":
			dialog.text = "Jobb, ha... ne is kérdezd. Egy hónapig... nem fogok inni. Egy hónapig nem iszom. Híreim vannak! A kapitány... észhez tért.";
			link.l1 = "Az egyetlen túlélô spanyol?";
			link.l1.go = "Himenes_83";
		break;
		
		case "Himenes_83":
			dialog.text = "Hic! Jaj! Igen, a Factoriában helyezték el, egy ôrzött házban.";
			link.l1 = "Igen, persze. Elmegyek hozzá. Vigyázz, hogy ne vidd túlzásba.";
			link.l1.go = "Himenes_84";
		break;
		
		case "Himenes_84":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10); /// ОН ИДЕТ НА ВЫХОД, ПОСТАВИТЬ ПРАВИЛЬНЫЙ ЛОКАТОР
			IslaMona_ChurchSetHispanos();
		break;
		
		case "Himenes_85":
			dialog.text = "Úsztam egyet, és minden olyan jó, mint újkorában! Élni és dolgozni fogunk. Megpróbálom a lehetô leghosszabb ideig mûködtetni a Factoriát. Hát, és javításokat, kisebb építési munkákat végezni. Talán még a gyerekekrôl is döntünk az enyémmel.";
			link.l1 = "Örülök mindannyiótoknak! Nagyon ideges, költséges... és csodálatos kaland volt, és örülök, hogy nekünk sikerült. Sok szerencsét mindenkinek, és a vitorlát bontóknak még több szerencsét!";
			link.l1.go = "Himenes_86";
		break;
		
		case "Himenes_86":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_Final", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// солдат в бухте
		case "Capral":
			dialog.text = "Állj! Tizedes "+GetFullName(npchar)+". Harci zónában szállt le! Azonnal azonosítsa magát, és mondja meg, hogy miért van itt!";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Tizedes, álljon le! "+GetFullName(pchar)+", a francia haditengerészet kapitánya. Parancsolom, hogy kísérjen el a fôtisztjéhez. Hajtsa végre a parancsot!";
				link.l1.go = "Capral_1";
			}
			else
			{
				link.l1 = ""+GetFullName(pchar)+", a '"+pchar.ship.name+"'nevû hajó kapitánya. Teljesen véletlenül érkezett erre a szigetre - esetleges javítások és az édesvízkészletek feltöltése miatt.";
				link.l1.go = "Capral_3";
			}
		break;
		
		case "Capral_1":
			if(IsUniformEquip())
			{
				dialog.text = "Igen, uram, kapitány! Kérem, kövessenek. Könyörgöm, legyen óvatos! Ez a sziget hemzseg a banditáktól.";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Elnézését kérem, kapitány. Ön nincs egyenruhában, így kénytelen vagyok ellenôrizni a tiszti szabadalmát.";
				link.l1 = "Nézze. Elégedett? Most pedig - siessen a parancs végrehajtásával, tizedes!";
			}
			link.l1.go = "Capral_2";
		break;
		
		case "Capral_2":
			DialogExit();
			AddQuestRecord("IslaMona", "16");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 20.0);
		break;
		
		case "Capral_3":
			dialog.text = "Velem kell jönnie, kapitány. A rangidôs tisztünk beszélni fog önnel. Ettôl a pillanattól kezdve a hajóját úgy tekintjük, hogy ideiglenesen a francia haditengerészet igényeihez van rendelve. Azonnal értesítse az aktuális ôrséget és kövessen engem.";
			link.l1 = "A Charle Prince nevû hajóra van szükséged? Nem hinném!";
			link.l1.go = "Capral_5";
			link.l2 = "Úgy tûnik, nincs más választásom. Azt teszem, amit mond.";
			link.l2.go = "Capral_4";
		break;
		
		case "Capral_4":
			DialogExit();
			AddQuestRecord("IslaMona", "18");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 5.0);
		break;
		
		case "Capral_5":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_DefKillCapral", 1.0);
		break;
		
		case "Capral_6":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Kapitány úr, az ellenséges táborhoz vezetô út jobbra van tôlünk. Elkísérem önöket.";
				link.l1 = "Álljon le, tizedes. Inkább megyek egyedül.";
			}
			else
			{
				dialog.text = "Kapitány, az út az ellenséges táborhoz jobbra van tôlünk. Nem fog eltévedni.";
				link.l1 = "Köszönöm az aggodalmát.";
			}
			link.l1.go = "Capral_7";
		break;
		
		case "Capral_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			IslaMona_DefGotoMarch();
			pchar.quest.islamona_def_killslaves.win_condition.l1 = "location";
			pchar.quest.islamona_def_killslaves.win_condition.l1.location = "IslaMona_town";
			pchar.quest.islamona_def_killslaves.function = "IslaMona_DefKillSlaves";
		break;
		
		case "FraOfficer":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Kapitány "+GetFullName(pchar)+"! Hála Istennek! Engedjék meg, hogy bemutatkozzam - hadnagy "+GetFullName(npchar)+". Az önök nagy tisztelôje! Nem tudom, mit keres ezen a nyomorult földdarabon, de éppen jókor jött!\nMeg kell mondanom, kapitány úr, ön nagyon népszerû lett a tisztikarunk körében. Bár sokakat bosszant az ön... 'speciális' szolgálati stílusa, abban mindenki egyetért, hogy az ön szabadalma erôsebbé teszi a flottánkat. Jelenleg teljesen patthelyzetben vagyunk, így egy olyan ember segítségét, mint te, nehéz lesz túlbecsülni!";
				link.l1 = "Mit tehetek? És mi folyik itt?";
				link.l1.go = "FraOfficer_1";
			}
			else
			{
				dialog.text = "Kapitány "+GetFullName(pchar)+". A flottajelentésekben többször is megemlítették a nevét. És mindig nagyon kétes fényben. Most azonban lehetôséged van arra, hogy megszakítsd ezt a kevésbé tiszteletre méltó tendenciát, és a hazát szolgáld.";
				link.l1 = "Mit tehetek? És mi folyik itt?";
				link.l1.go = "FraOfficer_8";
			}
		break;
		
		case "FraOfficer_1":
			dialog.text = "A 'Warrior', rutinfeladaton voltunk - különösen merész spanyol fosztogatókra vadászva. Az ügy általában nagyon egyszerû: a kém megadja a területet és a célpont adatait, te pedig elkapod a horizont alól. Nincs semmi különös, és az egésznek nagyon rossz vége lett: a spanyolok találtak ránk elôször, és támadtak, annak ellenére, hogy ôk maguk is egy korvettre szálltak. Ha valami komolyabbat kaptunk volna, nem mentünk volna magunkkal a fenékre... de legalább sikerült felrobbantani az egész hajótestüket. Csak az én osztagom élte túl. A kasztíliaiaknál azonban szintén volt valaki, aki túlélte. De nem sokáig, haha!";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "A fregatt 'Warrior'? Shocke kapitány meghalt?";
				link.l1.go = "FraOfficer_1_1";
			}
			else
			{
				link.l1 = "";
				link.l1.go = "FraOfficer_2";
			}
		break;
		
		case "FraOfficer_1_1":
			dialog.text = "Nem vagyok meglepve, hogy kérdezett róla, kapitány úr. Hallottam, hogy részt vett a 'Alcantara'. elfogásában, nagyszerû teljesítmény, már akkor megalapozta a szabadalmát! Shocke parancsnok nem halt meg, épp ellenkezôleg! Elôléptették, és kérésére a Földközi-tengerre küldték szolgálatra. Csak irigyelhetjük ôt most a miénkhez hasonló helyzetben. Szóval, ami a mi helyzetünket illeti...";
			link.l1 = "";
			link.l1.go = "FraOfficer_2";
		break;
		
		case "FraOfficer_2":
			dialog.text = "Találtunk egy települést a szigeten - eléggé benépesített rablóbarlang - csak figyelj - kalózok és spanyolok számára. Hihetetlen! Tudod, általában ezek a fattyak csak egymást vagdossák és akasztják, de itt - lám: a szigetvilág kellôs közepén, mint egy család, együtt dolgoznak a kalózfa kitermelésén. Láttad a mólót, amit építettek maguknak? Erre a fajtára nem evezôs csónakokon érkeznek a vendégek. A feladatunk rendkívül egyértelmû: a segítségeddel elfoglaljuk a települést, elvisszük a kalózfát és a foglyokat, te pedig mindenkit elviszel Capsterburgba. Addig is a hatóságok majd kitalálnak maguknak valamit... És amíg ôk kitalálják, addig mi elintézzük a kalózfát, és rendesen megünnepeljük az otthoni századom többi tisztjével!";
			link.l1 = "Mi akadályozott meg abban, hogy mostanra egyedül foglaljátok el a települést?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_3":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "Valószínûleg sokkal több bandita van, mint mi - láttunk sátrakat a parton. És a sátrak mellett van faluk, kapujuk, ágyújuk is!";
			else sTemp = "Valószínûleg nincsenek olyan sokan a banditák, különben már rég kirúgtak volna minket innen, de nekik még van faluk, kapujuk, ágyújuk és rengeteg idejük!";
			dialog.text = "Mi akadályozott meg bennünket?! Csak tizenkét fusziliánk és hét matrózunk van. Mind fáradtak és kimerültek. Csak öt muskétát mentettünk meg, legjobb esetben is csak egy-egy töltényt! "+sTemp+"";
			link.l1 = "De van valami terved?";
			link.l1.go = "FraOfficer_4";
		break;
		
		case "FraOfficer_4":
			dialog.text = "Figyelj, nem vesztegettük az idôt. Elôször is elfoglaltuk ezt a gyárat, így zsákmányoltunk némi élelem- és vízkészletet, és ami a legfontosabb - egy teljes raktárnyi kalózfát és több mint egy tucat rabszolgát! A rabszolgákat amúgy sem tudtuk volna ôrizni, ezért azonnal harci felderítést végeztünk, és muskétáink fedezékében elküldtük ôket, hogy támadják meg korábbi gazdáikat. Így tudtuk meg, hogy a banditáknak van fegyverük.";
			link.l1 = "Jól értem, hogy most engem és az embereimet akarsz a rabszolgák helyett erre a fegyverre küldeni?";
			link.l1.go = "FraOfficer_5";
		break;
		
		case "FraOfficer_5":
			dialog.text = "Nem, de a banditákhoz mehetsz tárgyalni. Az érkezésed azt jelenti, hogy a búvóhelyük leleplezôdött, és most a király katonáinak van egy hajójuk és erôsítésük. Nos, amíg ôk lógatják a fülüket, és felmérik a mélységüket, addig te minél közelebb mész a fegyverhez, dobsz alá egy kézigránátot, és nem hagyod magad megölni, amíg a mi embereink és a te embereid nem közelednek. Ha nem vagy biztos benne, hogy meg tudod oldani, próbáld meg magad helyett az egyik emberedet küldeni.";
			link.l1 = "Engedje meg, hogy elôször én menjek oda hozzájuk bomba nélkül, és ajánljam fel nekik, hogy adják meg magukat. Körülnézek, megértem a hangulatukat és az erejüket, kételyt vetek a lelkükbe. Ha nem adják meg magukat, akkor újra odamegyek hozzájuk, de már bombával.";
			if (CheckCharacterItem(pchar, "patent_fra")) link.l1.go = "FraOfficer_6";
			else link.l1.go = "FraOfficer_6_1";
		break;
		
		case "FraOfficer_6":
			GiveItem2Character(pchar, "grenade");
			//Log_Info("Вы получили гранату");
			PlaySound("interface\important_item.wav");
			dialog.text = "... és addigra már hozzád is hozzászoktak, így könnyebb lesz a szabotázst végrehajtani! Okos! Nos, nem is vártam mást magától, kapitány. Folytassa, ha készen áll. De akkor is, itt... Ez még jól jöhet.";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_6_1":
			dialog.text = "... és addigra már hozzászoktak, így könnyebb lesz a szabotázs végrehajtása. Ezt fogjuk tenni. Folytassátok!";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_7":
			DialogExit();
			AddQuestRecord("IslaMona", "19");
			chrDisableReloadToLocation = false;
			pchar.quest.islamona_def_goout.win_condition.l1 = "location";
			pchar.quest.islamona_def_goout.win_condition.l1.location = "IslaMona_Jungle_01";
			pchar.quest.islamona_def_goout.function = "IslaMona_DefCapralTalk";
		break;
		
		case "FraOfficer_8":
			dialog.text = "Ezen a területen hosszan tartó harc folyt a spanyolokkal. Mindkét hajó elsüllyedt, és a túlélôk itt kötöttek ki. Többnyire franciák, de néhány ellenségünknek is sikerült túlélnie. És ennél többet nem kell tudnia, sajnálom, kapitány. Titkos információ, érti.";
			link.l1 = "Megértettem.";
			link.l1.go = "FraOfficer_9";
		break;
		
		case "FraOfficer_9":
			dialog.text = "Találtunk egy települést a szigeten - eléggé benépesített banditák barlangja - csak figyeljen - kalózok és spanyolok számára. Hihetetlen! Tudja, általában ezek a fattyúk csak egymást vagdossák és akasztják, de itt - íme: a szigetvilág kellôs közepén, mint egy család, együtt dolgoznak a kalózfa kitermelésén. Láttad a mólót, amit építettek maguknak? Erre a fajtára nem evezôs csónakokon érkeznek a vendégek. A feladatunk rendkívül egyértelmû: a segítségeddel elfoglaljuk a települést, elvisszük a kalózfát és a foglyokat, te pedig mindenkit elviszel Capsterburgba. Addig is a hatóságok majd kitalálnak maguknak valamit... És amíg ôk rájönnek, talán még arra is kész vagyok, hogy lehetôséget adjak nektek, hogy értékes faanyagot vegyetek magatokhoz.";
			link.l1 = "Mi akadályozott meg abban, hogy mostanra egyedül foglaljátok el a települést?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_10":
			dialog.text = "Tessék, tessék! Van valami hír?";
			link.l1 = "Ez egy tiszteletbeli ôrség?";
			link.l1.go = "FraOfficer_11";
		break;
		
		case "FraOfficer_11":
			dialog.text = "Nyilvánvalóan hamarosan döntés születik a további teendôinkrôl. Nem szeretném az embereimet az egész szigeten keresni, hogy újabb parancsokat adjak ki.";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Kiváló kezdeményezés! Megkapják a parancsokat. Felderítést végeztem: az ellenség gyenge, az ágyúból pedig elfogyott a lôszer. Parancsolom, hogy azonnal támadja meg a banditák búvóhelyét, hadnagy úr. Ne ápolja a kezét. Csak egy újabb nap a flottában. Végrehajtani!";
				link.l1.go = "FraOfficer_12";
			}
			else
			{
				link.l1 = "Véleményem szerint a 'slave' reconnaissance után rögtön erôszakkal is elfoglalhatták volna ôket. A védelmük nevetséges, csak pár komoly harcos. Nem kell túlgondolni - egy vasfahegyen ülve trófeabort iszogathattunk volna.";
				link.l1.go = "FraOfficer_14";
			}
		break;
		
		case "FraOfficer_12":
			dialog.text = "Megerôsítve, kapitány!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_13";
		break;
		
		case "FraOfficer_13":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -25);
			AddQuestRecord("IslaMona", "22");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_14":
			dialog.text = "És ezek a felderítés eredményei? Megértem, hogy furcsa lehet túl sokat várni egy nem katonai személytôl, de nekem tényekre van szükségem! Tényekre, kapitány, nem a véleményére!";
			link.l1 = "Megsértett, hadnagy. Jelentést!";
			link.l1.go = "FraOfficer_15";
		break;
		
		case "FraOfficer_15":
			dialog.text = "";
			link.l1 = "Most éppen egy spanyol hajó túlélô kapitánya van önnel, akit elsüllyesztett. Egy tapasztalt parancsnok, aki hamarosan felépül. Ha késlekedik, felépül és megszervezi a védelmet a hadtudomány könyvei szerint, és akkor nehéz dolgunk lesz. Sietnünk kell - ismétlem, gyengék és demoralizáltak.";
			link.l1.go = "FraOfficer_15_1";
			link.l2 = "Hamarosan jön az erôsítés - hogy bevegyük a bakonyi erdôt. Nem hiszem, hogy ez blöff: te magad is láttad a dokkokat és egy halom szállítókész árut a gyár raktárában. Sietnünk kell - ismétlem, gyengék és demoralizáltak. Ha késlekedünk, megvárjuk egy kalózhajó érkezését.";
			link.l2.go = "FraOfficer_15_2";
			link.l3 = "Ennek a lyuknak a lakóinak majdnem a fele nô. Még csak nem is a milícia ellen harcoltok: egész idô alatt nem volt több mint egy tucat harcos ellenetek. Gyengék és demoralizáltak.";
			link.l3.go = "FraOfficer_15_3";
			link.l4 = "Az ágyúból kifogyott a lôszer. Elég ágyút láttam már életemben, és meg tudom mondani, mikor áll készen a legénység a tüzelésre, és mikor nem. A tüzérségük nélkül csak szegény harcosok; gyengék és demoralizáltak.";
			link.l4.go = "FraOfficer_15_4";
			link.l5 = "Gondoljon a trófeákra és a dicsôségre, hadnagy úr! Egyéni gyôzelem egy spanyol fosztogató felett, egy bandita fészek elfoglalása és egy egyedülálló kalózfaforrás - mindez a saját hajó parancsnokságáért kiált! Ismétlem, gyengék és demoralizáltak, itt az ideje, hogy szétzúzzuk ôket!";
			link.l5.go = "FraOfficer_15_5";
		break;
		
		case "FraOfficer_15_1":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				notification("Képességellenôrzés megfelelt", SKILL_LEADERSHIP);
				dialog.text = "Köszönöm, kapitány. Ez értékes információ, és igazad volt, itt nincs okunk késlekedni. Az embereim mind itt vannak, erôsek, kiképzettek és készen állunk. Fél órán belül mindennek vége lesz. Kapitány, kérem, készüljön fel az emberek, a foglyok és a rakomány fogadására a hajóján. Nem fogunk itt sokáig idôzni.";
				link.l1 = "Minden készen áll, hadnagy. Csak önre vártunk. Viszlát késôbb!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Képességpróba Sikertelen (80)", SKILL_LEADERSHIP);
				dialog.text = "Köszönöm, kapitány. Ez értékes információ. Ebben az esetben menjen a dokkhoz, és készítse elô a beszálló csapatot. Együtt és azonnal megrohamozzuk a banditák fészkét. Az én és a te embereid közül a legjobbak fogják vezetni az elôôrsöt - ôk lesznek azok, akik elfoglalják a kapukat. A többit majd megbeszéljük, miután közösen ellenôriztük az erôinket. Ne hagyj cserben engem és az országodat, "+GetFullName(pchar)+".";
				link.l1 = "...úgy legyen. Viszlát késôbb, hadnagy.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_2":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputáció ellenôrzés átment", "None");
				notification("Képességellenôrzés megfelelt", SKILL_LEADERSHIP);
				dialog.text = "Köszönöm, kapitány. Ez értékes információ, és igazad volt, itt nincs okunk késlekedni. Az embereim mind itt vannak, erôsek, kiképzettek és készen állunk. Fél órán belül mindennek vége lesz. Kapitány, kérem, készüljön fel az emberek, a foglyok és a rakomány fogadására a hajóján. Nem fogunk itt sokáig idôzni.";
				link.l1 = "Minden készen áll, hadnagy. Csak önre vártunk. Viszlát késôbb!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Túl alacsony a hírneve! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Képességpróba Sikertelen (60)", SKILL_LEADERSHIP);
				dialog.text = "Köszönöm, kapitány. Ez értékes információ. Ebben az esetben menjen a dokkhoz, és készítse elô a beszálló csapatot. Együtt és azonnal megrohamozzuk a banditák fészkét. Az én és a te embereid közül a legjobbak fogják vezetni az elôôrsöt - ôk lesznek azok, akik elfoglalják a kapukat. A többit majd megbeszéljük, miután közösen ellenôriztük az erôinket. Ne hagyj cserben engem és az országodat, "+GetFullName(pchar)+".";
				link.l1 = "...úgy legyen. Viszlát késôbb, hadnagy.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 70 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputáció ellenôrzés átment", "None");
				notification("Képességellenôrzés megfelelt", SKILL_LEADERSHIP);
				dialog.text = "Köszönöm, kapitány. Ez értékes információ, és igazad volt, itt nincs okunk késlekedni. Az embereim mind itt vannak, erôsek, kiképzettek és készen állunk. Fél órán belül mindennek vége lesz. Kapitány, kérem, készüljön fel az emberek, a foglyok és a rakomány fogadására a hajóján. Nem fogunk itt sokáig idôzni.";
				link.l1 = "Minden készen áll, hadnagy. Csak önre vártunk. Viszlát késôbb!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Túl alacsony a hírneve! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Képességpróba Sikertelen (70)", SKILL_LEADERSHIP);
				dialog.text = "Köszönöm, kapitány. Ez értékes információ. Ebben az esetben menjen a dokkhoz, és készítse elô a beszálló csapatot. Együtt és azonnal megrohamozzuk a banditák fészkét. Az én és a te embereid közül a legjobbak fogják vezetni az elôôrsöt - ôk lesznek azok, akik elfoglalják a kapukat. A többit majd megbeszéljük, miután közösen ellenôriztük az erôinket. Ne hagyj cserben engem és az országodat, "+GetFullName(pchar)+".";
				link.l1 = "...úgy legyen. Viszlát késôbb, hadnagy.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_4":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputáció ellenôrzés átment", "None");
				notification("Képességellenôrzés megfelelt", SKILL_LEADERSHIP);
				dialog.text = "Köszönöm, kapitány. Ez értékes információ, és igazad volt, itt nincs okunk késlekedni. Az embereim mind itt vannak, erôsek, kiképzettek és készen állunk. Fél órán belül mindennek vége lesz. Kapitány, kérem, készüljön fel az emberek, a foglyok és a rakomány fogadására a hajóján. Nem fogunk itt sokáig idôzni.";
				link.l1 = "Minden készen áll, hadnagy. Csak önre vártunk. Viszlát késôbb!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Túl alacsony a hírneve! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Képességpróba Sikertelen (60)", SKILL_LEADERSHIP);
				dialog.text = "Köszönöm, kapitány. Ez értékes információ. Ebben az esetben menjen a dokkhoz, és készítse elô a beszálló csapatot. Együtt és azonnal megrohamozzuk a banditák fészkét. Az én és a te embereid közül a legjobbak fogják vezetni az elôôrsöt - ôk lesznek azok, akik elfoglalják a kapukat. A többit majd megbeszéljük, miután közösen ellenôriztük az erôinket. Ne hagyj cserben engem és az országodat, "+GetFullName(pchar)+".";
				link.l1 = "...úgy legyen. Viszlát késôbb, hadnagy.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_5":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 90)
			{
				notification("Képességellenôrzés megfelelt", SKILL_LEADERSHIP);
				dialog.text = "Köszönöm, kapitány. Ez értékes információ, és igazad volt, itt nincs okunk késlekedni. Az embereim mind itt vannak, erôsek, kiképzettek és készen állunk. Fél órán belül mindennek vége lesz. Kapitány, kérem, készüljön fel az emberek, a foglyok és a rakomány fogadására a hajóján. Nem fogunk itt sokáig idôzni.";
				link.l1 = "Minden készen áll, hadnagy. Csak önre vártunk. Viszlát késôbb!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Képességpróba Sikertelen (90)", SKILL_LEADERSHIP);
				dialog.text = "Köszönöm, kapitány. Ez értékes információ. Ebben az esetben menjen a dokkhoz, és készítse elô a beszálló csapatot. Együtt és azonnal megrohamozzuk a banditák fészkét. Az én és a te embereid közül a legjobbak fogják vezetni az elôôrsöt - ôk lesznek azok, akik elfoglalják a kapukat. A többit majd megbeszéljük, miután közösen ellenôriztük az erôinket. Ne hagyj cserben engem és az országodat, "+GetFullName(pchar)+".";
				link.l1 = "...úgy legyen. Viszlát késôbb, hadnagy.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_16": // французы атакуют сами
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			AddQuestRecord("IslaMona", "24");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_17": // совместная атака
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -7);
			AddQuestRecord("IslaMona", "23");
			IslaMona_DefAttackCommon();
		break;
		
		case "FraOfficer_18":
			if (CheckCharacterItem(pchar, "patent_fra")) dialog.text = "És én, idióta, csodáltalak téged! A-agh! Franciaország büszkesége, kapitány " + GetFullName(pchar) + "!!! Méltatlan vagy a szabadalmadhoz!!!";
			else dialog.text = ""+GetFullName(pchar)+", Söpredék, áruló és átkozott kalóz! Tudhattam volna, hogy ez a nyomorult barlang a te büdös birodalmad! Franciaország nem felejt és nem bocsát meg az ilyen embereknek, mint te!";
			link.l1 = "";
			link.l1.go = "FraOfficer_19";
		break;
		
		case "FraOfficer_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_75";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FraOfficer_20":
			dialog.text = "Készen áll, kapitány? A csapata méltónak tûnik rá!";
			link.l1 = "Köszönöm, hadnagy úr. Kezdhetjük?";
			link.l1.go = "FraOfficer_21";
		break;
		
		case "FraOfficer_21":
			dialog.text = "Igen, azonnal kezdjük!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_22";
		break;
		
		case "FraOfficer_22":
			DialogExit();
			IslaMona_DefAttackCommonRun();
		break;
		
		// обиженный пират
		case "Pirate":
			dialog.text = "Ha! " + GetFullName(pchar) + "! Micsoda találkozó. Hé, kapjátok el! Ez a szemétláda mindent birtokol itt! Ez az ô szigete!";
			link.l1 = "Micsoda nap ez a mai...";
			link.l1.go = "Pirate_1";
		break;
		
		case "Pirate_1":
			DialogExit();
			IslaMona_DefCheckJungleFight();
		break;
		
		// Алонсо
		case "Alonso":
			dialog.text = "Kapitány, mik a parancsok? A jelek szerint készenlétben kell állni, és a behatoló csapatot küldeni.";
			link.l1 = "A parancs áll. Fiúk, kövessetek, meg kell tisztítanunk az otthonunkat a nemkívánatos vendégektôl. A díj az enyém, az összes trófea a tiétek!";
			link.l1.go = "Alonso_1";
		break;
		
		case "Alonso_1":
			dialog.text = "Hurrá!";
			link.l1 = "A csatára!";
			link.l1.go = "Alonso_2";
		break;
		
		case "Alonso_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_our_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common"))
			{
				pchar.quest.islamona_attack_common1.win_condition.l1 = "location";
				pchar.quest.islamona_attack_common1.win_condition.l1.location = "IslaMona_Jungle_01";
				pchar.quest.islamona_attack_common1.function = "IslaMona_DefAttackCommonPrepare";
			}
			else
			{
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", true);
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", true);
				pchar.quest.islamona_attack_force.win_condition.l1 = "location";
				pchar.quest.islamona_attack_force.win_condition.l1.location = "IslaMona_factoria";
				pchar.quest.islamona_attack_force.function = "IslaMona_DefAttackForce";
			}
		break;
		
		// испанский офицер
		case "SpaOfficer":
			dialog.text = "Üdvözlöm, senor. Ön ennek a földnek a tulajdonosa? Engedje meg, hogy bemutatkozzam, Grand Francisco de Alba, a 'Perro Marino' corvette egykori kapitánya.";
			link.l1 = "Igen, ez az én földem. Én vagyok " + GetFullName(pchar) + ", a hajó kapitánya '" + pchar.ship.name + "'. Nagy? Ilyen elôkelô vendégeink még nem voltak itt.";
			link.l1.go = "SpaOfficer_1";
		break;
		
		case "SpaOfficer_1":
			dialog.text = "Ó, Monsieur " + GetFullName(pchar) + "! A neve jól ismert. Tudja, az utóbbi idôben az ön neve olyan gyakran bukkant fel a Casa de Contratacion jelentéseiben, hogy komolyan vártam a megbízásokat, hogy önnel üzleteljek.";
			link.l1 = "Velem?";
			link.l1.go = "SpaOfficer_2";
		break;
		
		case "SpaOfficer_2":
			dialog.text = "Azt hiszem, nincs értelme színlelni. Az én feladatom, hogy felkutassam és elpusztítsam Spanyolország és Fülöp király ellenségeit a világ minden tengerén.";
			link.l1 = "Szerencse, hogy ilyen parancs még nem érkezett. Ön nyilvánvalóan nagyon képzett tengerésztiszt.";
			link.l1.go = "SpaOfficer_3";
		break;
		
		case "SpaOfficer_3":
			dialog.text = "Az a tény, hogy most félholt fogoly vagyok egy apró szigeten, ahol hemzsegnek a kalózok és a menekülô honfitársaim, csak megerôsíti a következtetésedet, ha-ha! Nagyon veszélyes ügy volt, de a parancs az parancs. Majdnem sikerült! Mélységesen sajnálom az embereimet - mindannyiukat név szerint ismertem, hosszú évekig szolgáltunk együtt. De az országomnak több fiát' vérét kell majd ontania, hogy megôrizze birodalmi státuszát. A mi családunk ezt jobban tudja, mint a legtöbben.";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "";
				link.l1.go = "SpaOfficer_4";
			}
			else
			{
				link.l1 = "Most térjünk vissza a sürgetôbb dolgokhoz. Mihez kezdjek veled, Nagyúr?";
				link.l1.go = "SpaOfficer_5";
			}
		break;
		
		case "SpaOfficer_4":
			dialog.text = "Egyébként, Monsieur de Mor, a 'Warrior' - az a kis hajó ismerôs volt önnek, ugye? A Porto Bellóban végrehajtott merész akciója nem maradt észrevétlen. Merész, sôt öngyilkos. Nagyon kellett a pénz, igazam van? Ha!";
			link.l1 = "Sokat tud rólam, Grand. De térjünk rá a sorsodra.";
			link.l1.go = "SpaOfficer_5";
		break;
		
		case "SpaOfficer_5":
			dialog.text = "Mit kell gondolni? Mint minden jó történetben, három lehetôséged van: megölsz, itt hagysz, vagy szabadon engedsz. Ha szabadon engedsz, a de Alba család szavát adom, hogy soha senkinek nem fogok beszélni errôl a helyrôl és a te részvételedrôl a kalandjaimban. Továbbá, az adósod leszek, és amíg ezt az adósságot nem törleszted, soha nem harcolok ellened.";
			link.l1 = "Nem kockáztathatom meg, Grand.";
			link.l1.go = "SpaOfficer_6";
			link.l2 = "Itt fogsz eltölteni egy kis idôt. Egyenlô feltételek mellett fogsz élni és dolgozni a honfitársaiddal.";
			link.l2.go = "SpaOfficer_7";
			link.l3 = "Üdvözöllek a hajóm fedélzetén, Grand. A Santiago világítótornyánál fogok kiszállni, ha eljön az ideje. Remélem, megtartod a szavadat.";
			link.l3.go = "SpaOfficer_8";
		break;
		
		case "SpaOfficer_6":
			dialog.text = "Megértem, senor. Nos, mindenesetre én már halott vagyok abban a csatában az embereimmel együtt. Ez egy jó befejezés.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_6_1";
		break;
		
		case "SpaOfficer_6_1":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_KillSpanish", 1.0);
		break;
		
		case "SpaOfficer_7":
			dialog.text = "Bevallom, nem szeretek félszívû lenni. De fogságban nincs szégyen, ezért elfogadom az élet ajándékát, és békében fogok élni ezekkel a kedves és láthatóan nagyon boldog emberekkel. Mindazonáltal, ha valaha is elhagyom ezt a helyet, nem tartozom neked semmivel.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_7_1";
		break;
		
		case "SpaOfficer_7_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			AddQuestRecord("IslaMona", "27");
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_8":
			dialog.text = "Szavamat adom és a de Alba család szavát! Találkozunk a hajón!";
			link.l1 = "";
			link.l1.go = "SpaOfficer_8_1";
		break;
		
		case "SpaOfficer_8_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("IslaMona", "28");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			pchar.quest.islamona_final_mayak.win_condition.l1 = "location";
			pchar.quest.islamona_final_mayak.win_condition.l1.location = "Mayak9";
			pchar.quest.islamona_final_mayak.function = "IslaMona_FinalMayakSpanish";
			pchar.questTemp.IslaMona.Mayak = "true";
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_9":
			dialog.text = "Kapitány " + GetFullName(pchar) + "! Megmentetted az életemet és visszahoztál a sajátomba. Megértem, milyen nehéz volt ilyen kockázatot vállalni - én soha nem mertem volna ilyet tenni. Tartozom önnek, senor. A szavamat adom, hogy soha senkinek nem fogok beszélni annak a szerencsétlen sorsú csatának a körülményeirôl. Ha visszatér az Óvilágba, feltétlenül keressen meg engem; a madridi családi birtokunkon mindig szívesen látjuk. Egyelôre fogadd el ezt...";
			link.l1 = "Egy térképdarabot?";
			link.l1.go = "SpaOfficer_10";
		break;
		
		case "SpaOfficer_10":
			AddMapPart();
			dialog.text = "Ez minden, ami nálam volt. Nincs kétségem afelôl, hogy a másik darabot könnyen megtalálod. Viszontlátásra! És sok szerencsét neked, barátom.";
			link.l1 = "Isten veled, Nagyúr. Emlékezz a szavadra, és sok szerencsét neked!";
			link.l1.go = "SpaOfficer_11";
		break;
		
		case "SpaOfficer_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.IslaMona.Mayak = "done";
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			AddQuestRecord("IslaMona", "29");
			CloseQuestHeader("IslaMona");
		break;
		
		// Диалоги обитателей Исламоны
		// мужское население
		case "island_man":
			dialog.text = LinkRandPhrase("Üdvözletem! Hogy van, kapitány? Jól mennek a dolgaink.","A közösségért dolgozni a legnagyobb öröm!","A szigete csodálatos, kapitány úr, és mi mindent megteszünk a boldogulásáért.");
			link.l1 = LinkRandPhrase("Ezt örömmel hallom.","Örülök, hogy minden rendben van.","Csodálom a lelkesedésedet, amigo.");
			link.l1.go = "island_man_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Ne vegye szemtelenségnek, senor, de itt élni lehetetlen.","Bármi jobb, mint az inkvizíció celláiban ülni..."),
						                               RandPhraseSimple("Köszönjük, hogy megmentett minket, kapitány.","Ezek a... kalózok a barátaid?"));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 1:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Nem rossz itt! Csak egy kicsit unalmas.","Kapitány, örülök, hogy látom. Ugorj be valamikor!"),
						                               RandPhraseSimple("Valaki koponyákat talált a parton, és elhozta a reggeli megbeszélésre. Itt mindig ilyen a helyzet?","Elárulok egy titkot, Senor Himenesnek nyilvánvalóan jót tesz a friss levegô és a biztonság, amit ez a hely nyújt."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 2:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Nem rossz itt! Csak egy kicsit unalmas.","Kapitány, örülök, hogy látom. Ugorj be valamikor!"),
						                               RandPhraseSimple("Valaki koponyákat talált a parton, és elhozta a reggeli megbeszélésre. Itt mindig ilyen a helyzet?","Elárulok egy titkot, Senor Himenesnek nyilvánvalóan jót tesz a friss levegô és a biztonság, amit ez a hely nyújt."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 3:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Isten áldja meg, kapitány!","Hetente egyszer elôadásokat tartunk a strandon és a kocsmában. Ugorjatok be valamikor."),
						                               RandPhraseSimple("A tengerészeitek folyamatosan mindenféle csecsebecséket hoznak nekünk friss ételért cserébe. Köszönjük, hogy bátorítjátok ezt.","Elképesztô, hogy ezt a helyet még nem fedezték fel. Remélem, ez így is marad."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
				}
			}
		break;
		
		case "island_man_1":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
		break;
		
		case "island_man_2":
			dialog.text = "Köszönöm, senor. Hála önnek, láttuk az igazi Újvilágot. Isten áldja önöket!";
			link.l1 = "";
			link.l1.go = "island_man_3";
			locCameraFromToPos(1.64, 1.58, -5.11, false, 2.66, 0.20, -5.74);
		break;
		
		case "island_man_3":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
			sld = characterFromId("Himenes_companion_12");
			sld.dialog.currentnode = "island_woman_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// женское население
		case "island_woman":
			dialog.text = LinkRandPhrase("Biztonság és béke - ezt szeretem itt!","Egy csodálatos paradicsom! Nos, majdnem...","Boldogok vagyunk, hogy annyi viszontagság után itt találtunk új otthonra.");
			link.l1 = LinkRandPhrase("Örülök neked és a közösségednek.","Igen, én is szeretem ezt a kis szigetet.","Jó tudni, hogy elégedett vagy.");
			link.l1.go = "island_woman_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = LinkRandPhrase("Ó... Helló.","Senor, kik azok a... durva fegyveres férfiak?","Köszönjük, hogy megmentett minket, kapitány.");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 1:
						dialog.text = LinkRandPhrase("Az embereink nagyszerû munkát végeztek - a házak kiválóak. De mi is keményen dolgoztunk!","Kapitány Úr, ne aggódjon: kis klánunk asszonyai nem félnek a nehézségektôl és az átmeneti kényelmetlenségektôl.","Micsoda levegô van itt! És a tenger! Közelebb érzed magad Istenhez!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 2:
						dialog.text = LinkRandPhrase("Az embereink nagyszerû munkát végeztek - a házak kiválóak. De mi is keményen dolgoztunk!","Kapitány Úr, ne aggódjon: kis klánunk asszonyai nem félnek a nehézségektôl és az átmeneti kényelmetlenségektôl.","Micsoda levegô van itt! És a tenger! Közelebb érzed magad Istenhez!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 3:
						dialog.text = LinkRandPhrase("Jöjjön vissza gyakrabban, Kapitány Úr. Mindig örülök, ha látom.","Senor Rodgar csodálatos mesélô. Örökké hallgathatod a beszédét!","Hehe. Azt mondják, hogy valaki a csoportunkból máris családtagot vár. Az élet megy tovább, még Isla Monán is!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
				}
			}
		break;
		
		case "island_woman_1":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
		break;
		
		case "island_woman_2":
			dialog.text = "Te... Muchas gracias, senor! Gyere gyakrabban...";
			link.l1 = "";
			link.l1.go = "island_woman_3";
			locCameraFromToPos(-1.86, 1.18, 4.51, true, -1.49, 0.20, 6.13);
		break;
		
		case "island_woman_3":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// пираты Родгара
		case "fort_pirate":
			if(npchar.location == "islamona_factoria")
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Minden rendben, Cap!","A rabszolgákat irányítás alatt tartjuk, ne aggódj."),
						                                 RandPhraseSimple("Nem kell aggódni, a lázadás kizárt.","Köszönöm a rumot! Munkához látunk!"));
			}
			else
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Spanyolok? Ezt nem vártuk tôled.","Most már egészen a tengerpartig kell gyalogolnunk, csak hogy nyugodtan aludhassunk!"),
						                                 RandPhraseSimple("Miért döntöttél így - mi, Cap?","A fônök akkoriban bízott benned - és nem tévedett. Mi megint hinni fogunk benned."));
			}
			link.l1 = "...";
			link.l1.go = "fort_pirate_1";
		break;
		
		case "fort_pirate_1":
			DialogExit();
			npchar.dialog.currentnode = "fort_pirate";
		break;
		
		// посетители таверны
		case "citizen_tavern":
			dialog.text = LinkRandPhrase("A fárasztó munka után nem bûn egy-két pohár ital...","Már majdnem végeztem és hazafelé tartok; a feleségem már biztosan vár...","Á, milyen jó munka után a kocsmánkban pihenni! Mindannyian hálásak vagyunk neked, kapitány!");
			link.l1 = LinkRandPhrase("Jó étvágyat az italhoz, compadre, ha-ha!","Nyugi, haver, csak ne vidd túlzásba, mert a feleséged leszid, ha-ha!","Nyugalom, haver, az élet nem csak a munkáról szól!");
			link.l1.go = "citizen_tavern_1";
		break;
		
		case "citizen_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "citizen_tavern";
		break;
		
		case "sailor_tavern":
			if (GetCharacterIndex("Mirabella") != -1) sTemp = "Ki az a csinos mulatt nô, aki itt lakik?";
				else sTemp = "Kapitány, szép lakásod van!";
			dialog.text = RandPhraseSimple(RandPhraseSimple("Kapitány, szép hely ez itt!", "Képzeljük el, ha hirtelen rum nélkül maradnánk. Biztosan szereznél még, nem igaz?"), RandPhraseSimple("Régóta álmodtam már egy ilyen nyaralásról. Bár egy kuplerájt imádnék... csak egy vad gondolat, Cap.", sTemp));
			link.l1 = "...";
			link.l1.go = "sailor_tavern_1";
		break;
		
		case "sailor_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_tavern";
		break;
		
		case "sailor_town":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Köszönöm a nyaralást, kapitány.", "Szép helyet építettél itt fel - van érzéked a dolgok rendben tartásához, kapitány."), RandPhraseSimple("Friss ételek, pia, szilárd talaj a lábad alatt. Ez egy álom.", "Szeretnék még egy kicsit itt maradni."));
			link.l1 = "...";
			link.l1.go = "sailor_town_1";
		break;
		
		case "sailor_town_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_town";
		break;
		
		// рабы
		case "slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Annyira fáradt vagyok - alig bírok állni.", "Nincs több erôm így élni!"), RandPhraseSimple("Ez a munka túl nehéz nekem.", "A felügyelôk egyetlen élô sejtet sem hagytak a bôrömön!"));				
			link.l1 = "";
			link.l1.go = "slave_1";
		break;
		
		case "slave_1":
			DialogExit();
			npchar.dialog.currentnode = "slave";
		break;
		
		// энкауниеры в домах
		case "HouseMan":
			dialog.text = LinkRandPhrase("Segíthetek valamiben, kapitány?","Jöjjön be, együnk egy kis helyi paellát. Csak az Isten szerelmére, ne kérdezd meg, mibôl készült!","Üdvözlöm, kapitány. Hogy tetszik itt?");
			link.l1 = "...";
			link.l1.go = "HouseMan_1";
		break;
		
		case "HouseMan_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseMan";
		break;
		
		case "HouseWoman":
			dialog.text = LinkRandPhrase("Senor, üdvözlöm!","Üdvözlöm, kapitány. Marad?","Miattam van itt? Kérem, jöjjön be, csak ne törôdjön a rendetlenséggel, senor.");
			link.l1 = "...";
			link.l1.go = "HouseWoman_1";
		break;
		case "HouseWoman_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseWoman";
		break;
	}
}