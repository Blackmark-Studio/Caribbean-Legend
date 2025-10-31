// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Beszélj, hallgatlak.";
			link.l1 = "Tévedtem. Viszontlátásra.";
			link.l1.go = "Exit";
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "start")
			{
				link.l1 = "Hallottam egy tolvaj- és rablóbandáról, amely Belize környékén és magában a városban tevékenykedik.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
				DelLandQuestMarkToPhantom();
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "know" && CheckAttribute(pchar, "questTemp.Caleuche.belizbandos") && GetQuestPastDayParam("questTemp.Caleuche.belizbandos") < 3)
			{
				link.l1 = "Információkat tudok adni a bandáról.";
				link.l1.go = "caleuche_3";
				DelLandQuestMark(npchar);
				DelLandQuestMarkToPhantom();
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.BelizRegard"))
			{
				link.l1 = "Milyen híreket a bandáról? Elfogták ôket a barlangnál?";
				link.l1.go = "caleuche_7";
				DelLandQuestMark(npchar);
				DelLandQuestMarkToPhantom();
			}
			// Путеводная звезда ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz_Komendant"))
			{
				link.l1 = "Úgy tûnik, az egész város a kalóz elfogását ünnepli. Tudna errôl többet mondani?";
				link.l1.go = "PZ_Beliz_Komendant_1";
				DeleteAttribute(pchar, "questTemp.PZ_Beliz_Komendant");
			}
			// <== Путеводная звезда
		break;
		
		// Путеводная звезда ==>
		case "PZ_Beliz_Komendant_1":
			dialog.text = "Örömmel! Ez nem akármilyen kalóz - ez az a gazember, Matthew Lutter.";
			link.l1 = "Mindenkinek eljön a szerencséje.";
			link.l1.go = "PZ_Beliz_Komendant_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Beliz_Komendant_2":
			dialog.text = "Ön nem angol, és nem úgy néz ki, mint egy kereskedô, így értem, miért nem olyan izgatott. Lutter évek óta terrorizálja ezeket a vizeket, megtámadva minket és a Donokat is, de gyakrabban minket. Mindig sikerült elkerülnie a parti ôrjáratainkat, a Sirály nevû korvettjével, amely egykor a leggyorsabb hajó volt a szigetvilágban. Hogy hogyan került egy ilyen hadihajó parancsnoki székébe, azt csak Isten tudja.";
			link.l1 = "Szóval igaz, hogy vesztett egy kereskedôvel szemben? Egy korvettel? Hihetetlennek hangzik.";
			link.l1.go = "PZ_Beliz_Komendant_3";
		break;
		
		case "PZ_Beliz_Komendant_3":
			dialog.text = "Bármilyen furcsán is hangzik, de igaz. Egy kereskedô, ráadásul spanyol! A mi flottánk tanulhatna tôle egy-két dolgot. Sotta kapitány, felismerve, hogy nincs menekvés, felkészült a csatára...";
			link.l1 = "Elég szokatlan személyiség ez a Sotta.";
			link.l1.go = "PZ_Beliz_Komendant_4";
		break;
		
		case "PZ_Beliz_Komendant_4":
			dialog.text = "Talán. Átépíttette a hajóját, hogy minél több rakományt tudjon szállítani, ami lehetetlenné tette a menekülést. Mivel tudta, hogy a kalózok a rakományát akarják, úgy tett, mintha sodródna. És aztán...";
			link.l1 = "...a megfelelô pillanatban felhúzta a vitorlákat?";
			link.l1.go = "PZ_Beliz_Komendant_5";
			if (!CharacterIsHere("Longway"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
		break;
		
		case "PZ_Beliz_Komendant_5":
			dialog.text = "Ha! Nem, közvetlen közelrôl lôtt ki egy széles sortüzet, amikor Lutter közeledett, aztán maga szállt a kalóz fedélzetére! Amikor megtudta, hogy ki az a Lutter, átadta nekünk. Egy igazi hôs, egy becsületes ember!";
			link.l1 = "Nem csak a becsület vezérelte - bizonyára jutalmat kapott a Szélzsák elfogásáért.";
			link.l1.go = "PZ_Beliz_Komendant_6";
		break;
		
		case "PZ_Beliz_Komendant_6":
			dialog.text = "Néha a haszon és a jó szándék összeér. De igen, bôséges jutalmat kapott. Ôkegyelme drága árucikkekkel pakolta fel városunk hálája jeléül, mielôtt elhajózott.";
			link.l1 = "Bárcsak találkoztam volna vele - szívesen kezet ráznék vele. Mondd csak...";
			link.l1.go = "PZ_Beliz_Komendant_7";
		break;
		
		case "PZ_Beliz_Komendant_7":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_8", "Quest\CompanionQuests\Longway.c");
		break;
		// <== Путеводная звезда
		
		// Калеуче
		case "caleuche":
			dialog.text = "A forrásod igazat mondott. Ezek a banditák igazi púp a hátunkon. Akarsz mondani valamit róluk?";
			link.l1 = "Azon kívül, hogy elloptak tôlem egy fontos dolgot - igazából semmit. Reméltem, hogy tudtok majd mondani valamit róluk. Talán az egyiküket elkapták, és most készen áll tanúskodni...";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Sajnálom, hogy csalódást kell okoznom, kapitány, de nincs információm róluk. Csak azt tudom, hogy valahol a dzsungelben bujkálnak, és vannak bûntársaik a városban, ennyi. Ha bármi újat megtud róluk, kérem, azonnal szóljon.";
			link.l1 = "Rendben, biztos úr. Úgy lesz.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddQuestRecord("Caleuche", "10");
			pchar.questTemp.Caleuche.Bandos = "seek";
		break;
		
		case "caleuche_3":
			string sTime;
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 0) sTime = "három nap alatt";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 1) sTime = "holnapután.";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 2) sTime = "holnap";
			dialog.text = "Komolyan mondja, kapitány? Beszéljen, csupa fül vagyok.";
			link.l1 = "Megtaláltam az egyik besúgójukat a városban. Elmondta, hogy bandájuk egy hajó megtámadására készül, amely állítólag Chetumal öblébe érkezik. A gazemberek "+sTime+" éjszaka gyülekeznek egy barlang közelében, nem messze Belize-tôl. Ahhoz, hogy odaérjünk, csak a dzsungelben lévô elágazásnál balra kell menni az ösvényen.";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "A barlangnál? Kitûnô hírek. Megparancsolom, hogy készítsenek elô egy csapdát ezeknek a gazembereknek. Ha jól értetted és az informátorod igazat mondott, akkor elkapjuk ezeket a gazembereket, és akkor a kormányzó elôtt kérvényezni fogom, hogy jutalmazzon meg.";
			link.l1 = "Köszönöm! Majd meglátogatlak, ha végeztünk.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Rendben. Rendben.";
			link.l1 = "Hamarosan találkozunk, biztos úr.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_BelizComendantPrison");
		break;
		
		case "caleuche_7":
			if (sti(pchar.questTemp.Caleuche.BelizChance) < 3)
			{
				dialog.text = "Meleg fogadtatással készültünk a gazembereknek, ha-ha-ha-ha! Bárcsak láthattad volna az arcukat! Mindenkit elkaptunk, beleértve a fôkolompost is! Néhányan megpróbáltak ellenállni, de bátor katonáink kiiktatták ôket.";
				link.l1 = "Kitûnô hírek, tiszt úr! Most már Belize polgárai végre nyugodtan alhatnak.";
				link.l1.go = "caleuche_12";
			}
			else
			{
				dialog.text = "Hmm... A katonáim egész éjjel várták ôket a barlangnál, de senki sem jelent meg. Az ôrmester nagyon dühös volt. Még jó, hogy még mindig nem kapott el.";
				link.l1 = "Az istenit! Ez nem lehet! Melyik barlangnál állítottatok rajtaütést? Kettô van belôlük!";
				link.l1.go = "caleuche_8";
			}
		break;
		
		case "caleuche_8":
			dialog.text = "Ahol mondtad. A jobb oldali elágazásnál...";
			link.l1 = "AZ A BAL OLDALI! Az elágazástól balra, ti idióták!";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "De tökéletesen emlékszem, hogy azt mondtad 'a jobbra.'.";
			link.l1 = "Uramisten! Balra! Azt mondtam, balra! A! BALRA! Hagytad ôket elszökni, és ez a te hibád volt!";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			AddQuestRecord("Caleuche", "16");
			dialog.text = "Akkor biztos motyogtál valamit az orrod alatt. Tudja, én elég jól hallok.";
			link.l1 = "Rendben, biztos úr, nem fogok vitatkozni. Segíteni akartam önnek, de nem lehet segíteni azokon, akik nem tudnak segíteni magukon. Viszontlátásra.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizChance");
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizRegard");
		break;
		
		case "caleuche_12":
			dialog.text = "Jelentettem a kormányzónak, hogy milyen szerepet játszott a banda felszámolásában. Nagyra értékelte a közremûködésedet, és felhatalmazott, hogy jutalmat adjak át neked: pénzjutalmat és egy trófeás arquebust.";
			link.l1 = "Köszönöm!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			Log_Info("Kaptál egy ládát dublonnal");
			Log_Info("Kaptál egy arquebust");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Caleuche", "17");
			GiveItem2Character(pchar, "chest"); 
			GiveItem2Character(pchar, "mushket3"); 
			dialog.text = "Köszönöm a szolgálatot, kapitány! Ha minden polgárunk olyan lelkiismeretes lenne, mint ön, már régen egyszer s mindenkorra legyôztük volna a bûntényt! Sok szerencsét!";
			link.l1 = "Viszlát, tiszt úr! Sok szerencsét a szolgálathoz!";
			link.l1.go = "caleuche_11";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, ENGLAND, 8);
			AddCharacterExpToSkill(pchar, "Leadership", 300);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
