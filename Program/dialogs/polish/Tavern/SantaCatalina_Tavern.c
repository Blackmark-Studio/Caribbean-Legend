// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			if(startHeroType == 4)
			{
				dialog.text = NPCStringReactionRepeat("Oczywiście, Helen. Co to takiego?","Ach, w końcu przypomniałeś sobie, czego chciałeś?","Jesteś pewien, że wszystko z tobą w porządku? Zaczynasz mnie martwić. Może powinieneś zobaczyć się z lekarzem? ","Dobrze, Helen. Odpocznij, zaczerpnij świeżego powietrza - krótko mówiąc, zrób sobie przerwę. Potem wróć. Mhm?","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Nie, nic takiego.","Nie, nie, przepraszam, że przeszkadzam.","Pewnie masz rację...","Tak, prawdopodobnie masz rację. To najlepsza rzecz, jaką można zrobić.",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),"Próbowałeś zadać mi jakieś pytanie niedawno, "+GetAddress_Form(NPChar)+"... ","Przez cały ten dzień to już trzeci raz mówisz o jakimś pytaniu...","Więcej pytań, jak sądzę?","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam teraz nic do powiedzenia."),"Umph, gdzież się podziała moja pamięć...","Tak, to naprawdę trzeci raz...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				link.l1 = "Słuchaj, "+npchar.name+"Kim jest Jan Svenson i jak mogę go znaleźć?";
                link.l1.go = "Svenson";
			}	
			//<-- Бремя гасконца
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Słuchaj, czy przybył tutaj do tego miasta jakiś alchemik, lekarz? Jest Włochem, ma około trzydziestu lat, nazywa się Gino Gvineili. Słyszałeś coś o tym?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "Svenson":
			dialog.text = "To pierwszy raz, kiedy spotykam człowieka, który nie wie, kim jest Leśny Diabeł. To przezwisko nadali mu Hiszpanie, a oni zaoferowali cały worek pełen złota za głowę tego korsarza z Wyspy Providence piętnaście lat temu! Tak, lata lecą... Ludzie już zaczynają zapominać o naszym Janie. Może naprawdę nadszedł czas, by odpoczął.";
			link.l1 = "Niedawno tu przybyłem i niewiele wiem...";
			link.l1.go = "Svenson_1";			
		break;
		
		case "Svenson_1":
			dialog.text = "Jeśli interesujesz się przeszłością, mogę sprzedać ci książkę historyczną. Wielu oddałoby za nią fortunę, ale ja...";
			link.l2 = "Nie kręć mi tu! Zadałem ci pytanie. Powtarzam. Gdzie mieszka Jan Svenson? Mam z nim poważną rozmowę do przeprowadzenia.";
			link.l2.go = "Svenson_2";
		break;
		
		case "Svenson_2":
			dialog.text = "Mieszka w rezydencji naprzeciwko domu naszego burmistrza, obok fontanny. Ale obecnie przeżywa ciężkie chwile i nie polecałbym go niepokoić, chyba że to sprawa najwyższej wagi.";
			link.l1 = "Z jakiego to powodu?";
			link.l1.go = "Svenson_3";			
		break;
		
		case "Svenson_3":
			dialog.text = "Jego ulubiona dziewczyna Helen, znana również jako Rumba, córka jego zmarłego starego przyjaciela Shawn McArthura, zaginęła. Spoczywaj w pokoju, stary człowieku... Jan traktuje młodą diablicę jak własną córkę, ponieważ nie ma swoich dzieci. Ale dziewczyna zniknęła wraz ze swoim szkunerem 'Tęcza' i całą załogą\nSzkoda mi dziewczyny. Rzadkiej urody, mądra też. Gorąca i zadziorna jak ogień, dlatego nazwali ją Rumba! Jej ojciec nauczył ją wszystkiego, co wiedział, odziedziczyła statek i każdy członek załogi pozostał po jej stronie. Nawet najstarsi wilki morskie uznali ją za kapitana...";
			link.l1 = "Piracka dama? Co mogło się z nią stać?";
			link.l1.go = "Svenson_4";			
		break;
		
		case "Svenson_4":
			dialog.text = "Kto wie... Tydzień to nie tak długo, ale wdowa po MacAthuru jest przekonana, że coś złego stało się jej córce i udało jej się przekonać Svensona o tym. Zebrał swoich ludzi i sam rozpoczął poszukiwania, ale jak dotąd bez rezultatu. 'Tęcza' i jej załoga po prostu zniknęły\nMogę ci powiedzieć, gdzie znaleźć Gladys za tysiąc sztuk ośmiu.";
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = "Twoja wiedza jest dość kosztowna, ale wzbudziłeś moje zainteresowanie. Oto twoje pieniądze. Gdzie ją znajdę?";
				link.l1.go = "Svenson_5";
			}
			else
			{
				link.l1 = "Nie rób tego. Sam sobie poradzę, jeśli będzie trzeba. Żegnaj, dzięki za opowieść!";
				link.l1.go = "Svenson_6";
			}		
		break;
		
		case "Svenson_5":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Jej dom jest obok przystani, na lewo od miejsca cumowania. Ale prawdopodobnie jej tam nie ma. Cały dzień spędza przy murach fortu, wypatrując swojej ukochanej córki. Musiała już wypłakać sobie oczy.";
			link.l1 = "Dzięki za opowieść! Do zobaczenia, kumplu!";
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
			dialog.text = LinkRandPhrase("Nie, nie znam nikogo takiego. Mamy zielarzy i lekarzy, ale żadnego o takim imieniu.","Pierwszy raz słyszę takie dziwne imię. Nie, nigdy nie odwiedził nas człowiek, o którym mówisz.","Nie mamy tu w ogóle alchemików. Mamy lekarzy, ale żaden z nich nie nosi tak dziwnego imienia.");
			link.l1 = "Rozumiem. To szkoda. Będę szukał dalej!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
