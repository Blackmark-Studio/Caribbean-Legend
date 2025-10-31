#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && hrand(1) == 0 && sti(Pchar.money) >= 2000) 
			{
				dialog.text = "Nézze, uram, nem akar venni egy mulatságos kis dolgot? Olcsó, csak néhány ezer pezó...";
				link.l1 = "Hmm. Valószínûleg ellopta ezt a 'apróságot', és most próbálja lerázni magáról?";
				link.l1.go = "caleuche";
				break;
			}
			// <-- калеуче
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Helló. A nevem " + GetFullName(npchar) + ". Gondolom, nem örülsz a találkozásnak, de talán legalább a nevemre emlékszel...", 
					"Üdvözlöm, " + GetAddress_Form(NPChar) +  ". A nevem " + GetFullName(npchar) + ".", 
					"A nevem " + GetFullName(npchar) + ", " + GetAddress_Form(NPChar) + ". Örülök, hogy találkoztunk.");
				link.l1 = RandPhraseSimple("Üdvözletem.", "Hello.");
				link.l1.go = "First time";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = "Hé, figyelj, szeretnél keresni pár ezer pezót ezek helyett a szánalmas alamizsnák helyett?";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "Az a medál egy cameóval... Hol találtad?";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				npchar.quest.meeting = "1";
			}			
			else
			{
				dialog.text = NPCStringReactionRepeat("Nézd, milyen mélyre zuhantam...", 
					"Alamizsnából élni nem könnyû...", 
					"Mindent megadnék, hogy kitörjek ebbôl a szegénységbôl!",
					"Már megint te?...", "block", 1, npchar, Dialog.CurrentNode);

				link.l1 = HeroStringReactionRepeat("Értem. Nos, nem nagy ügy.", 
					"Természetesen. Hát, tudod, a történelem legnagyobb embere volt a legszegényebb.",
					"Akkor el kellene kezdened valamit csinálni, nem itt ülni egész nap.", 
					"Ah-ha. Máris idegesít?", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple("Mire van szüksége?", "Mit szeretnél?");
				link.l2.go = "Whants";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					DelLandQuestMark(npchar);
					link.l2 = "Hé, figyelj, szeretnél keresni pár ezer pezót ezek helyett a szánalmas alamizsnák helyett?";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "Az a medál drágakövekkel... Hol találtad?";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				link.l3 = LinkRandPhrase("Tudsz nekem valami érdekeset mondani?", 
					"Mi újság a városban?", "Ó, szeretném hallani a legújabb pletykákat...");
				link.l3.go = "rumours_poor";
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple("Nem, miért, máris bosszús? Nem vagyok különösebben elfoglalt, mint láthatod...", 
				"Csak fáradt vagyok. Bár szegény vagyok, mégiscsak férfi vagyok.");
			link.l1 = "Heh, értem...";
			link.l1.go = "exit";
		break;
		//выходы
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//милостыня
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase("Hmm, " + GetAddress_Form(NPChar) +  ", az emberek sok csúnya dolgot mondanak rólad. De én továbbra is hiszek az emberekben - még az olyanokban is, mint te. Kérlek, adj nekem alamizsnát kenyérre és vízre, könyörülj rajtam.",
					"könyörgöm neked, " + GetAddress_Form(NPChar) + "! Kérlek, ne fordulj el egy szegény embertôl, adj alamizsnát ételre...");
				link.l1 = RandPhraseSimple("Nem adok neked semmit.", "Pénz nélkül is boldogulsz.");
				link.l1.go = "exit";
				Link.l2 = "Rendben, és mennyire van szükséged?";
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase("Tôled? Semmitôl.", "Nincs szükségem semmire, " + GetAddress_Form(NPChar) + ", köszönöm.");
				link.l1 = RandPhraseSimple("Hmm, rendben.", "Úgy tûnik, a te életed közel sem olyan rossz, haver.");
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = "Én még egy pitiáner rézsút sem utasítanék vissza, " + GetAddress_Form(NPChar) + ". Amennyit a pénztárcád és a kegyelmed adhat...";
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "A gyengék és fáradtak kigúnyolása bûn...";
				link.l1 = "Ha-ha-ha-ha! Egy pillanatig is azt hitted, hogy pénzt adok neked, te elmebeteg koldus?!";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = "Köszönjük a " + FindRussianMoneyString(iTemp) + ", " + GetAddress_Form(NPChar) + ". Most már tudok venni egy kis kenyeret abból a pénzbôl...";
				link.l1 = "Tessék, csavargó - menj, erôsítsd meg magad egy kicsit.";
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 100 && iTemp <= 500)
			{
				dialog.text = "Köszönöm, " + GetAddress_Form(NPChar) + ". Most már egy hétig tudok élni ebbôl a pénzbôl!";
				link.l1 = "Öröm volt segíteni.";
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 500 && iTemp <= 1000)
			{
				dialog.text = "Köszönöm, " + GetAddress_Form(NPChar) + ". Mindenkinek el fogom mondani a kedvességedet!";
				link.l1 = "Ez nem igazán szükséges.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", iTemp/2000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = "Köszönöm, tisztelt "+ GetSexPhrase("uram","hölgy") +" " + GetAddress_Form(NPChar) + ". Az Úr vigyázzon rátok...";
				link.l1 = "Igen, az Ô védelme biztosan nem ártana!";
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), iTemp/10000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 5000 && iTemp <= 10000)
			{
				dialog.text = "Köszönöm, "+ GetSexPhrase("nagytiszteletû úr","nagytiszteletû hölgy") +" " + GetAddress_Form(NPChar) + ". Minden jót kívánok!";
				link.l1 = "Köszönöm, haver.";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", iTemp/5000.0);
				AddCharacterExpToSkill(pchar, "Fortune", iTemp/5000.0);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
                 if (iTemp > 10000 && iTemp < 25000)
			{
				dialog.text = "Figyelj, " + GetAddress_Form(NPChar) + ", megôrültél vagy mi? Te adsz nekem " + FindRussianMoneyString(iTemp) + "! Nem fogadhatok el ilyen pénzt, biztos van valami csapda... Hagyj békén!";
				link.l1 = "Nos, ahogy akarod...";
				link.l1.go = "exit";
			}
                 if (iTemp == 25000)
			{
				dialog.text = "Huszonötezer elfogadva... Ez a pénz elég lesz Lelyának és nekem egy egész évre!";
				link.l1 = "Elôbb éljetek ebben az évben...";
				link.l1.go = "exit";
			}
			if (iTemp > 25000)
			{
				dialog.text = "Figyelj, " + GetAddress_Form(NPChar) + ", megôrültél vagy mi? Te adsz nekem " + FindRussianMoneyString(iTemp) + "! Nem fogadhatok el ilyen pénzt, biztos van valami csapda... Hagyj békén!";
				link.l1 = "Nos, ahogy akarod...";
				link.l1.go = "exit";
			}
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "Buta kérdés, senor! Persze, hogy megtenném! De... mit kell tennem? Biztosan nem fogsz nekem ennyi pénzt adni csak a gyönyörû mosolyomért.";
			link.l1 = "Természetesen nem. Hallgassa meg most. A kormányzó nevében cselekszem. Ôkegyelme azt gyanítja, hogy valaki a hajógyárban szándékosan szabotálja 'Alacantara', gályája vízre bocsátását. És a gyanúja csak erôsödik, miután nemrég elfogtak egy francia kémet...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "";
			link.l1 = "Ôkegyelme már hallotta a hajós kifogásait, de nem biztos benne, hogy igazat mondott. Ki kell derítenünk, ki szabotálja a munkát és miért. Menjetek a dokkokhoz, nézzetek körül, és kérdezzétek meg a munkásokat, hogy mi a fene 'Alacantara' még mindig nem hajózik...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "";
			link.l1 = "Senki sem fog gyanút fogni, sôt, még egy halom dohányt is kaphatsz. Ami engem illet, nekem senki sem fog mondani semmit. Mindenki tudni fogja, hogy kinek dolgozom. Ha sikerül valami érdemlegeset megtudnod, háromezer pezót kapsz. Eleget ahhoz, hogy legalább egy hónapra felhagyj a 'munkáddal' .";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "Háromezer pezó? De, tisztelt Senor...";
			link.l1 = "Most alkudozik velem, vagy mi? Ó, és ha kideríti, ki áll az egész idôhúzás mögött, kap még kétezer dollárt. Megegyeztünk?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Rendben, senor. Nem lesz túl nehéz - sok régi haverom dolgozik mostanában a dokkokban. Hé, régen én is tengerész voltam. Úgy tíz évvel ezelôtt...";
			link.l1 = "Majd késôbb elmesélheti az élettörténetét. Találkozzunk a mólónál este tizenegy után. Most menj.";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			DialogExit();
			AddDialogExitQuestFunction("Trial_Poorman_DlgExit");
		break;
		
		case "trial_6":
			dialog.text = "Jó estét, senor...";
			link.l1 = "Jó estét, Senor. Megtudtál valamit?";
			link.l1.go = "trial_7";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_7":
			dialog.text = "Igen, senor, igen. Nem biztos, hogy ez mind egyezik azzal, amit mondott nekem... Elhozta a pénzt? Ötezer pezó.";
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = "Ne aggódjon. Itt a pénzed. Most köpd ki.";
				link.l1.go = "trial_8";
			}
			else
			{
				link.l1 = "Elôször az információ, aztán a pénz. Gyerünk, ne vesztegesse az idômet!";
				link.l1.go = "trial_fail";
			}
		break;
		
		case "trial_fail":
			dialog.text = "Maga megpróbál becsapni engem, senor! Ha nem akar fizetni - menjen és kérjen meg valaki mást. És eszébe se jusson a kardjáért nyúlni, mert hívom az ôrséget!";
			link.l1 = "...";
			link.l1.go = "trial_fail_1";
		break;
		
		case "trial_fail_1":
			DialogExit();
			AddDialogExitQuestFunction("Trial_FailPoormanInPort");
		break;
		
		case "trial_8":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Szóval így megy ez: 'Alcantara' már régóta hajózásra készen állt, de szándékosan nem rakodták be, méghozzá magának a kormányzónak a parancsára. Legalábbis nekem ezt mondták. És az ácsok most mindenféle különbözô kisebb munkákat végeznek, ami nem befolyásolja a hajó indulását.\nMindenki várja, hogy Cartagenából megérkezzen valami kéreg. A dolog az 'Alcantara' kapitánya szerint nem rendelkezik elegendô lôporral. Így hát a hajó itt marad, és egész napokig várakozik, amíg 'Puebla' hozza a lôport.\nDe mindenki úgy gondolja, hogy ez a sok várakozás csak idôpocsékolás, így ha 'Puebla' három napon belül nem érkezik meg, 'Alcantara' a lôpor nélkül emeli fel a horgonyt...";
			link.l1 = "Valóban így van? És ki mondta ezt neked? A neve?";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "AAlacantara- Felipe Dabinho egyik vitorlázója 'Alacantara' - Felipe Dabinho... De ez valójában egyáltalán nem titok, és Ôkegyelmessége kormányzó maga rendelte el...";
			link.l1 = "Értem. Erre számítottam. Francia kémek vannak a városban, de ezek az idióták úgy fecsegnek, mint a kereskedôlányok, hihetetlen! Bármelyik elsôs azt tudhat meg, amit csak akar Ôfelsége terveirôl. Ó, ez a Felipe Dabinho most komoly bajban van! És a hajóskapitány 'Alacantara' too! Az ô hibája, hogy a legénysége semmit sem tud a fegyelemrôl!";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "Ó... Szóval, már az elejétôl fogva tudtad? De miért... Nem az én hibám! Te mondtad, hogy ezt csináljam!";
			link.l1 = "Nem a te hibád volt, ne aggódj emiatt, senki sem fog megbüntetni. Most már tudjuk, hogy a 'Alacantara' legénysége bármilyen információt elkotyoghat az ellenségnek - még azt is, amit titokban kellene tartani. Rendben, most már elmehetsz. Köszönöm a segítségét. Menj, költsd el a pénzed.";
			link.l1.go = "trial_11";
			link.l2 = "Adios. (Öld meg)";
			link.l2.go = "trial_11a";
		break;
		
		case "trial_11a":
			DialogExit();
			AddDialogExitQuestFunction("Trial_KillPoormanInPort");
		break;
		
		case "trial_11":
			DialogExit();
			AddDialogExitQuestFunction("Trial_PeacePoormanInPort");
		break;
		
		// --> калеуче
		case "Caleuche":
			dialog.text = "Bocsásson meg, jó uram... Egy kockajátékban nyertem egy idegen ellen, azt hittem, hogy ez egy gyógyító amulett, de tévedtem... Nem gyógyít betegségeket, és a piaci kereskedôket nem érdekli. És itt vagy te - tengerész, kapitány, tanult ember. Nézd meg, és talán hasznosnak találod.\nNeked ez a pár ezer forint kis összeg, de nekem egy darab kenyér és egy korty rum egy hónapig. Nézze, uram...";
			link.l1 = "Rendben, mutassa...";
			link.l1.go = "Caleuche_1";
		break;
		
		case "Caleuche_1":
			Log_Info("Kaptál egy furcsa amulettet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Tessék...";
			link.l1 = "Szóval... Érdekes dolog, egyetértek. Biztos vagyok benne, hogy az indián településekrôl lopták. Rendben, elviszem. Itt a pénze.";
			link.l1.go = "Caleuche_2";
		break;
		
		case "Caleuche_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Köszönöm, uram! Remélem, ez a dolog szerencsét hoz! Az Úr óvjon meg téged!";
			link.l1 = "Sok szerencsét, haver. Ne költsd el az összes pénzt egyszerre a kocsmában.";
			link.l1.go = "Caleuche_3";
		break;
		
		case "Caleuche_3":
			DialogExit();
			GiveItem2Character(pchar, "kaleuche_amulet1"); 
		break;
		// <-- калеуче
		
		// --> Тайна Бетси Прайс
		case "TBP_Kulon_1":
			dialog.text = "Eh, "+GetAddress_Form(NPChar)+", mit érdekel téged egy régi csecsebecse?";
			link.l1 = "Amikor a csizmámmal belerúgok a hülye fejedbe, azonnal meg fogod érteni, miért érdekel.";
			link.l1.go = "TBP_Kulon_TO";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon2"))
			{
				link.l2 = "Ez a medál Betsy Price-é volt. Szóval, hol találtad?";
				link.l2.go = "TBP_Kulon_leadership";
			}
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon3");
		break;

		case "TBP_Kulon_TO":
			dialog.text = "A ház mellett feküdt a lámpással, "+GetAddress_Form(NPChar)+". Egy durva férfi csizmája taposta a sárba. De abban a házban már régóta nem lakott senki, így úgy döntöttem, hogy gazdátlan...";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "FencingH", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;

		case "TBP_Kulon_leadership":
			dialog.text = "A ház mellett feküdt a lámpással, "+GetAddress_Form(NPChar)+". Egy durva férfi csizmája taposta a sárba. De abban a házban már régóta nem lakott senki, így úgy döntöttem, hogy gazdátlan...";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;
		// <-- Тайна Бетси Прайс
	}
}
