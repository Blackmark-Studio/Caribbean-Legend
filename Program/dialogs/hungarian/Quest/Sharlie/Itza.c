// диалоги Уракана, Канека и прочих индейцев ица
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Szükséged van valamire?";
			link.l1 = "Nem, semmit.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// ица-горожане
		case "itza_ctz":
			dialog.text = LinkRandPhrase("Egy másik sápadt arc... A nagy pap örömmel faragja ki a szívedet...","Sápadt arc tudja, hogyan jön Tayasalba, de senki sem hagyja el a várost!","Meglepôdtem, sápadtarcú: még mindig nem mentél el a szellemek földjére... Sétálj, amíg tudsz, hamarosan meglátod az ôseidet.");
			link.l1 = LinkRandPhrase("Nocsak, nocsak. Majd meglátjuk...","Ne próbálj megijeszteni, vörösbôrû harcos. Láttam már ennél rosszabbat is.","Menj, menj. Próbáld meg megijeszteni a gyerekeket.");
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz";
		break;
		
		case "itza_ctz_1":
			dialog.text = LinkRandPhrase("Áldj meg az ellenséggel való harcra, nagy Cavil!","Nagy Cavil és a nagy Kukulcan megtisztelnek minket jelenlétükkel. Még az ôsi majáknál sem fordult elô ilyesmi!","Átadjuk Kukulcan és Cavil nagy csatájának legendáját gyermekeinknek!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz_1";
		break;
		
		// Уракан - вождь ица
		case "urakan":
			dialog.text = "Nagy harcos vagy, sápadt arcú. Véredet az istenek elé visszük. Méltósággal halsz meg.";
			link.l1 = "Nyugalom, vörös bôrû harcos. Nem fogom hagyni, hogy a kaneketek áldozatul hozzon engem Kukulkánnak, vagy bárki másnak, ami azt illeti. A harcosaid nem voltak képesek elfogni engem. Mindegyikük elesett a csatában.";
			link.l1.go = "urakan_1";
		break;
		
		case "urakan_1":
			dialog.text = "Igen, te kegyes harcos, sápadt arcú. De te nem tudsz ellenállni több száz Tayasal Itza harcosnak. De érdekes szavakat mondtál. Honnan tudsz a nagy Kanekrôl és Kukulcanról?";
			link.l1 = "Nos, hadd találjam ki... Mivel te nem Kanek vagy, a neved biztosan Urakan és Kanek pap fia vagy?";
			link.l1.go = "urakan_2";
		break;
		
		case "urakan_2":
			dialog.text = "Az ajkaid igazat beszélnek, sápadt arc. Urakan vagyok, és meglepôdtem.";
			link.l1 = "Még jobban meg fogsz lepôdni, ha ezt megnézed... Nézzétek.";
			link.l1.go = "urakan_3";
		break;
		
		case "urakan_3":
			dialog.text = "Ó, istenek! Ha a sápadt arcod maszkot visel, az azt jelenti, hogy eljött az idô... Te vagy az, akirôl Kukulcan beszélt. Megparancsolta, hogy hozzanak el hozzá, amikor megérkezel Tayasalba. Tudja, hogy jöttél.";
			link.l1 = "Kukulcan?! Itt van Tayasalban?";
			link.l1.go = "urakan_4";
		break;
		
		case "urakan_4":
			dialog.text = "Igen, fehér harcos. Quetzalcoatl eljött Tayasalba. Hamarosan elindul, hogy fényt hozzon az ôsöknek, Maya nagy városába.";
			link.l1 = "Az istenit! Szóval már itt van...(leereszkedô hang) Urakan, én mindent tudok. Tudom, hogy te vagy az, aki Ksatl Cha-t az Igazság Ôrével együtt elküldte Ksocheatem és Kukulcan maszkjának keresésére...";
			link.l1.go = "urakan_5";
		break;
		
		case "urakan_5":
			dialog.text = "";
			link.l1 = "Meglepetést látok a szemedben, de egyben kétséget is, nagy Urakan fônök. Nem vagy elégedett Kukulcannal, igazam van?";
			link.l1.go = "urakan_6";
		break;
		
		case "urakan_6":
			dialog.text = "Minden Itza harcos boldog nagy Kukulcan jöjjön, fehér harcos. Kukulcan elé kell állnod. Sok éjszakát vár rád. Ô a nagy próféta. Mindent elôre tud. Menj a Repülô Kígyóhoz, nincs más utad. Nem engedjük, hogy elhagyd Tayasalt.";
			link.l1 = "Nem értitek, hogy amint Kukulcan távozik az idô kapuján keresztül, mindannyian, és ti személyesen is megszûntök létezni? És a legjobb rész az, hogy egy másik képmásban, egy másik testben fogtok újjászületni... Talán egyszerû harcosként, vagy akár nyomorékként vagy koldusként...";
			link.l1.go = "urakan_7";
		break;
		
		case "urakan_7":
			dialog.text = "Menj, sápadt bôrû harcos. Megtalálod Kukulcant az Itza harcosok nagy templomában. Menj egyenesen a hídon, amíg meg nem látod a nagy piramist. Menj be a templom alsó ajtaján, és közelítsd meg a szentélyt.";
			link.l1 = "Jól van. Elmegyek Kukulcanhoz, mert úgy látom, hogy nem ússzuk meg ezt a találkozást. De én már figyelmeztettelek titeket.";
			link.l1.go = "urakan_8";
		break;
		
		case "urakan_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_warrior_SetStay(npchar, true);
			LAi_warrior_DialogEnable(npchar, true);
			NextDiag.CurrentNode = "urakan_9";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			AddQuestRecord("Tieyasal", "25");
			pchar.quest.Tieyasal_Templegreat.win_condition.l1 = "location";
			pchar.quest.Tieyasal_Templegreat.win_condition.l1.location = "Temple_great";
			pchar.quest.Tieyasal_Templegreat.function = "Tieyasal_InGreatTemple";
			// экспа за бой
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "urakan_9":
			dialog.text = "Menj, fehér harcos. Kukulcan vár rád.";
			link.l1 = "Én már úton vagyok...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_9";
		break;
		
		case "urakan_10":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "Valóra vált! Amikor látom, hogyan harcolsz Kukulcan ellen, tudom, hogy te vagy maga Cavil. Azért jöttél Tayasalba, hogy megmentsd az Itza népet a haláltól apád és Kukulcan miatt. Apám, a nagy Kanek pap, az Itza népet a rég halott maja ôsök dicsôségére kárhoztatta.\nAz Urakan hadvezér vagyok, aki sok éven át védte az Itza népet. Egyetlen sápadt arc sem hagyta el Tayasalt élve. Én és a harcosok gondoskodunk arról, hogy az Itza népet megvédjük és életben tartsuk még sok-sok évig. Nem akarom feláldozni az egész népemet.";
			link.l1 = "Tudtam, Urakan. És megkértelek, hogy segíts nekem a hídon.";
			link.l1.go = "urakan_11";
		break;
		
		case "urakan_11":
			dialog.text = "Semmi sem rejtôzhet el a nagy Cavil szeme elôl. Bocsáss meg Urakan-nak, hogy nem érti, ki vagy te valójában.";
			link.l1 = "Ne aggódj emiatt, fônök. Legyôztem Kukulcan halandó megtestesülését, de egy másik fontos feladat is elôttünk áll - bezárni a múlt kapuit. Ezt a természetellenes lyukat az idôben meg kell szüntetni. Segítesz nekem?";
			link.l1.go = "urakan_12";
		break;
		
		case "urakan_12":
			dialog.text = "Miben tud Urakan segíteni neked, ó, Cavil?";
			link.l1 = "Elküldted Ksatl Cha-t az Igazság Ôrével, hogy keresse meg Ksocheatem-et és Kukulcan maszkját. Tehát tudod, hogy az idô kapuit be lehet vele zárni. Apád mesélt neked errôl?";
			link.l1.go = "urakan_13";
		break;
		
		case "urakan_13":
			dialog.text = "Apám nem beszélt. A Tudás és Bölcsesség templomában tanulmányozom az írásokat. De az Urakan nem sokat tud róla. Talán Cavil meg tudja érteni?";
			link.l1 = "Mit tudtál meg pontosan?";
			link.l1.go = "urakan_14";
		break;
		
		case "urakan_14":
			dialog.text = "Kívülrôl tanulom. Írás hirdeti: 'Amikor a nap felkel az esôvel szemben, és a tûz közöttük háromszögben, üsd Tohil lábát a lábára, és égesd el Kukulcan maszkját az idô oltárán. És zárjátok le Itzamna kapuit az idô kapuját a napok végéig.'";
			link.l1 = "Micsoda?";
			link.l1.go = "urakan_15";
		break;
		
		case "urakan_15":
			dialog.text = "Igen.";
			link.l1 = "Jézusom... Mutasd meg a kapukat.";
			link.l1.go = "urakan_16";
		break;
		
		case "urakan_16":
			dialog.text = "Ôk található templom Kukulcan. De az ajtó zárva van. Csak apám tudja bezárni és kinyitni. Amikor kinyitja a Kukulcan templom ajtaját, azt mondja: 'Nap jön és megy, víz esik és alábbhagy, tûz gyullad és elhalványul, háború és béke váltakozik, de csak a mennyország marad örökké. Az idô fölött csak a mennyország van.'";
			link.l1 = "Érdekes... Emlékezzünk erre, és lássuk, mit tehetünk...";
			link.l1.go = "urakan_17";
		break;
		
		case "urakan_17":
			dialog.text = "Én itt maradok, lent, az idô alterének közelében. Taysal minden piramisát és épületét belülrôl látom. Találd meg a kulcsokat. Itt maradok.";
			link.l1 = "Ha bármi fontos kérdésem van, mindenképpen hozzád fordulok.";
			link.l1.go = "urakan_18";
		break;
		
		case "urakan_18":
			DialogExit();
			NextDiag.CurrentNode = "urakan_adv";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1 = "location";
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1.location = "Tenochtitlan";
			pchar.quest.Tieyasal_UrakanTemple.function = "Tieyasal_UrakanInTemple";
			AddQuestRecord("Tieyasal", "26");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "quest", "urakan", "", -1);
			// экспа за бой
			AddComplexSelfExpToScill(1000, 1000, 1000, 1000);
			AddCharacterExpToSkill(pchar, "Leadership", 3000);
			AddCharacterExpToSkill(pchar, "Fortune", 1500);
		break;
		
		case "urakan_adv":
			dialog.text = "Urakan tud-e segíteni a nagy Cavilnak tanáccsal vagy cselekedettel?";
			if (Tieyasal_CheckTablets() && !CheckAttribute(npchar, "quest.tablets"))
			{
				link.l1 = "Nézd meg ezt a táblát, amit találtam. A helybôl ítélve, ahol találtam, valami köze lehetett az apádhoz, és nyilvánvalóan nem egy szokványos tárgy...";
				link.l1.go = "tablets";
			}
			if (CheckAttribute(npchar, "quest.treasureentrance"))
			{
				link.l1 = "Találtam egy másik bejáratot a Nagy Templom tetején, de az le van zárva. Hogyan juthatok be oda? Talán ott van, amit keresek.";
				link.l1.go = "treasure";
			}
			link.l9 = "Jelenleg semmit, Urakan. Elboldogulok egyedül...";
			link.l9.go = "exit";
			NextDiag.TempNode = "urakan_adv";
		break;
		
		case "tablets":
			dialog.text = "Istenek kôlapja. Apámnak több különbözô darabja van, és nagyon értékes számára. Az ôsi Tayasal építôi a lemezt rejtett mechanizmusok aktiválására, ajtó nyitására és zárására, sôt mágikus rituálékra is használják.\nAzok mûködnek, ha a megfelelô helyre teszik ôket - ezt csinálja az apám. De én is harcos vagyok, mint te, nem tudom, hogyan kell használni ôket. Talán Cavil tudja?";
			link.l1 = "Biztosan a végére járunk a dolognak...";
			link.l1.go = "exit";
			npchar.quest.tablets = "true";
			NextDiag.TempNode = "urakan_adv";
			AddQuestRecord("Tieyasal", "31");
		break;
		
		case "treasure":
			dialog.text = "Ez a Tayasal kincseinek ajtaja. Az itzai indiánok gazdagsága. Az ajtót belülrôl csak apám nyitja és zárja. Senki sem mer belépni a kincsekbe nélküle. Még én sem.";
			link.l1 = "Hogyan nyitotta ki apád a bejáratot?";
			link.l1.go = "treasure_1";
		break;
		
		case "treasure_1":
			dialog.text = "Apám azt mondja: 'Minden gazdagságnak két oldala van. Csak az léphet be Tayasal kincseibe, aki ismeri ezt a két oldalt.' Mit jelent ez - nem tudom. Talán Cavil találgat?";
			link.l1 = "Ezt is ki fogjuk találni...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_adv";
			DeleteAttribute(npchar, "quest.treasureentrance");
			AddQuestRecord("Tieyasal", "32");
		break;
		
		case "urakan_19":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "Tedd meg, ó, nagy Cavil! Itza népe most már biztonságban van. Én, Urakan, Kanek fia, biztosíthatlak, hogy nem hozok szégyent a becsületre, amit adtál nekem, és megvédem Tayasalt a te nevedben a becstelen sápadtarcúak bármilyen inváziójától.";
			link.l1 = "Elhiszem, fônök. Nos, most már ünnepelhetünk: véget vetettünk Kukulcan áruló terveinek. Soha többé nem lesz képes idôforradalmat materializálni.";
			link.l1.go = "urakan_20";
		break;
		
		case "urakan_20":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Dicsôség nagy Cavil! Nekem és a nemzedékemnek nagy megtiszteltetésben részesül Tayasal két isten. Ezt a történelmet gyermekeinknek írjuk. Ôk tudnak az istenek harcáról Tayasalban! Dicsôség Cavil! Dicsôség!";
			link.l1 = "Innom kell valamit...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_Win_IndianBead");
		break;
		
		// Канек - жрец ица
		case "kanek":
			dialog.text = "Sápadt arccal állsz a Szárnyas Kígyó elôtt. A hatalmas Kukulcan szelleme emberi testben. Szerencsés vagy, hogy a testvére lehetsz a megtestesült apja révén, ahogy én is szerencsés vagyok, hogy az anyja apja lehetek, az asszonyé, aki életet adott neki. Ez nagy megtiszteltetés. Talán ezért lettél erôs harcos és ezért vagy még életben.\nDe az idôd lejár, sápadtarcú. Új idôt fogunk kezdeni, a nagy Maya idejét. Megalapozzuk a saját hatalmunkat, és soha nem engedjük, hogy a sápadt arcok eljöjjenek a világunkba. Hamarosan. Én, Kanek, a pap, megyek és elkezdem a szertartást!";
			link.l1 = "Csodálatos...";
			link.l1.go = "kanek_1";
		break;
		
		case "kanek_1":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kanek_2":
			dialog.text = "Urakan, hallottad, mit mondott az urunk. Adjátok meg magatokat!";
			link.l1 = "Amikor a nagyok harcolnak egymással, jobb nekünk, egyszerû halandóknak félreállni és távolról figyelni, atyám...";
			link.l1.go = "kanek_3";
		break;
		
		case "kanek_3":
			dialog.text = "Micsoda?! Térj észhez, fiam!";
			link.l1 = "Ez az ember Kukulcan testvére és nagy harcos. Magát Cavil-t látom benne megtestesülni! Rajta kívül senki más nem áll ellen az istennek úgy, mint ô. Nem könnyû az istenek párbajában, apám! És ha áldozatot hozol Kukulcan-nak, a harcosaim a vérüket adják Cavil-nek!";
			link.l1.go = "kanek_4";
		break;
		
		case "kanek_4":
			dialog.text = "Épeszû vagy, Urakan?";
			link.l1 = "Sok éven át én, név szerint Hurakan, sikeresen védtem földjeinket Cavil nevében az idegenek inváziójától. Több százan estek el az ütegeink alatt, és senki sem hagyta el Tayasalt. De soha életemben nem láttam még olyan erôs és gyors harcost, mint ez a sápadt arc. Ha ô képes legyôzni Kukulcant, akkor ô maga Cavil szellemének megtestesítôje!";
			link.l1.go = "kanek_5";
		break;
		
		case "kanek_5":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
