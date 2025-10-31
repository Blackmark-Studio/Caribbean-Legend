// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			if(startHeroType == 4)
			{
				dialog.text = NPCStringReactionRepeat("Persze, Helen. Mi az?", "Á, végre eszedbe jutott, mit akartál?", "Biztos, hogy jól vagy? Kezdesz aggasztani. Talán orvoshoz kéne menned? ",
							  "Rendben, Helen. Aludjon egy kicsit, szívjon friss levegôt - egyszóval, tartson egy kis szünetet. Aztán jöjjön vissza. Mhm?", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Nem, igazából semmit.", "Nem, nem, bocsánat a zavarásért.",
						  "Valószínûleg igazad van...", "Igen, valószínûleg igazad van. Ez a legjobb, amit tehetsz.", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek, " + GetAddress_Form(NPChar) + "?"), "Nemrég próbáltál feltenni nekem néhány kérdést, " + GetAddress_Form(NPChar) + "...", "Az egész nap folyamán ez a harmadik alkalom, hogy valamilyen kérdésrôl beszélsz...",
							  "További kérdések, gondolom?", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
						  "Igen, ez tényleg a harmadik alkalom...", "Nem, milyen kérdéseket?...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				link.l1 = "Figyeljen, "+npchar.name+", ki az a Jan Svenson, és hogyan találom meg?";
                link.l1.go = "Svenson";
			}	
			//<-- Бремя гасконца
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Figyeljen, nem érkezett ide a városba egy alkimista, egy orvos? Olasz, harminc év körüli, a neve Gino Gvineili. Hallottál róla valamit?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "Svenson":
			dialog.text = "Ez az elsô alkalom, hogy olyan emberrel találkozom, aki nem tudja, ki az Erdei Ördög. Hogy a becenevet a spanyolok adták neki, és egy egész zsák aranyat ajánlottak fel annak a providence-szigeti kalóznak a fejéért, még tizenöt évvel ezelôtt! Igen, repülnek az évek... Az emberek már kezdik elfelejteni a mi Janunkat. Talán tényleg itt az ideje, hogy pihenjen.";
			link.l1 = "Nemrég érkeztem ide, és nem sokat tudok...";
			link.l1.go = "Svenson_1";			
		break;
		
		case "Svenson_1":
			dialog.text = "Ha érdekel a múlt, eladhatok neked egy történelemkönyvet. Sokan egy vagyont adnának érte, de én...";
			link.l2 = "Ne kerülgess engem! Kérdeztem valamit. Ismétlem. Hol lakik Jan Svenson? Komoly beszélgetésem van vele.";
			link.l2.go = "Svenson_2";
		break;
		
		case "Svenson_2":
			dialog.text = "Egy kúriában lakik, szemben a polgármesterünk rezidenciájával, a szökôkút mellett. De jelenleg nehéz idôket él át, és nem javasolnám, hogy zaklassuk, hacsak nem a legfontosabb.";
			link.l1 = "Miért nem?";
			link.l1.go = "Svenson_3";			
		break;
		
		case "Svenson_3":
			dialog.text = "Kedvenc lánya, Helen, más néven Rumba, néhai régi barátja, Shawn McArthur lánya eltûnt. Nyugodj békében, öregem... Jan saját lányaként kezeli a fiatal ördögöt, hiszen neki nincsenek saját gyerekei. De a lány eltûnt a szkúnárral 'Rainbow' és az egész legénységgel együtt\nSzánom a lányt. Ritka szép, és okos is. Forró és tüzes, mint a tûz, ezért nevezték el Rumbának! Az apja tanította meg mindenre, amit tudott, ô örökölte a hajót, és a legénység minden egyes tagja mellette maradt. Még a legöregebb tengeri farkasok is elismerték ôt kapitánynak...";
			link.l1 = "Egy kalózkisasszony? Mi történhetett vele?";
			link.l1.go = "Svenson_4";			
		break;
		
		case "Svenson_4":
			dialog.text = "Ki tudja... Egy hét nem olyan hosszú idô, de MacAthur özvegye biztos benne, hogy valami rossz történt a lányával, és errôl sikerült meggyôznie Svensont. Kihívta az embereit, és maga is keresni kezdte, egyelôre eredménytelenül. 'Rainbow' és a legénysége egyszerûen eltûnt\nEzer pesóért meg tudom mondani, hol találod Gladyst.";
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = "A tudásod elég drága, de felkeltetted az érdeklôdésemet. Itt a pénzed. Hol találom meg?";
				link.l1.go = "Svenson_5";
			}
			else
			{
				link.l1 = "Ne tedd. Majd én elintézem, ha kell. Viszlát, köszönöm a történetet!";
				link.l1.go = "Svenson_6";
			}		
		break;
		
		case "Svenson_5":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Az otthona a móló mellett van, a kikötôhelytôl balra. De valószínûleg nincs ott. Egész nap az erôd falainál lóg és vigyáz a szeretett lányára. Biztos kisírta már a szemét.";
			link.l1 = "Köszönöm a történetet! Szia, haver!";
			link.l1.go = "Svenson_6";			
		break;
		
		case "Svenson_6"://устанавливаем Глэдис на форт
			DialogExit();
			ref sld = characterFromId("Gladis");
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl_8";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("JS_girl"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Nem, még nem. Vannak gyógynövényszakértôink és orvosaink, de ilyen nevûek nincsenek.","Most hallottam elôször ilyen furcsa nevet. Nem, még soha nem látogatott meg minket az az ember, akirôl beszél.","Nálunk egyáltalán nincsenek alkimisták. Orvosaink vannak, de ilyen furcsa nevûek nincsenek.");
			link.l1 = "Értem. Az nagy kár. Folytatom a keresést!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
