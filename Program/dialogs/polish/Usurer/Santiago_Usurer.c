// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś już zadać mi to pytanie niedawno...","Tak, pozwól zgadnąć... Znowu kręcisz się w kółko?","Słuchaj, ja tu zajmuję się finansami, nie odpowiadam na pytania...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam teraz nic do powiedzenia."),"Umph, gdzież to podziała się moja pamięć...","Zgadłeś, przepraszam...","Rozumiem...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит, Голландия
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				link.l1 = "Senior, jestem kapitanem "+GetFullName(pchar)+", i jestem tutaj z polecenia Lucasa Rodenburga. Mam dla ciebie paczkę od niego.";
				link.l1.go = "SantiagoTripBank";	
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripReturn")
			{
				link.l1 = "Przyszedłem po odpowiedź seniora Lucasa Rodenburga.";
				link.l1.go = "SantiagoTripBank_3";	
			}
			//Голландский гамбит, Голландия
		break;
		
		case "SantiagoTripBank":
			if (GetCharacterItem(pchar, "Chest") >= 5)
			{
			dialog.text = "Wyobraź sobie... paczka! No, dawaj, seniorze.";
			link.l1 = "Także, Senior Rodenburg prosił, bym ci to przekazał...";
			link.l1.go = "SantiagoTripBank_1";
			RemoveItems(PChar, "NPC_Letter", 1);
			RemoveItems(PChar, "Chest", 5);
			DelLandQuestMark(npchar);
			}
			else
			{
			dialog.text = "Z tego co wiem, miałem otrzymać coś jeszcze oprócz paczki, kapitanie. Więc... gdzie to jest? Rozumiesz, o czym mówię?";
			link.l1 = "Ależ oczywiście! Skrzynie są pod bezpieczną strażą na moim statku. Dostarczę je do ciebie natychmiast.";
			link.l1.go = "exit";
			}
		break;
		
		case "SantiagoTripBank_1":
			dialog.text = "Hm-m... interesujące. Więc on 'przesyła swoje ubolewania'. No cóż. Chociaż ubolewania seniora Rodenburga są dość przekonujące, trudno zaprzeczyć. Seniorze, napisanie odpowiedzi zajmie trochę czasu, czy mógłbyś przyjść jutro w południe, aby odebrać odpowiedź? Odpocznij w karczmie, przejdź się po mieście. Santiago ma wiele do zaoferowania.";
			link.l1 = "Zgoda, wrócę jutro około południa. Do zobaczenia wtedy, señor.";
			link.l1.go = "SantiagoTripBank_2";
		break;
		
		case "SantiagoTripBank_2":
			DialogExit();
			pchar.quest.SantiagoTripOver.over = "yes"; //снять таймер
			bDisableFastReload = true;
			pchar.quest.Santiago_Trip.win_condition.l1 = "location";
			pchar.quest.Santiago_Trip.win_condition.l1.location = "Santiago_town";
			pchar.quest.Santiago_Trip.function = "SantiagoTrip_Attack";
			pchar.questTemp.HWIC.Holl = "SantiagoTripAttack";
			LAi_LocationDisableOfficersGen("Santiago_town", true);//офицеров не пускать // 291112
		break;
		
		case "SantiagoTripBank_3":
			dialog.text = "Tak, oczywiście... ale sądzę, że możemy się obyć bez pisemnych formalności. Po prostu powiedz mu te słowa 'ten człowiek musi umrzeć'. To będzie sprawiedliwe i nie będziemy mieli żadnych problemów z oceną 'wartości' otrzymanych przeprosin. A incydent będzie uważany za całkowicie załatwiony.";
			link.l1 = "Dobrze, zapamiętam to, senor. Coś jeszcze?";
			link.l1.go = "SantiagoTripBank_4";
			DelLandQuestMark(npchar);
		break;
		
		case "SantiagoTripBank_4":
			dialog.text = "Tak, oczywiście. To, co powiedziałem, jest wolą rodziny Giraldi. I możesz, oczywiście, przekazać moje najlepsze życzenia Senorowi Lucasowi. Życzę ci pomyślnych wiatrów, kapitanie "+GetFullName(pchar)+".";
			link.l1 = "Rozumiem. Żegnaj, seniorze "+npchar.name+".";
			link.l1.go = "SantiagoTripBank_5";
		break;
		
		case "SantiagoTripBank_5":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "SantiagoTripFinal";
			LAi_LocationDisableOfficersGen("Santiago_town", false);//офицеров пускать // 291112
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
