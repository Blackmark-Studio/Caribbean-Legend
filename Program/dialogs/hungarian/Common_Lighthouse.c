#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
// Jason общий диалог смотрителей маяков
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Lighthouse\" + NPChar.City + "_Lighthouse.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
    int iTest, iTemp;
	string sTemp;
	bool ok;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("A városban riadalmat keltettek. Úgy tûnik, itt az ideje, hogy én is fegyvert fogjak...", "A városôrök nem futnak utánad véletlenül?", "Itt nem találsz menedéket, de a bordáid alatt több centi hideg acélt találhatsz!"), 
					LinkRandPhrase("Mit akarsz, "+ GetSexPhrase("gazember","gazember") +"?! Az ôrök a nyomodban vannak, nem jutsz messzire, "+ GetSexPhrase("mocskos kalóz","büdös") +"!", ""+ GetSexPhrase("mocskos","mocskos") +" gyilkos! Ôrség!!!", "Nem félek tôled, "+ GetSexPhrase("görény","büdös") +"! Hamarosan felakasztanak az erôdünkben, nem jutsz messzire..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Látom, belefáradtál az életbe...", "Úgy tûnik, nincs békés ember " + XI_ConvertString("Colony" + npchar.city + "Gen") + ", mindenki hôs akar lenni!"), 
					RandPhraseSimple("Menj a pokolba!", "Heh, ezek lesznek életed utolsó másodpercei..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			//belamour legendary edtion карибские нравы
			if(npchar.quest.meeting != "0" && CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Mi szél hozta ide ezúttal?";
				link.l1 = "Azt hiszem, ismersz egy Gerard LeCroix nevû úriembert? Jutalmat kellett volna hagynia nekem...";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Jó napot, tengerész! A nevem "+GetFullName(npchar)+", és én vagyok ennek a világítótoronynak az ôre. Milyen szél hozta ide?", "Üdvözlöm! Jó ideje már, hogy utoljára új arcokat láttam a világítótornyomban... Engedjétek meg, hogy bemutatkozzam - "+GetFullName(npchar)+", és ez a világítótorony az otthonom és a munkám. Mit tehetek értetek?");
				link.l1 = "Sziasztok, "+npchar.name+"! A nevem "+GetFullName(pchar)+", hajóskapitány vagyok. Éppen sétáltam ebben a csodálatos öbölben és úgy döntöttem, hogy megállok, hogy megnézzem, ki lakik ott.";
				link.l1.go = "Lightman_meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ó, öreg barátom, kapitány "+GetFullName(pchar)+"! Gyere be, gyere be! Mi szél hozott ide ezúttal?";
				link.l1 = "Üdvözöllek, öreg só! Nem jajgatsz magányosan itt a világítótornyodban?";
				link.l1.go = "Lightman_talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_meeting":
			dialog.text = "Most már tudod. Valaha én is tengerész voltam, akárcsak te, de már régen jártam utoljára hajófedélzeten. Most ez a világítótorony az én gondjaimra van bízva, és eladok néhány dolgot is...";
			link.l1 = "És pontosan mit árulsz?";
			link.l1.go = "trade_info";
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_talk":
			dialog.text = " Mi hozott ide ezúttal?";
			link.l1 = RandPhraseSimple("Elmondanád, hogy történt-e valami érdekes dolog mostanában a kolóniádon?","Már jó ideje nem voltam a szárazföldön... Mi folyik itt?");
			link.l1.go = "rumours_lighthouse";
			link.l2 = "Lássuk, mit kínálsz eladásra.";
			link.l2.go = "Trade_lighthouse";
			if (CheckAttribute(npchar, "artefact"))
			{
				if (CheckAttribute(npchar, "quest.art"))
				{
					link.l3 = "Szóval, "+npchar.name+", már meg is érkezett az amulettem?";
					link.l3.go = "Trade_artefact_3";
				}
				else
				{
					link.l3 = ""+npchar.name+", Szeretnék rendelni egy amulettet tôled.";
					link.l3.go = "Trade_artefact_1";
				}
				// калеуче
				if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "amulet" && !CheckAttribute(npchar, "quest.Caleuche"))
				{
					link.l5 = "Figyeljen, "+npchar.name+", tudom, hogy ön amulettek rendelésre történô szállításával foglalkozik. Szóval, biztosan sokat tudsz róluk. Nézze, kérem, ezt a kis izét - mit tud róla mondani?";
					link.l5.go = "Caleuche";
				}
				if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster && CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "mayak")
				{
					link.l5 = "Barátom, azért jöttem, hogy megint azokról a furcsa amulettekrôl kérdezzem...";
					link.l5.go = "Caleuche_9";
				}
			}
			link.l4 = "Van valami, amit meg akartam kérdezni tôled...";
			link.l4.go = "quests";
			link.l9 = "Csak egy pillantást vetettem rá...";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "Néha kimegyek a partra kagylókat gyûjteni, van egy szép hely nem messze innen, így mindig lehet tôlem gyöngyöt venni. Minden vihar hoz borostyánt, azt is árulom, bár sokba kerül.\nMáskor a hullámok mindenféle érdekes csecsebecséket hoznak az elsüllyedt hajókról, és a régi cimboráim is hoznak nekem különleges tárgyakat. Engem a varázslatos amulettek érdekelnek, a bölcsek jó pénzt fizetnek azokért.\nFegyvereket is kínálok különleges alkalmakkor, ne kérdezzétek, honnan szerzek. Egy városi kereskedô minden vacakot megvesz tôlem, a jó dolgokat magam adom el, miután megjavítottam és megtisztítottam.\nA rum érdekel. Nem arra a pisire gondolok, amit a helyi kocsmában bögrénként két pezóért szolgálnak fel. Igazi palackozott jamaikai rumról beszélek. Meggyógyítja és feltámasztja az embereket. Tízszer többet fizetek minden üvegért, amit hozol. Gondoljon bele.";
			link.l1 = "Figyelj, "+npchar.name+", azt mondtad, hogy vannak régi tengerész barátaid, akik elvarázsolt amuletteket hoznak neked. Lehetséges, hogy rendeljek tôled egy bizonyos amulettet? Szépen megfizetnék érte.";
			link.l1.go = "Trade_artefact";
		break;
		
		case "Trade_lighthouse":
			//иногда продает корабельные товары // Addon-2016 Jason
			npchar.quest.goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));
			npchar.quest.goodsqty = 50+hrand(100);
			if (sti(npchar.quest.goods) == GOOD_EBONY || sti(npchar.quest.goods) == GOOD_MAHOGANY) npchar.quest.goodsqty = 25+hrand(50);
			npchar.quest.goodsprice = makeint(sti(Goods[sti(npchar.quest.goods)].Cost)/4);//цена единицы товара
			npchar.quest.goodscost = sti(npchar.quest.goodsprice)*sti(npchar.quest.goodsqty);//стоимость товара
			ok = (!CheckAttribute(npchar, "goods_date")) || (GetNpcQuestPastDayParam(npchar, "goods_date") >= 10)
			if (hrand(4) == 1 && makeint(GetCharacterFreeSpace(pchar, sti(npchar.quest.goods))) > sti(npchar.quest.goodsqty) && sti(pchar.money) >= sti(npchar.quest.goodscost) && ok)
			{
				dialog.text = "Kapitány úr, nemrég partra sodortak egy csomó árut - " + GetGoodsNameAlt(sti(npchar.quest.goods)) + ". Egyes részeit a sós víz elrontotta, de " + FindRussianQtyString(sti(npchar.quest.goodsqty)) + " sikerült nagyszerû állapotban megmenteni. Akarsz venni belôle? Olcsón elajándékozom ôket, csak "+FindRussianMoneyString(sti(npchar.quest.goodsprice))+" egységenként.";
				link.l1 = "Nem. Mutasd meg a legutóbbi találkozóidat.";
				link.l1.go = "Trade_lighthouse_double";
				link.l2 = "Hm... Ôszinte ajánlat, egyetértek. Azt hiszem, némi haszonnal továbbértékesíthetem. Lássuk csak... Ez az összeg "+FindRussianMoneyString(sti(npchar.quest.goodscost))+". Így van?";
				link.l2.go = "Trade_goods";
				SaveCurrentNpcQuestDateParam(npchar, "goods_date");
			}
			else
			{
				DialogExit();
				if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
				{
					GiveItemToTrader(npchar);
					SaveCurrentNpcQuestDateParam(npchar, "trade_date");
				}
				LaunchItemsTrade(npchar, 0);
			}
		break;
		
		case "Trade_lighthouse_double":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		case "Trade_goods":
			AddCharacterGoods(pchar, sti(npchar.quest.goods), sti(npchar.quest.goodsqty));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.goodscost));
			AddMoneyToCharacter(npchar, sti(npchar.quest.goodscost));
			dialog.text = "Igaza van, kapitány. Nagyszerû üzlet! Mindketten tisztességes hasznot húztunk belôle...";
			link.l1 = "Rendben, akkor. Elküldöm a matrózokat, hogy vigyék a rakományt a hajómra. Most pedig mutasd meg, mit gyûjtöttél össze eladásra.";
			link.l1.go = "Trade_lighthouse_double";
		break;
//------------------------------------------------заказ артефактов------------------------------------------------
		case "Trade_artefact":
			if (CheckAttribute(npchar, "artefact")) // Addon-2016 Jason за дублоны
			{
				dialog.text = "Nos, nem mindet, de néhány csecsebecsét gyakrabban hozzák, mint másokat, így azt hiszem, tudnék segíteni neked. De figyelmeztetlek: minden így rendelt amulett 100 dublonnába kerül. Meg kell értened...";
				link.l1 = "Az ár nem probléma. Milyen amuletteket tudsz szállítani?";
				link.l1.go = "Trade_artefact_1";
				link.l2 = "Pff! Ennyi pénzbôl akár egy hajót is lehetne venni. Ez túl drága. Azt hiszem, egyedül is boldogulok...";
				link.l2.go = "exit_artefact";
			}
			else
			{
				dialog.text = "Nem, kapitány. Az ilyen dolgokat pusztán véletlenül lehet megtalálni, így lehetetlen elôre megrendelni ôket. És ráadásul egy kicsit kevesebbet kellene várni rájuk, mint örökké...";
				link.l1 = "Nos, ha ez a helyzet, akkor nincs mit tenni.";
				link.l1.go = "exit_artefact";
			}
		break;
		
		case "exit_artefact":
			if (CheckAttribute(npchar, "artefact")) dialog.text = "Ahogy kívánod. Gyere el hozzám, ha meggondoltad magad.";
			else dialog.text = "Szeretné megnézni, hogy mit kínálok ma eladásra, kapitány? Ha nem találsz semmi értékeset, gyere vissza hamarosan - lehet, hogy van még valami más eladó.";
			// belamour legendary edition карибские нравы -->
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				link.l1 = "Mindez persze jó, de a következôt akartam kérdezni - gondolom, ismer egy Gerard Lecroix nevû úriembert? Jutalmat kellett volna hagynia nekem...";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			link.l1 = "Mutasd meg a tárgyaidat.";
			link.l1.go = "Trade_lighthouse";
			link.l2 = "Csak mondja, milyen érdekes dolgok történtek mostanában a kolóniáján?";
			link.l2.go = "rumours_lighthouse";
			link.l3 = "A kereskedelem az kereskedelem, de kérdezni akartam valamit.";
			link.l3.go = "quests";
			link.l4 = "További szép napot, "+npchar.name+"! Örültem a találkozásnak! Majd máskor is benézek...";
			link.l4.go = "exit";
		break;
		
		case "Trade_artefact_1":
			dialog.text = "Válasszon.";
			iTemp = 1;
			string sArt;
			if (CheckAttribute(npchar, "artefact.indian")) sArt = "indian_";
			if (CheckAttribute(npchar, "artefact.amulet")) sArt = "amulet_";
			if (CheckAttribute(npchar, "artefact.obereg")) sArt = "obereg_";
			for (i=11; i>=1; i--)
			{
				sTemp = "l"+iTemp;
				link.(sTemp) = XI_ConvertString(sArt+i);
				link.(sTemp).go = sArt+i;
				iTemp++;
			}
			link.l12 = "Sajnos ebbôl a listából eddig semmi nem érdekel.";
			link.l12.go = "exit";
		break;
		
		//группа indian
		case "indian_1":
			dialog.text = "Egy vudu baba? Szereti a lôfegyvereket? Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_1";
		break;
		
		case "indian_2":
			dialog.text = "Egy puskapor tesztelô? Az éleslövészet a siker kulcsa minden csetepatéban. Szép...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_2";
		break;
		
		case "indian_3":
			dialog.text = "Egy rituális kés? Szereted az ellenséget egy nehéz széles kard erôteljes suhintásaival vagdosni? Akkor ez neked való. Jó... ";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_3";
		break;
		
		case "indian_4":
			dialog.text = "Egy rúdbalta? Egy hatalmas fejsze felülrôl lefelé irányuló csapása bármelyik ellenséget összezúzza! Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_4";
		break;
		
		case "indian_5":
			dialog.text = "Egy tsantsa? Az a dolog még a legvakmerôbb kalózt is megijeszti. Nem, nem, nem, nem, nem.";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_5";
		break;
		
		case "indian_6":
			dialog.text = "Egy korallfej? Az ágyúid grapeshotja egyenesen a célpontba repül! Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_6";
		break;
		
		case "indian_7":
			dialog.text = "Púpos? A fáradhatatlanság a harcos legjobb barátja. Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_7";
		break;
		
		case "indian_8":
			dialog.text = "Xiuhtecuhtli? Hagyd, hogy az ellenséges hajó burkolata porrá omoljon! Jól van...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_8";
		break;
		
		case "indian_9":
			dialog.text = "Baldo? Tedd fel Baldót - és minden ágyúgolyó egyenesen a célpontba repül! Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_9";
		break;
		
		case "indian_10":
			dialog.text = "Cascavella? A kígyóméreg a legveszélyesebb dolog. A kígyó kígyója a legveszélyesebb.";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_10";
		break;
		
		case "indian_11":
			dialog.text = "Ngombo maszk? Tedd le az ellenségeid éberségét, ha-ha! Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_11";
		break;
		
		//группа amulet
		case "amulet_1":
			dialog.text = "Ngombo pajzs? Ha nem sikerült kikerülnöd egy golyót, ez az amulett megmentheti az életed. Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_1";
		break;
		
		case "amulet_2":
			dialog.text = "Euchologion? Egy jó ima még egy golyót is el tud téríteni. Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_2";
		break;
		
		case "amulet_3":
			dialog.text = "Egy feszület? Ez nagyban segíti a keresztényt a közelharcban. Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_3";
		break;
		
		case "amulet_4":
			dialog.text = "El Trozo? Ez egy halálos sebet csak egy karcolássá tesz. Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_4";
		break;
		
		case "amulet_5":
			dialog.text = "Sogbo? És az ágyúk mindig legyenek harcra készen! Jól van...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_5";
		break;
		
		case "amulet_6":
			dialog.text = "Madonna? A Legszentebb Szûz arca erôs gyógyító tulajdonságokkal rendelkezik. Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_6";
		break;
		
		case "amulet_7":
			dialog.text = "Szentelt víz? Még egy szenteltvízzel meglocsolva még egy gyengébôl is epikus hôs lesz! Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_7";
		break;
		
		case "amulet_8":
			dialog.text = "Egy horgony? És a hajód még egy ágyúgolyósorozat alatt is a víz felett maradjon, ha-ha! Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_8";
		break;
		
		case "amulet_9":
			dialog.text = "Encolpion? A vitorláid nem félnek a széltôl, amíg ez az amulett a birtokodban van. Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_9";
		break;
		
		case "amulet_10":
			dialog.text = "Csodamûvész? Az Úr vigyázzon legénységedre mind a szárazföldön, mind a tengeren! Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_10";
		break;
		
		case "amulet_11":
			dialog.text = "Cimaruta? A muskétagolyók a fejed fölött repülnek, és nem okoznak kárt! Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_11";
		break;
		
		//группа obereg
		case "obereg_1":
			dialog.text = "Teredo? Minden hajóépítô errôl álmodik. Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_1";
		break;
		
		case "obereg_2":
			dialog.text = "Xochipilli? Azzal megspórolhatsz egy kis idôt a vitorlák stoppolásával. Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_2";
		break;
		
		case "obereg_3":
			dialog.text = "Egy majom? Egy öszvér, azt mondanám! Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_3";
		break;
		
		case "obereg_4":
			dialog.text = "Gypsy legyezôje? Tegye a szemellenzôt egy járôr szemére! Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_4";
		break;
		
		case "obereg_5":
			dialog.text = "Egy jáde teknôs? Az az ászod a kártyapakliban! Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_5";
		break;
		
		case "obereg_6":
			dialog.text = "Egy majom ökle? Ahogy mondani szokták - érd el, hogy tiszteljenek téged! Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_6";
		break;
		
		case "obereg_7":
			dialog.text = "Egy halász? Ez minden navigátor álma. Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_7";
		break;
		
		case "obereg_8":
			dialog.text = "Kereskedôi gyöngyök? A pénz szereti, ha megszámolják, nem igaz? Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_8";
		break;
		
		case "obereg_9":
			dialog.text = "Ehecatl? Bármilyen alacsony sebességû öreg teknô gyorsabban repül, mint a szél! Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_9";
		break;
		
		case "obereg_10":
			dialog.text = "Tengerész fülbevaló? Azt add a kormányosodnak! Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_10";
		break;
		
		case "obereg_11":
			dialog.text = "Zarándok? Az ellenszélbôl hátszél lesz. Jó...";
			link.l1 = "Mikor jöjjek vissza a rendelésemért?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_11";
		break;
		
		case "Trade_artefact_2":
			dialog.text = "Két hónap múlva, nem hamarabb. Azt hiszem, addigra már elhozzák nekem. Szóval két hónap múlva várom a pénzzel.";
			link.l1 = "Nagyszerû! Ott leszek! Köszönöm, "+npchar.name+"!";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "art_date");
			npchar.quest.artday = rand(20)+50;
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "1");
			ReOpenQuestHeader(sTemp);
			AddQuestUserData(sTemp, "sAml", XI_ConvertString(npchar.quest.art)); // dlc
		break;
		
		case "Trade_artefact_3":
			if (CheckAttribute(npchar, "art_date") && GetNpcQuestPastDayParam(npchar, "art_date") >= sti(npchar.quest.artday))
			{
			dialog.text = "Igen, megvan. Készítettél 100 dublont, kapitány?"; // Addon-2016 Jason
				// belamour legendary edition -->
				if(PCharDublonsTotal() >= 100) 
				{
					link.l1 = "Persze! Tessék, ahogy megbeszéltük.";
					link.l1.go = "Trade_artefact_4";
				}
				else
				{
					link.l1 = "Ó, a hajón felejtettem a pénzt! Mindjárt hozom.";
					link.l1.go = "exit";
				}
				// <-- legendary edition
			}
			else
			{
			dialog.text = "Még nem. Jöjjön el hozzám késôbb. És ne aggódj - az amuletted biztosan megérkezik.";
			link.l1 = "Rendben.";
			link.l1.go = "exit";
			}
		break;
		
		case "Trade_artefact_4":
			RemoveDublonsFromPCharTotal(100); // Addon-2016 Jason
			Log_Info("Adtál 100 dublont.");
			dialog.text = "Úgy tûnik, minden rendben van. Itt az amuletted. Sok szerencsét hozzá!";
			link.l1 = "Köszönöm, "+npchar.name+"!";
			link.l1.go = "Trade_artefact_5";
		break;
		
		case "Trade_artefact_5":
			DialogExit();
			Log_Info("Megkaptad "+XI_ConvertString(npchar.quest.art)+"");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, npchar.quest.art, 1);
			DeleteAttribute(npchar, "quest.art");
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "2");
			CloseQuestHeader(sTemp);
		break;
		
		// --> калеуче
		case "caleuche":
			PlaySound("interface\important_item.wav");
			dialog.text = "Mutasd meg, hogy mi van nálad.";
			link.l1 = "Itt úgy néz ki, mint egy ôsi indiai amulett. De fogalmam sincs, hogyan kell használni, vagy mi a rejtett ereje.";
			link.l1.go = "caleuche_1";
			npchar.quest.caleuche = "true";
		break;
		
		case "caleuche_1":
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster)
			{
				dialog.text = "Jól van, jól van. Te vagy a harmadik, aki ilyet mutat nekem, haver. Ezt az amulettet Dél-Main vad szelvájáról hozták ide. Vannak indiánok Panamától nem messze, akik ilyen csecsebecséket hordanak. A vörösbôrûek azt mondják, hogy ez az ô 'nagy ôseik hagyatéka.'\nNem tudom, kik voltak az ôseik, és milyen örökséget hagytak hátra, de tudok tanácsot adni, hogy hol érdeklôdj. Érdekli?";
				link.l1 = "Természetesen!";
				link.l1.go = "caleuche_2";
				DelLandQuestMark(npchar);
				if (npchar.id == "BasTer_Lightman") DelMapQuestMarkShore("Mayak4");
				if (npchar.id == "Santiago_Lightman") DelMapQuestMarkShore("Mayak9");
			}
			else
			{
				dialog.text = "Hmm... Sok amulettet tartottam már a kezemben, de ezt most látom elôször a Karib-tengeren. Sajnálom, pajtás, nem tudok segíteni, nem értek az ilyesmihez. De ez nem egy egyszerû dolog; ez tény. Kérdezz meg valaki mást. Biztosan tudom, hogy vannak más világítótoronyôrök is, mint én, akik nem kevésbé értenek az amulettekhez.";
				link.l1 = "Bocsásson meg... Akkor folytatom a kérdezôsködést.";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_2":
			dialog.text = "Van egy karibi falu Dominikán, és a helyi fônököt Moknitekuvrinak hívják. Van egy Tuttuathapak nevû sámánjuk, egy nagy tiszteletnek örvendô indián. Ô nem a karibok közül való; ô arról a helyrôl származik, amelyrôl már meséltem nektek. Ô többet tud nálam errôl az amulettrôl mondani. De légy óvatos - Tuttuathapak gyûlöli a fehér embereket. Nagyon utálja ôket. Elvégre egyszer rabszolgasorba taszították és elvitték az otthonából...";
			link.l1 = "Gondolom, így került a Karib-szigetekre.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Igen, ez egy nagyon érdekes történet. A hajó, amely indiai rabszolgákat szállított, Marie Galante közelében holt szélcsendbe került, és a legénység fele hirtelen lázban meghalt. Mégsem betegedett meg egyetlen indián sem!\nEzután egy kapitány dühös lett, és felgyújtotta a hajóját. Ennek következtében a bebörtönzött indián lázadásba kezdett, és lemészárolta a legénységet. Kitalálod, ki volt a vezetôjük?";
			link.l1 = "Én igen...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "Ez az! Lefogadom, hogy egy sámán varázslata volt, amely a tengert holtig tartó nyugalomba helyezte, és halálos betegséggel fertôzte meg a legénységet. Ez az indián nagyon okos és nagyon veszélyes. Ha odamész hozzá - viselkedj udvariasan és vigyázz a nyelvedre - különben sok bajod lesz. Továbbá nem is fog veled szóba állni, ha nem adsz neki felajánlást.";
			link.l1 = "És milyen felajánlást kérhet?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Nem fogod megvesztegetni ôt valami szarsággal. Tudtommal a karibi katonáit fehér településekre küldi, hogy lôfegyvert vegyenek. Hozz neki ajándékba egy muskétát, és akkor, azt hiszem, elégedett lesz, és egy kis figyelmet szentel neked.";
			link.l1 = "Köszönöm! Úgy teszek, ahogy mondod... Mondd csak, haver, honnan tudod mindezt?";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "A barátom matróz volt a szerencsétlenül járt hajón. Szerencsére sikerült túlélnie azt a poklot... Láttam rajta egy olyan amulettet, mint a tiéd, úgy tûnik, a néhai kapitány is elrabolta az indiánok holmiját. Biztos vagyok benne, hogy az amuletted az ô gyûjteményébôl való - amikor a kapitány megôrült és felgyújtotta a hajóját, a matrózai megölték, majd kifosztották a kabinban lévô ládákat.";
			link.l1 = "Megértettem. Akkor csak egy ajándékkal kell elmennem Dominikára. Köszönöm a segítséget és az érdekes történetet!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Sok szerencsét, barátom, és vigyázz ezzel a vörösbôrû ördöggel...";
			link.l1 = "...";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			AddQuestRecord("Caleuche", "2");
			pchar.questTemp.Caleuche = "dominica"; 
			Caleuche_CreateShamane();
		break;
		
		case "caleuche_9":
			dialog.text = "Igen, uram? Beszéltél Tuttuathapakkal, igazam van?";
			link.l1 = "Igen, pontosan. És most még két amulettet akarok találni. Azt mondtad, én voltam a harmadik, aki megmutatta neked ezt a leletet. És ki volt a másik kettô?";
			link.l1.go = "caleuche_10";
			DelLandQuestMark(npchar);
		break;
		
		case "caleuche_10":
			dialog.text = "Az egyik a barátom, a matróz arról a hajóról, amelyik Tuttuathapakot a karibi szigetekre vitte. Azóta az incidens óta nem tette be a lábát egyetlen hajó fedélzetére sem. Egy ideje nem láttam ôt, de tudom, hol lakik. Keressétek ôt a Nyugati-fônél, Belize-ben - ô most vadászik, és a dzsungelekben kóborol. A neve Fergus Hooper.";
			link.l1 = "Jól van. És a második?";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "A másodikról csak egy kicsit tudok. Hogy Jacknek hívják-e, vagy Jacksonnak, és hogy magánzó-e, vagy kisvállalkozó, vagy egyszerûen csak kalandor. Van egy furcsa nevû xebec tulajdonosa... hmm... a neve... A fenébe, elfelejtettem! De a neve valami démoni. Megkérdeztem tôle, hogy mit jelent, mire azt mondta, hogy egy madaras nô, akit a tenger istenei születtek. Pah! Istentelen...";
			link.l1 = "Kocka... Szóval nem emlékszel a nevére?";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "Nem, villámcsapjon meg a mennydörgés, nem emlékszem. Ó, és amikor bemutatkozott, megemlítette, hogy Barbadosról származik.";
			link.l1 = "Ez nem semmi! Rendben, megpróbálom megtalálni a tollas nôk szerelmesét, amíg valaki más meg nem találja... Köszönöm, haver, sokat segítettél!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			dialog.text = "Szívesen, sapka, nézz be néha.";
			link.l1 = "Persze!";
			link.l1.go = "caleuche_14";
		break;
		
		case "caleuche_14":
			DialogExit();
			AddQuestRecord("Caleuche", "7");
			pchar.questTemp.Caleuche = "hunting"; 
			pchar.questTemp.Caleuche.Belizterms = rand(4)+3;
			pchar.quest.caleuche_prepare_beliz.win_condition.l1 = "location";
			pchar.quest.caleuche_prepare_beliz.win_condition.l1.location = "Beliz";
			pchar.quest.caleuche_prepare_beliz.function = "Caleuche_PrepareBeliz";
			AddLandQuestMark(characterFromId("Bridgetown_Portman"), "questmarkmain");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_SetOwnerType(NPChar); // belamour иначе обижается навсегда		   
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("Te "+ GetSexPhrase(" egy tolvaj vagy, kedvesem! Ôrség, fogjátok el a"," tolvajt! Ôrség, fogjátok el") +"!!!", "Hûha! Kicsit félrebámultam, és máris a mellkasodba kaptad a fejed! Fogjátok meg a tolvajt!", "ôrök! Rablás! Állítsák meg a tolvajt!");
			link.l1 = "Argh, a francba!";
			link.l1.go = "fight";
		break;
		
		// belamour legendary edition карибские нравы
		case "Trial":
			dialog.text = "Ah, szóval te vagy az a kapitány! Igen, már vártam rád. Gerard is várt, de sürgôsen el kellett mennie valamilyen expedícióra, ezért megkért, hogy utaljam át a fizetséget neked. Azt mondta, hogy el kell jönnöd. Itt van 90 dublon, ha kérhetem.");
			link.l1 = "Köszönöm! Jó dolog becsületes emberekkel üzletelni.";
			link.l1.go = "Trial_1";
		break;
		
		case "Trial_1":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 90);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.IslamonaSpaOfficer = true;
			CloseQuestHeader("Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		// <-- legendary edition
	}
}
