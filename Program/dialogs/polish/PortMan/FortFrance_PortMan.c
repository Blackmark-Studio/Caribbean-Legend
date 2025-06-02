// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakiego rodzaju pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Już próbowałeś zadać mi pytanie "+GetAddress_Form(NPChar)+"... ","Już trzeci raz dzisiaj mówisz o jakimś pytaniu...","Spójrz, jeśli nie masz nic do powiedzenia o sprawach portu, to nie zawracaj mi głowy swoimi pytaniami.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie.","Nie mam o czym rozmawiać."),"Nieważne.","Rzeczywiście, już trzeci raz...","Przykro mi, ale na razie nie interesują mnie sprawy portu.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "ship" && !CheckAttribute(npchar, "quest.RescueDaughter"))
		{
			DelLandQuestMark(npchar);
			link.l1 = "Sir, szukam pracy. Ale nie pracy tragarza, coś bardziej odpowiedniego dla mojego rangi. Misja, służba, z delikatnymi sprawami... Przyjmę każde zadanie, które macie.";
			link.l1.go = "Sharlie";
		}
		//<-- Бремя гасконца
		
		// Jason „олго и счастливо
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "portman")
		{
			link.l1 = "Powiedziano mi, że masz dla mnie list. Nazywam się Kapitan Charles de Maure.";
			link.l1.go = "LH_letter";
		}
		break;
		
		case "Sharlie":
			dialog.text = "Pomoc? Hm. Radzę sobie, dzięki Bogu. Ale jeden z moich przyjaciół naprawdę potrzebuje pomocy i to pilnie. Zamierza wejść sam do dżungli, by walczyć z Indianami, to absolutne szaleństwo!\nPróbowałem go przekonać, błagałem go, ale nie słuchał! Za bardzo martwi się o swoją córkę i jest gotów oddać za nią życie!";
			link.l1 = "Zaczekaj, zacznijmy od nowa: kim jest twój przyjaciel, gdzie mogę go znaleźć i jakiej pomocy potrzebuje?";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			dialog.text = "Ach, przepraszam, jestem po prostu zbyt niespokojny. Nazywa się Prosper... Prosper Troubale. Na pewno zginie! A ja nie mogę mu pomóc - nie jestem żołnierzem. Jego córka zaginęła, a on wierzy, że to miejscowi Indianie są odpowiedzialni. Wyobraź sobie, planuje sam iść za dzikimi dzikusami! Rozsieczą go na kawałki... W tej chwili kupuje muszkiet i szykuje się do wyjścia do selwy!";
			link.l1 = "Jesteś marnym bajarzem, panie. Gdzie mogę znaleźć twego przyjaciela... jak on się nazywał... Prosper?";
			link.l1.go = "Sharlie_2";			
		break;
		
		case "Sharlie_2":
			dialog.text = "Rozmawiałem właśnie z nim i próbowałem go przekonać, by zmienił zdanie. Nie jest daleko od bram miasta, przy studni, sprawdza swoją muszkietę i amunicję. Idź do niego i zrób coś! Jeśli pójdzie sam do dżungli, nie wróci, jestem tego pewien. Czerwono-skórzy diabły go rozszarpią...";
			link.l1 = "Przestań bredzić, brzmisz jak stara baba! Od razu idę do twego przyjaciela. Mam nadzieję, że będę w stanie mu pomóc.";
			link.l1.go = "Sharlie_3";			
		break;
		
		case "Sharlie_3":
			DialogExit();
			AddQuestRecord("SharlieF", "1");
			RescueDaughter_CreateProsper();
			npchar.quest.RescueDaughter = "true";
			QuestPointerDelLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		// Jason „олго и счастливо
		case "LH_letter":
			dialog.text = "Tak, masz rację - jest koperta. Oto ona, ale najpierw musisz zapłacić za dostawę - dwanaście tysięcy srebrnych pesos.";
			if (sti(pchar.money) >= 12000)
			{
				link.l1 = "Zawsze podejrzewałem, że twój handel to w gruncie rzeczy złodziejski interes, ale jakoś przegapiłem wiadomość, hm. Proszę, oto twoje pieniądze.";
				link.l1.go = "LH_letter_1";
			}
			else
			{
				link.l1 = "Wrócę trochę później, myślę, że zostawiłem mój sakiewkę w tawernie.";
				link.l1.go = "exit";
			}
		break;
		
		case "LH_letter_1":
			DialogExit();
			AddMoneyToCharacter(pchar, -12000);
			LongHappy_RecibeLetter();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
