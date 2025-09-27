void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "Mit szeretne?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;
		
		// Диалог с Алонсо после успешного абордажа
		case "Memento_MortimerGrimDead_Alonso_1":
			dialog.text = "Kapitány, a nap a miénk. Az elôôrs befejezi az alsó fedélzet átfésülését. Nincsenek foglyok... Ha! Látom, te sem fogtad vissza magad.";
			link.l1 = "Valamiért azt hittem, hogy valami nagy beszédet fogsz mondani. De csak úgy berontott.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_2";
			Achievment_Set("ach_CL_154");
			if (sti(pchar.rank) <= 13) Achievment_Set("ach_CL_156");
		break;

		case "Memento_MortimerGrimDead_Alonso_2":
			dialog.text = "Engedélyt kaptam, hogy szabadon beszéljek?";
			link.l1 = "Megadva.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_3";
			link.l2 = "Nem, itt végeztünk.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_end";
		break;

		case "Memento_MortimerGrimDead_Alonso_3":
			dialog.text = "Miért támadtuk meg ôket? Az a brigg nem jelentett veszélyt, nem szállított rakományt. Persze, mindenféle pletykák keringtek Grimrôl, de csak a rabszolgatartók féltek tôle. Sok ember halt meg ma - és miért?";
			if (sti(pchar.questTemp.ISawDiegoDeLanda) >= 2)
			{
				link.l1 = "...";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_4";
			}
			else
			{
				link.l1 = "Most a legénység nevében beszélsz?";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
			}
		break;

		case "Memento_MortimerGrimDead_Alonso_4":
			dialog.text = "És nem ez az elsô alkalom...";
			link.l1 = "Most a legénység nevében beszélsz?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_5":
			dialog.text = "Nem. Hidd el, ha a legénységnek ilyen kérdései lennének, az azt jelentené, hogy rosszul végzem a munkámat, és te máris halott ember vagy\n"+
			"Szerencsédre a srácok szép hasznot húztak ebbôl az átkozott vállalkozásból. Ezen a hajón minden matróznak tele volt a zsebe dublonnal!\n"+
			"Bár értékes rakomány nem volt - csak bennszülött csecsebecsék és hátborzongató talizmánok. A legénység mégis úgy járt, mint a rablók. Úgy tûnik, Grim jól megfizette ôket\n"+
			"Remélem, nem tervezi, hogy részesedést követel abból az aranyból, kapitány?";
			link.l1 = "Nem, Alonso. Köszönöm, hogy tájékoztattál.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_6";
			link.l2 = "Én igen. Gondoskodj róla, hogy a részemet a kabinomba szállítsák.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_7";
		break;

		case "Memento_MortimerGrimDead_Alonso_6":
			dialog.text = "Mindig a maga oldalán állok, kapitány. Egyébként, mit tervez a Mementóval?";
			link.l1 = "Elvinni nyereményként - mi mást?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Még nem döntöttem"+GetSexPhrase(""," még")+" .";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
		break;

		case "Memento_MortimerGrimDead_Alonso_7":
			dialog.text = "Mindig a maga oldalán állok, kapitány. Egyébként, mit tervez a Mementóval?";
			link.l1 = "Elvinni nyereményként - mi mást?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Még nem döntöttem"+GetSexPhrase(""," még")+" .";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
			AddCrewMorale(Pchar, -10);
			AddItems(Pchar, "gold_dublon", 500);
		break;

		case "Memento_MortimerGrimDead_Alonso_8":
			dialog.text = "Jobb, ha nem. Valamiféle bennszülött szimbólumok borítják. És rossz pletykák keringenek róla - azt mondják, egyszer túlélt egy szörnyû pestist, és a fedélzeten szinte táncoltak a hullák\n"+
			"Ami a hajó tatján lévô csontvázat illeti, oda nem is megyek: amíg valami idióta nem meri szórakozásból elkapni a koponyát, addig rajtam kívül senki sem mer ott ôrködni.";
			link.l1 = "Értettem, Alonso. Vissza a munkához.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_9";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_9":
			dialog.text = "Igenis, kapitány.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_end";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_end":
			DialogExit();
			AddDialogExitQuestFunction("Memento_MortimerGrimDead_Alonso_2");
		break;
		
		// Диалог с Алонсо в первую ночь
		case "Memento_Dich_EtapOne_Alonso_1":
			dialog.text = "Kapitány, elnézést, hogy ilyenkor zavarom.";
			link.l1 = "Jelentést, Alonso.";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_2";
			if (CheckAttribute(pchar, "questTemp.Memento_Dich_EtapTwo"))
			{
				dialog.text = "Kapitány? Mit keres itt? Itt aludtál?";
				link.l1 = "Nem számít.";
				link.l1.go = "Memento_Dich_EtapTwo_Alonso_2";
				link.l2 = "A kabinom... nyugtalanító érzés.";
				link.l2.go = "Memento_Dich_EtapTwo_Alonso_2";
			}
		break;

		case "Memento_Dich_EtapOne_Alonso_2":
			dialog.text = "A dolgok rosszul állnak. A legénység morálja a padlón van! Az emberek nyíltan azt mondják, hogy a hajó el van átkozva. Panaszkodnak, hogy éjszaka dolgokat látnak.";
			link.l1 = "Pontosan mit látnak?";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_3";
		break;

		case "Memento_Dich_EtapOne_Alonso_3":
			dialog.text = "Rémálmokat, leginkább. De a legrosszabb, hogy az egyik emberünk lázban meghalt. Egy fiatal fiú, erôs volt, mint egy ökör, és néhány óra alatt elégett.";
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				link.l1 = "Ezt az orvosnak kell eldöntenie. "+sld.name+" ismeri a szakmáját.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
			else
			{
				link.l1 = "Ez nem normális. Tartsd a legénységet kordában, Alonso. Ez a te dolgod.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
		break;
		
		case "Memento_Dich_EtapOne_Alonso_4":
			dialog.text = "Igenis!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapOne_End");
		break;
		
		// Диалог с Алонсо во вторую ночь
		case "Memento_Dich_EtapTwo_Alonso_2":
			dialog.text = "Ez a te dolgod, Alonso. Sokan a legénységbôl most csoportosan alszanak - félnek egyedül lenni. Mintha egyáltalán lehetséges lenne egyedül lenni ezen a hajón...";
			link.l1 = "Nem úgy tûnik, mintha sikerült volna. Mi történt?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_3";
		break;

		case "Memento_Dich_EtapTwo_Alonso_3":
			dialog.text = "Verekedés - José leszúrta Marcelt. Azt kiabálta, hogy 'hordozza a pestist.'";
			link.l1 = "Rosszabbodik a helyzet?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_4";
		break;

		case "Memento_Dich_EtapTwo_Alonso_4":
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				dialog.text = sld.name+" Ma reggel már jelentették. Tizenegy lelket vesztettünk. Mit tegyünk?";
			}
			else
			{
				dialog.text = "Újabb tizenegy lélek veszett oda. Mit tegyünk?";
			}
			link.l1 = "Majd én telefonálok.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_5";
		break;

		case "Memento_Dich_EtapTwo_Alonso_5":
			dialog.text = "Remélem, kapitány. Mi lesz Joséval? A gyilkosság nem vicc.";
			link.l1 = "A harangszó után felakasztjuk. Mutassuk meg, hogy mi irányítunk.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_6";
			link.l2 = "Harminc korbácsütés. Ha túléli - akkor ez Isten akarata.";
			link.l2.go = "Memento_Dich_EtapTwo_Alonso_7";
		break;

		case "Memento_Dich_EtapTwo_Alonso_6":
			dialog.text = "Igenis!";
			link.l1 = "...";
			link.l1.go = "exit";
			SetCrewQuantity(pchar, GetCrewQuantity(pchar) - 1);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;

		case "Memento_Dich_EtapTwo_Alonso_7":
			dialog.text = "Igenis!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddCrewMorale(Pchar, -10);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;
		
		// Диалог с Алонсо в третью ночь
		case "Memento_Dich_EtapThree_AlonsoPrizrak_1":
			dialog.text = "Kapitány! Riadó! Azonnal a fedélzetre kell mennie!";
			link.l1 = "Mi folyik itt?";
			link.l1.go = "Memento_Dich_EtapThree_AlonsoPrizrak_2";
		break;

		case "Memento_Dich_EtapThree_AlonsoPrizrak_2":
			dialog.text = "Jobb, ha a saját szemével látja. Gyerünk, gyorsan!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_4_1");
		break;
		
		// Уже утром
		case "Memento_Dich_EtapThree_Alonso_1":
			dialog.text = "Jó reggelt, kapitány!";
			link.l1 = "Hm?!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_2";
		break;

		case "Memento_Dich_EtapThree_Alonso_2":
			dialog.text = "Uh, szörnyen nézel ki. Kemény éjszaka? Nos, jó híreim vannak. A járványnak vége. Kiderült, hogy nem is volt.";
			link.l1 = "Hogy érti ezt?";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_3";
		break;

		case "Memento_Dich_EtapThree_Alonso_3":
			dialog.text = "A legénység megijedt, és elkezdett hinni ezekben a hülye szellemhajós történetekben. A szuggesztió ereje... ijesztô dolog, én mondom neked. Több hajót is elsüllyesztett már.";
			link.l1 = "De emberek haltak meg!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_4";
		break;

		case "Memento_Dich_EtapThree_Alonso_4":
			dialog.text = "Verekedés, piszkos sebek, romlott sós hús - csak a szokásos matrózmatek. Ha nem korbácsoltuk volna fel magunkat az elátkozott hajókról szóló mesékkel, talán kevesebbet veszítettünk volna\n"+
			"Az a csontváz a tatnál nem segített. Még jó, hogy valami... csínytevô ellopta a kalapját az éjszaka\n"+
			"Mivel ilyen káromkodásért nem csapott belénk a villám, a legénység felélénkült, és matrózok eszükkel szorgalmasan fôzték a huncutságokat. Mint például...";
			link.l1 = "Ne nyúljatok a csontvázhoz!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_5";
		break;

		case "Memento_Dich_EtapThree_Alonso_5":
			dialog.text = "Ööö... nos, ha megkedvelted, akkor természetesen nem fogjuk. Szép napot, kapitány\n"+
			"Egyébként szép sapka! Jól áll neked. Nyilván nem illett az elôzô tulajdonosra.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_End");
		break;
		
		// Диалоги с командой Мементо
		case "Memento_Sailor_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Üdvözlöm, kapitány. Beszélnie kellene Grim kapitánnyal.";
				link.l1 = "Sajnálom, matróz, de te itt kilógsz a sorból.";
				link.l1.go = "Memento_Sailor_1_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Még valami, kapitány?";
				link.l1 = "Semmi.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_1_1":
			dialog.text = "Tudom, mire gondol, kapitány. Én egy szabad kapitány alatt szolgáltam - akárcsak maga. Kincsekre vadászott, kereskedett, rakományt szállított. Aztán úgy döntött, hogy kirabol néhány kereskedôt - nem jött össze. A túlélôket kalózkodásért akasztásra ítélték.";
			link.l1 = "És Grim kapitány megvette magát?";
			link.l1.go = "Memento_Sailor_1_2";
		break;

		case "Memento_Sailor_1_2":
			dialog.text = "Mindannyiunkat megvett, mint egy rakományt. Minden hajónak szüksége van tapasztalt matrózokra, és Grim nem a kocsmákban toboroz... De etet minket és jól fizet. És mi szolgálunk - és sorsolunk.";
			link.l1 = "A sorsolás?";
			link.l1.go = "Memento_Sailor_1_3";
		break;

		case "Memento_Sailor_1_3":
			dialog.text = "Sajnálom, errôl nem szabad beszélnünk.";
			link.l1 = "Miért nem megyünk el?";
			link.l1.go = "Memento_Sailor_1_4";
		break;

		case "Memento_Sailor_1_4":
			dialog.text = "Hová? Itt legalább van esély. Talán a szerencse mosolyogni fog. Minden hajónak megvan a maga sorsolása. Grimnek is megvan az övé, neked is megvan a tiéd. Nem vagyunk emberek, csak számok a hajónaplóban.";
			link.l1 = "Az én hajómon másképp mennek a dolgok.";
			link.l1.go = "Memento_Sailor_1_5";
		break;
		
		case "Memento_Sailor_1_5":
			dialog.text = "Ahogy mondja, kapitány. Jó napot kívánok.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_2":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Régen volt már látogató ezen a szép hajón!";
				link.l1 = "Maga tengerész? Nem úgy néz ki.";
				link.l1.go = "Memento_Sailor_2_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Még valami, kapitány?";
				link.l1 = "Semmi.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_2_1":
			dialog.text = "Há! A kapitány egyenesen a cellából vett meg. Port Royalban akartak felakasztani - leszúrtam egy fickót, aki verseket szavalt. Megérdemelte a szemétláda.";
			link.l1 = "Szóval szerencséd volt?";
			link.l1.go = "Memento_Sailor_2_2";
		break;

		case "Memento_Sailor_2_2":
			dialog.text = "Hát persze! A kapitány nem fukar, bár néha ki kell játszani a... játékát.";
			link.l1 = "Miféle játékokat?";
			link.l1.go = "Memento_Sailor_2_3";
		break;
		
		case "Memento_Sailor_2_3":
			dialog.text = "Minden héten pálcát húzunk: a rövid pálca veszélyes munkát jelent, vagy néha át kell ugrani a fedélzetre. Ez tényleg jó móka. Nem mindenkinek való, de a kapitány azt mondja, hogy így választja ki az érdemteleneket.";
			link.l1 = "Mire érdemteleneket?";
			link.l1.go = "Memento_Sailor_2_4";
		break;

		case "Memento_Sailor_2_4":
			dialog.text = "Honnan tudhatom? A kapitány szeret beszélni, úgy prédikál, mint egy pap: Csak akkor élhetsz igazán, ha szembenézel a halállal!\n"+
			"(Köpi.)";
			link.l1 = "A fedélzetre köpködésért korbácsütés jár. Úgy viselkedsz, mint egy rabló, nem mint egy tengerész. Viszlát.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_3":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Üdvözletem, kapitány.";
				link.l1 = "Hogy kerültél ide?";
				link.l1.go = "Memento_Sailor_3_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Még valami, kapitány?";
				link.l1 = "Semmi.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_3";
		break;

		case "Memento_Sailor_3_1":
			dialog.text = "Grim kapitány elvitte a rabszolgahajót, amin voltam. Beteg voltam, haldokoltam a raktérben... Nem sok mindenre emlékszem. A következô dolog, amire emlékszem, hogy itt ébredtem fel, a Mementón.";
			link.l1 = "És mi történt a többi rabszolgával?";
			link.l1.go = "Memento_Sailor_3_2";
		break;
		
		case "Memento_Sailor_3_2":
			dialog.text = "Nem tudom. A kapitány azt mondta, hogy mindenkit kiszabadított, de csak engem hoztak fel a fedélzetre. A többiek szétszóródtak a szigeteken, vagy belehaltak a sebeikbe. Az a nap számomra homályos.";
			link.l1 = "Legalább most már szabad vagy.";
			link.l1.go = "Memento_Sailor_3_3";
		break;

		case "Memento_Sailor_3_3":
			dialog.text = "Szabad? Itt senki sem szabad. A kapitány ad aranyat, élelmet, ruhát, de cserébe teljes hûséget követel - és sorsot húzattat velünk.";
			link.l1 = "A sorsolás?";
			link.l1.go = "Memento_Sailor_3_4";
		break;

		case "Memento_Sailor_3_4":
			dialog.text = "Minden héten valaki húzza a rövidebbet, és kap egy veszélyes munkát - nem mindenki jön vissza. A kapitány szerint így választják el az élôket a holtaktól.";
			link.l1 = "És te ezt elviseled?";
			link.l1.go = "Memento_Sailor_3_5";
		break;

		case "Memento_Sailor_3_5":
			dialog.text = "Mindenki reméli, hogy a szerencse melléjük áll. A kapitány tudja, mi hajtja az egyes embereket: a huroktól való félelem, az arany utáni mohóság, a késztetés, hogy törlesszenek egy megmentett életért. Nekem mindez nem számít. Nincs szükségem pénzre, és milyen adóssággal tartozhatsz olyasmiért, amire nem emlékszel?";
			link.l1 = "Nem félsz ilyen nyíltan beszélni?";
			link.l1.go = "Memento_Sailor_3_6";
		break;

		case "Memento_Sailor_3_6":
			dialog.text = "Mit tehetnek velem? Ez a halottak hajója, kapitány, és én ide tartozom. De te - te nem.";
			link.l1 = "Ha maga mondja. Viszontlátásra.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_3";
		break;
		
		case "Memento_Sailor_4":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Üdvözlöm a Memento fedélzetén, kapitány.";
				link.l1 = "Egy spanyol katona egy kalózhajón? Ilyet nem mindennap lát az ember.";
				link.l1.go = "Memento_Sailor_4_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Még valami, kapitány?";
				link.l1 = "Semmi.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_4";
		break;

		case "Memento_Sailor_4_1":
			dialog.text = "Dezertôr vagyok. Grim kapitány megvett a San Jose téri akasztófáról. Nagy árat fizetett - egy egész zsák dublont a szánalmas bôrömért.";
			link.l1 = "Miért akasztottak fel?";
			link.l1.go = "Memento_Sailor_4_2";
		break;

		case "Memento_Sailor_4_2":
			dialog.text = "Saldo tiszt elküldött minket, hogy ôrizzük a munkásokat a dzsungelben, ahol a fele egy hét alatt belehal a lázba. Úgy gondoltam, az én életem többet ér. Most azt az embert szolgálom, aki megfizetett érte.";
			link.l1 = "Nem bántad meg?";
			link.l1.go = "Memento_Sailor_4_3";
		break;

		case "Memento_Sailor_4_3":
			dialog.text = "A kötél sokáig csavarodhat... A kapitány nagylelkû azokkal, akik hûségesek hozzá. Bár néha furcsa próbatételeket állít elénk - sorshúzás. Nem mindenkinek van szerencséje.";
			link.l1 = "Sorsolás?";
			link.l1.go = "Memento_Sailor_4_4";
		break;
		
		case "Memento_Sailor_4_4":
			dialog.text = "Tudjátok. Van, akit a viharba küldenek, van, akit az élcsapatba. A kapitány azt mondja, így teszteli, hogy készen állsz-e. Hogy mire, azt nem tudom megmondani, de remélem, a szerencse az én oldalamon áll.";
			link.l1 = "Sok szerencsét... Gondolom.";
			link.l1.go = "Memento_Sailor_4_5";
		break;

		case "Memento_Sailor_4_5":
			dialog.text = "Köszönöm, kapitány. A halál elôbb-utóbb mindannyiunkat elér.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_4";
		break;
		
		/*case "Memento_Sailor_5":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "5. párbeszéd";
				link.l1 = "5. párbeszéd";
				link.l1.go = "exit";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Még valami, kapitány?";
				link.l1 = "Semmi.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_5";
		break;*/
		
		case "Memento_MortimerGrim_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Üdvözlöm a Memento fedélzetén, kolléga. A nevem Mortimer Grim.";
				link.l1 = "Kapitány "+GetFullName(pchar)+". Köszönöm, hogy itt lehetek...";
				link.l1.go = "Memento_MortimerGrim_2";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Mirôl beszélhetnénk még?";
				if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
				{
					link.l1 = "Ez egy figyelemre méltó penge, kapitány.";
					link.l1.go = "Memento_MortimerGrim_question_1_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
				{
					link.l2 = "A távcsöve remekül mutat a csontváz mellett.";
					link.l2.go = "Memento_MortimerGrim_question_2_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
				{
					link.l3 = "Azt kell mondjam, a legénységed eléggé vegyes.";
					link.l3.go = "Memento_MortimerGrim_question_3_1";
				}
				link.l4 = "Semmi... kolléga. Szép szeleket kívánok.";
				link.l4.go = "exit";
				NextDiag.TempNode = "Memento_MortimerGrim_1";
			}
		break;

		case "Memento_MortimerGrim_2":
			dialog.text = "A Karib-tenger nagylelkû azokkal, akik az akasztófára rohannak, ennyit tudok.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_3";
		break;
		
		case "Memento_MortimerGrim_3":
			dialog.text = "Igen, uram? Szeretne kérdezni valamit?";
			link.l1 = "Egy csontváz lóg a hátad mögött.";
			link.l1.go = "Memento_MortimerGrim_4";
			link.l2 = "Szép szél van ma, nem igaz? És az idôjárás is remek.";
			link.l2.go = "Memento_MortimerGrim_5";
		break;

		case "Memento_MortimerGrim_4":
			dialog.text = "Milyen csontváz? Mögöttem csak a kék Karib-tenger van.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_5":
			dialog.text = "Egyetértek, kolléga. Nem bánnám, ha minden nap ilyen lenne!";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_6":
			dialog.text = "Ha-ha-ha-ha! Ez a vicc sosem öregszik! Ne ijedjen meg: az öreg Yorick, akárcsak ez a hajó, egy emlék az elôzô életembôl. Szó szerint, biztosíthatom.";
			link.l1 = "'Szó szerint?'";
			link.l1.go = "Memento_MortimerGrim_7";
		break;

		case "Memento_MortimerGrim_7":
			dialog.text = "Kolléga, félsz a haláltól? Nem fenyegetés, ôszintén kíváncsi vagyok.";
			link.l1 = "Hát persze. Aki mást állít, az hazudik.";
			link.l1.go = "Memento_MortimerGrim_8_leadership";
			link.l2 = "Nem. Mindannyian ott fogjuk végezni.";
			link.l2.go = "Memento_MortimerGrim_8_weapon";
			link.l3 = "És maga?";
			link.l3.go = "Memento_MortimerGrim_8_sneak";
		break;
		
		case "Memento_MortimerGrim_8_leadership":
			dialog.text = "Ó! A halál minden félelem anyja. A magány, a sötétség, a büntetés - ezek mind csak az ô álarcai.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Memento_MortimerGrim_8_weapon":
			dialog.text = "Ó! A halál minden félelem anyja. A magány, a sötétség, a büntetés - ezek mind csak az ô álarcai.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "Memento_MortimerGrim_8_sneak":
			dialog.text = "Ó! A halál minden félelem anyja. A magány, a sötétség, a büntetés - ezek mind csak az ô álarcai.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Memento_MortimerGrim_9":
			dialog.text = "Nem kell messzire nézni. Vegyük az öreg Yorickot: egy halom csont, lámpással a bordáiban - mégis, még egy ilyen félelmetes kapitányt is megrázott, mint te!";
			if (startHeroType == 4)
			{
				dialog.text = "Nem kell messzire nézni. Vegyük az öreg Yorickot: egy halom csont, lámpással a bordáiban - még a rettenthetetlen Ellen, a nagy Sean MacArthur lánya is megijedt!";
			}
			link.l1 = "Jól beszélsz, de nem mondtad, hogy mit kezdjünk mindezzel.";
			link.l1.go = "Memento_MortimerGrim_10";
		break;

		case "Memento_MortimerGrim_10":
			dialog.text = "Tudom, mit kell tenni, de az én gyógymódom nem mindenkinek felel meg. Bármikor kipróbálhatod, de elôbb mondd el a véleményed.";
			link.l1 = "A Biblia szerint nincs halál.";
			link.l1.go = "Memento_MortimerGrim_11_1";
			link.l2 = "Ha elkezdek félni, akkor a hajónak vége.";
			link.l2.go = "Memento_MortimerGrim_11_2";
			link.l3 = "A válasz egy üveg rum aljára fulladt.";
			link.l3.go = "Memento_MortimerGrim_11_3";
		break;
		
		case "Memento_MortimerGrim_11_1":
			dialog.text = "Ez igaz. Az egyetlen dolog, amivel egyetértek abban a könyvben.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_2":
			dialog.text = "Csodálatra méltó. De a semmiért aggódsz: nincs halál.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_3":
			dialog.text = "Jo-ho-ho! Egy cinikus. De még rum nélkül is azt mondom: nincs halál.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_12":
			dialog.text = "Egyszerû: az igazi élet csak akkor kezdôdik, ha legyôzöd a halált. Én már jártam ott, a fátyolon túl, és hidd el, csak azután kezdtem el igazán élni.";
			link.l1 = "Jöjjön újra?";
			link.l1.go = "Memento_MortimerGrim_13";
		break;

		case "Memento_MortimerGrim_13":
			dialog.text = "Ne törôdjön vele, kolléga.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
		break;

		case "Memento_MortimerGrim_question_1_1":
			dialog.text = "Örülök, hogy észrevetted, kolléga! Nem vagyok hivalkodó, de milyen kalóz lennék félelmetes bicska nélkül?";
			link.l1 = "Tényleg számít ez?";
			link.l1.go = "Memento_MortimerGrim_question_1_2";
		break;
		
		case "Memento_MortimerGrim_question_1_2":
			dialog.text = "Pontosan! Az egyetlen alkalom, amikor személyes okokból jelentôsen megkönnyítettem a hajó kincstárát, az éppen ez a penge volt. Kétezer arany dublont, kolléga! A pokolba is, ha másodszor is feltámadhatnék a sírból, csak az ára miatt térnék vissza!\n"+
			"Maga a fegyver kiváló. De valahogy... mintha valami hiányozna belôle.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "Memento_MortimerGrim_question_2_1":
			dialog.text = "Egy ajándék valakitôl. Egy zseniális beszélgetôpartnertôl, aki úgy érti a halált, mint senki más - és vad fantáziával, mint láthatod.";
			link.l1 = "Komornak tûnik.";
			link.l1.go = "Memento_MortimerGrim_question_2_2";
		break;

		case "Memento_MortimerGrim_question_2_2":
			dialog.text = "Memento mori, kolléga.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_2 = true;
		break;

		case "Memento_MortimerGrim_question_3_1":
			dialog.text = "Az én legénységemben több közös van, mint a tiédben, például... Mindegyiküket én szabadítottam ki a kötél és a láncok alól. Mindegyikük érezte a halál leheletét. Ez jobban összeköti az embereket, mint a vér vagy a zászló.";
			link.l1 = "Szóval, gondolom, nem alkalmaz embereket a kocsmákban?";
			link.l1.go = "Memento_MortimerGrim_question_3_2";
		break;

		case "Memento_MortimerGrim_question_3_2":
			dialog.text = "Meglepôdnél, milyen szívesen jelentkeznek egykori rabszolgák és elítéltek: elcserélnéd a rabszolgatartó raktárát vagy az akasztófát a Memento fedélzetére? Most 178 emberem van - és mindegyikük tartozik nekem.";
			link.l1 = "De még mindig ki kell fizetned ôket, és fenn kell tartanod a hajót. A hála önmagában nem elég.";
			link.l1.go = "Memento_MortimerGrim_question_3_3";
		break;

		case "Memento_MortimerGrim_question_3_3":
			dialog.text = "Sikeres kalóz vagyok, kolléga. Egy igazi hostis humanitatis. Az emberiség igazi ellenségei - a rabszolgatartók és a koronás fejesek - így neveznének engem. Az egyetlen különbség köztük a cím.\n"+
			"Szerencsére rengeteg aranyuk van. A rabszolgatartó ládákból származó érméket arra használom, hogy megmentsem a korona által elítélteket. A többi a legénységemhez kerül - nekem nincs szükségem semmire. Mi haszna van egy halottnak az aranyból? Hamarosan rájönnek...";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_3 = true;
		break;
		
		// Диалог с Алонсо
		case "Memento_Alonso_phantom_11":
			dialog.text = "Ilyen szar helyzetben vagyunk, kapitány.";
			link.l1 = "Mi ez az egész?!";
			link.l1.go = "Memento_Alonso_phantom_12";
		break;

		case "Memento_Alonso_phantom_12":
			dialog.text = "Te vagy az egyetlen, aki megmaradt. A betegség mindannyiunkat elkapott. Cserben hagytál minket.";
			link.l1 = "Ez nem lehet!";
			link.l1.go = "Memento_Alonso_phantom_13";
		break;

		case "Memento_Alonso_phantom_13":
			dialog.text = "Egy elátkozott hajó fedélzetére hoztál minket.";
			link.l1 = "...";
			link.l1.go = "Memento_Alonso_phantom_14";
		break;

		case "Memento_Alonso_phantom_14":
			dialog.text = "Mindannyiunkat halálra ítéltél!";
			link.l1 = "Alonso, mi bajod van?!";
			link.l1.go = "Memento_Alonso_phantom_15";
			npchar.model = "skel1";
			npchar.model.animation = "skeleton";
			npchar.sex = "skeleton";
			Characters_RefreshModel(npchar);
			SetMusic("classic_music_retribution_1");
		break;

		case "Memento_Alonso_phantom_15":
			dialog.text = "Mortui vivos docent.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_6");
		break;
		
		// Диалог с Гримом
		
		case "Memento_MortimerGrim_phantom_11":
			dialog.text = "Miért álltál meg, kolléga? Meggondoltad magad? Akkor miért támadtál egyáltalán?";
			link.l1 = "Grim? De hát halott vagy!";
			link.l1.go = "Memento_MortimerGrim_phantom_12";
		break;

		case "Memento_MortimerGrim_phantom_12":
			dialog.text = "Ha! Ami halott, az talán sosem hal meg. És különben is, elôre ugrasz: lehet, hogy megnyerted a beszállást, de hogy túl fogod-e élni... nos, derüljön ki!";
			link.l1 = "Az a harc már hetekkel ezelôtt véget ért! Meghaltál!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_11");
		break;

		case "Memento_MortimerGrim_phantom_21":
			dialog.text = "Most már vége van. Gratulálok a gyôzelmedhez.";
			link.l1 = "Komor?";
			link.l1.go = "Memento_MortimerGrim_phantom_22";
			LAi_UseAtidoteBottle(pchar);
		break;

		case "Memento_MortimerGrim_phantom_22":
			dialog.text = "Tudod, én örülök. Igazán örülök, hogy megöltél. Tényleg.";
			link.l1 = "Mirôl beszélsz?";
			link.l1.go = "Memento_MortimerGrim_phantom_23";
		break;

		case "Memento_MortimerGrim_phantom_23":
			dialog.text = "Gyáva vagyok, kolléga. Csak egy szánalmas gyáva, aki félt a haláltól - mint elôtte ezrek. Amikor a legénység meghalt a pestisben... és ez az én hibám volt, megôrültem a félelemtôl. Egy hónapig sodródtam egyedül a halottak hajóján.";
			link.l1 = "Mi történt valójában?";
			link.l1.go = "Memento_MortimerGrim_phantom_24";
		break;

		case "Memento_MortimerGrim_phantom_24":
			dialog.text = "Megbuktam a halál próbáján. Ahelyett, hogy elfogadtam volna, túléltem volna, és tanultam volna valamit, még jobban féltem. És hogy elnyomjam ezt a félelmet... elkezdtem másokat is arra kényszeríteni, hogy átéljék azt, amit én.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_25";
		break;
		
		case "Memento_MortimerGrim_phantom_25":
			dialog.text = "Köszönöm, kolléga. Hogy megszabadítottál ettôl a... létezéstôl. Most már tényleg tudom, hogy nincs halál. És nem félek többé. Nem maradt senki, akit hibáztathatnék vagy rabszolgává tehetnék.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_26";
		break;

		case "Memento_MortimerGrim_phantom_26":
			dialog.text = "Ne válassza el a Mementót a kapitányától. Mortimer... Mortimer kapitány jó ember volt. Keresse meg ôt Dominicán. És a hajó... a hajó el fog fogadni téged.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_27";
		break;

		case "Memento_MortimerGrim_phantom_27":
			dialog.text = "Mortui vivos docent, kolléga. A holtak tanítják az élôket. Viszontlátásra.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_13");
		break;
		
	}
} 