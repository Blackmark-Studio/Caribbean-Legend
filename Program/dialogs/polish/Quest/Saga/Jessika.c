// Джессика Роуз - нежить и супербосс
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Chcesz czegoś?";
			link.l1 = "Nie, to nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// бой на рифе
		case "reef":
			PlaySound("Voice\English\saga\Jessica Rose-06.wav");
			dialog.text = "Ty! Przyprowadziłeś ją tutaj! Ona jest jego krwią i ciałem! Ona jest jej krwią i ciałem! Córka dziwki przyszła do grobu swojej matki! Zginie! A ty nie będziesz w stanie tego powstrzymać! Nie stawaj na drodze Jessiki! Zemsta należy do mnie!";
			link.l1 = "Ahoy, przyjacielu!";
			link.l1.go = "reef_1";
		break;
		
		case "reef_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "stage_1":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "Ha! Nie możesz mnie skrzywdzić!\n Powietrze, woda, ziemia, ogień - rozkazuję wam mi pomagać!\n Niech martwi powstaną, niech ogień płonie, niech woda strzeże mostu, a niech wiatr poniesie cię na swoich skrzydłach i rzuci na ziemię!\nBaw się dobrze!!!";
			link.l1 = "...";
			link.l1.go = "stage_1_exit";
		break;
		
		case "stage_1_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "top", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaFirstKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_2":
			PlaySound("Voice\English\saga\Jessica Rose-08.wav");
			dialog.text = "Ha! Nie możesz mnie skrzywdzić!\nNiech więcej zmarłych powstanie i zaatakuje, niech ogień spali kamień, niech wiatr uniesie cię i rzuci na ziemię, a ziemia niech wchłonie twoje siły!\nCiesz się!!!";
			link.l1 = "Zatrzymaj się, przyjacielu. Dokąd to zmierzasz w takim pośpiechu?";
			link.l1.go = "stage_2_exit";
		break;
		
		case "stage_2_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "rock", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.BladePenalty = 30;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaSecondKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_3":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "Ha! Nie możesz mnie zranić!\nNiech trucizna pokryje mój płomienny miecz, niech wiatr cię obejmie, niech woda wypije twoją zwinność!\nUmieraj! Ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "stage_3_exit";
		break;
		
		case "stage_3_exit":
			DialogExit();
			npchar.viper = true;
			TakeNItems(npchar, "potion2", 3);
			LAi_SetActorType(pchar);
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.EnergyPenalty = 2;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "quest", "bridge2");
			LAi_ActorTurnToLocator(pchar, "quest", "bridge1");
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaThirdKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_4":
			PlayStereoOGG("music_shore");
			sld = characterFromId("Svenson");
			dialog.text = "Dosyć... Jestem zmęczony. Jestem pokonany... Zlituj się nad losem nieszczęsnej Jessiki!";
			link.l1 = "Oczywiście... Oszczędzę twojej biednej duszy ciężaru tego martwego ciała!";
			link.l1.go = "exit_battle";
			if (CheckAttribute(sld, "quest.jessika_peace")) // выслушал историю Джессики
			{
				link.l2 = "Znam twoją historię, Jessico. I przykro mi, że twoje życie było tak smutne i skończyło się w ten sposób. Chcesz ze mną porozmawiać, prawda? Cóż, postaram się zapomnieć, że niedawno próbowałaś mnie zabić i cię wysłucham, chociaż nie będzie to dla mnie łatwe...";
				link.l2.go = "exit_talk";
			}
		break;
		
		case "exit_battle":
			DialogExit();
			SetMusic("music_teleport");
			DeleteAttribute(npchar, "viper");
			LAi_SetImmortal(npchar, false);
			npchar.chr_ai.hp = stf(npchar.chr_ai.hp)+100;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_JessikaDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.JessSeekTreatment = 0;
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
		break;
		
		case "exit_talk":
			dialog.text = "Dziękuję... Już wiesz o Beatrice Sharp i Lawrence... moim Lawrence. Zabiłam ją bez wahania, ale jego nie mogłam zabić. Nie mogłam tego zrobić, ale on mógł. Jessica zginęła...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef");
			NextDiag.TempNode = "exit_talk_0";
		break;
		
		case "exit_talk_0":
			dialog.text = "... ale krwawa przysięga, związana straszliwą przysięgą, wciąż nie została spełniona. Moc tej przysięgi pochodzi z indiańskiej magii. Wzbudziła zwłoki z grobu.\nNienawiść zamieniła moją duszę w pustynię. Każdy, kto przyszedł na tę rafę, został zgładzony moją ręką, a ich martwe ciała stały się moimi marionetkami. Mogę prosić o pomoc tylko tego, kto mnie pokonał...";
			link.l1 = "A co mogę dla ciebie zrobić? Jedyne, co mogę zrobić, to oszczędzić ci cierpienia...";
			link.l1.go = "exit_talk_1";
		break;
		
		case "exit_talk_1":
			PlaySound("Voice\English\saga\Jessica Rose-03.wav");
			dialog.text = "Pomóż mi... Zabierz mnie do niego.";
			link.l1 = "Do Lawrence'a Beltrope'a? A jak mam to zrobić? Moja załoga albo ucieknie, jak tylko cię zobaczą, albo spalą cię bez żalu. A przy okazji, wciąż potrafisz zarżnąć moich ludzi i 'kontrolować' ich...";
			link.l1.go = "exit_talk_2";
		break;
		
		case "exit_talk_2":
			dialog.text = "Nie zobaczą mnie. Ale ty tak. Musiałeś już zrozumieć, że posiadam moce niedostępne żywym. Ale nie mogę wejść na twój statek bez twojej zgody. Zabierz mnie do niego.\nNie zostanę z tobą długo. I nie skrzywdzę twoich ludzi. Wysadź mnie w zatoce Portland na Jamajce o północy, następnej nocy spotkamy się ponownie i otrzymasz to, czego chciałeś tutaj znaleźć.";
			link.l1 = "Skąd wiesz, dlaczego tu jestem?";
			link.l1.go = "exit_talk_3";
		break;
		
		case "exit_talk_3":
			PlaySound("Voice\English\saga\Jessica Rose-01.wav");
			dialog.text = "Ja wiem dużo. Więcej niż żywi. Widziałem ją... Potrzebujesz dokumentu dla niej i go dostaniesz. Dostaniesz nawet więcej, dam ci coś dodatkowo. Zabierz mnie do niego...";
			link.l1 = "Hm. Nie podobają mi się twoje krwiożercze zamiary wobec Heleny. Nie waż się jej nawet dotknąć. W końcu, ona nie jest odpowiedzialna za działania swojej matki.";
			link.l1.go = "exit_talk_4";
		break;
		
		case "exit_talk_4":
			dialog.text = "Pokonałeś mnie. Nie skrzywdzę jej... Obiecuję.";
			link.l1 = "To jeszcze nie koniec. Czy zamierzasz mnie uwolnić od swoich licznych klątw? Przyznaję, nie podoba mi się myśl o życiu z nimi na zawsze...";
			link.l1.go = "exit_talk_5";
		break;
		
		case "exit_talk_5":
			dialog.text = "To nie jest takie proste... Kiedy spotkamy się w Portland Cove po tym, jak ja... Powiem ci, jak się wyleczyć.";
			link.l1 = "Po tobie co?.. Co masz na myśli?";
			link.l1.go = "exit_talk_6";
		break;
		
		case "exit_talk_6":
			dialog.text = "Po moim spotkaniu z nim.";
			link.l1 = "Och, on nie będzie zadowolony. Mogę sobie wyobrazić. Dobrze, podsumujmy: po pierwsze, obiecujesz, że nikt cię nie zobaczy, po drugie, nie skrzywdzisz mojej załogi, po trzecie, nawet nie pomyślisz o Helen, po czwarte, dasz mi to, czego szukam, a po piąte, uwolnisz mnie od swoich klątw. Mam rację?";
			link.l1.go = "exit_talk_7";
		break;
		
		case "exit_talk_7":
			dialog.text = "Prawie. Nie uleczę cię, ale powiem ci, jak to zrobić. Będziesz musiał zrobić to sam.";
			link.l1 = "Dobrze. Umowa stoi. Pozwalam ci zaokrętować się na mój statek.";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef2");
			NextDiag.TempNode = "exit_talk_8";
		break;
		
		case "exit_talk_8":
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			dialog.text = "";
			link.l1 = "Ej! Gdzie jesteś? Po prostu zniknąłeś...";
			link.l1.go = "exit_talk_9";
		break;
		
		case "exit_talk_9":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			pchar.quest.Saga_JessFire.over = "yes"; 
			pchar.quest.Saga_JessFire1.over = "yes"; 
			pchar.quest.Saga_JessFire2.over = "yes";
			ref chr = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(chr, "hell_fire_1");
			DeleteAttribute(chr, "hell_fire_2");
			DeleteAttribute(chr, "hell_fire_3");
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Shadows", "9");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.Saga.JessOnShip = "true"; // атрибут на отрицательные последствия
			pchar.quest.Saga_Jessika_Travel.win_condition.l1 = "Hour";
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.start.hour = 0.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.finish.hour = 2.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l2 = "location";
			pchar.quest.Saga_Jessika_Travel.win_condition.l2.location = "shore36";
			pchar.quest.Saga_Jessika_Travel.function = "Saga_JessikaOnJamaica";
			NextDiag.CurrentNode = "shore";
			npchar.greeting = "jessika_2";
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
			LAi_LocationDisableOfficersGen("shore36", true);//офицеров не пускать в бухту Портленд
		break;
		
		case "shore":
			dialog.text = "Dotrzymałeś słowa - jesteśmy na Jamajce. Przyjdź tutaj jutro w nocy, a dotrzymam swojej obietnicy. Żegnaj.";
			link.l1 = "Żegnaj...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Saga.JessOnShip");
			DeleteAttribute(npchar, "SaveItemsForDead");
			DeleteAttribute(npchar, "DontClearDead");
			LAi_SetActorType(npchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Shadows", "10");
			SetFunctionTimerCondition("Saga_JessikaShoreWait", 0, 0, 1, false);
			NextDiag.CurrentNode = "shore_2";
			npchar.greeting = "jessika_3";
		break;
		
		case "shore_2":
			dialog.text = "To koniec, "+pchar.name+"Hello, lad.";
			link.l1 = "Co masz na myśli?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "To już koniec... Proszę, weź to, to jest to, czego szukałeś. To list mojej rywalki, został z nią pochowany. Jest dobrze zachowany. Wybaczyłem jej i nie ma już nienawiści w mojej duszy.";
			link.l1 = "Czy... spotkałeś się z nim? Z Lawrence'em?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			GiveItem2Character(pchar, "letter_beatriss"); // дать письмо
			AddQuestRecordInfo("Letter_beatriss", "1");
			dialog.text = "Tak. Ostatnią rzeczą, którą poczuł w swoim życiu, był horror. Nie jest mi go żal.";
			link.l1 = "Niech Bóg przebaczy jego grzeszną duszę... Wygląda na to, że nigdy go nie spotkam.";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Nie straciłeś nic wartościowego. Był bardzo złym człowiekiem. Teraz powinniśmy się pożegnać, nie mam tu już nic do zrobienia. Moja przysięga została spełniona, a magia straciła swoją moc. Obiecałem ci prezent. Oto mój Flamberge. Nie potrzebuję go już. Ta klinga jest wyjątkowa, nie znajdziesz lepszej na całym świecie.";
			link.l1 = "Dzięki...";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			RemoveAllCharacterItems(npchar, true);
			GiveItem2Character(pchar, "blade_25");
			PlaySound("interface\important_item.wav");
			dialog.text = "Teraz, o tobie. Udaj się do Bridgetown, do lokalnego kościoła, aby zdjąć moje klątwy. Znajdziesz tam księdza. Znał mnie osobiście. Porozmawiaj z nim, a powie ci, co robić. Przygotuj dwadzieścia świec, będą ci potrzebne.";
			link.l1 = "Czy jesteś pewien, że mnie wyleczy?";
			link.l1.go = "shore_7";
		break;
		
		case "shore_7":
			dialog.text = "Sam to zrobisz. Bóg cię poprowadzi. Bądź pewny. Wszystko będzie dobrze.";
			link.l1 = "Dobrze, natychmiast popłynę na Barbados. I co teraz?";
			link.l1.go = "shore_8";
		break;
		
		case "shore_8":
			PlaySound("Voice\English\saga\Jessica Rose-04.wav");
			dialog.text = "A teraz życzę sobie jeszcze jednej rzeczy. Pochowaj moje ciało tutaj, przy tej zatoce, blisko morza. Tego pragnę. Może pewnego dnia odwiedzisz grób biednej Jessiki. Żegnaj, "+pchar.name+",  i módl się za mnie...";
			link.l1 = "Jess?..";
			link.l1.go = "shore_9";
		break;
		
		case "shore_9":
			DialogExit();
			LAi_KillCharacter(npchar);
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("shore36", false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("Shadows", "11");
			pchar.questTemp.Saga.JessTreatment = "true";
			// вытираем Белтропа
			sld = characterFromId("Beltrop");
			sld.lifeday = 0;
			pchar.questTemp.Saga.Beltrop_die = "true"; // Белтроп убит
			sld = ItemsFromID("letter_jess");
			sld.price = 1; // страницу можно выкладывать 270912 
		break;
		
		case "soul":
			dialog.text = "Czy mnie rozpoznajesz, Kapitanie?";
			link.l1 = "Czy to... czy to ty? Ale jak?";
			link.l1.go = "soul_1";
		break;
		
		case "soul_1":
			dialog.text = "Tak, "+pchar.name+", to ja, Jessica! Przynajmniej tak wyglądałam dwadzieścia lat temu.";
			link.l1 = "Więc... czy ja umarłem? Ale kiedy? Jak?";
			link.l1.go = "soul_2";
		break;
		
		case "soul_2":
			dialog.text = "Nie jesteś martwy, "+pchar.name+" . Jesteś teraz w kościele w Bridgetown. Po prostu... śpisz.";
			link.l1 = "Czy to tylko sen? Wszystko wygląda zbyt realnie...";
			link.l1.go = "soul_3";
		break;
		
		case "soul_3":
			dialog.text = "Zdarza się czasem, "+pchar.name+" Bóg cię wysłuchał. Twoje modlitwy nie tylko cię uzdrowiły, ale również oczyściły moją duszę. Dziękuję ci bardzo, "+pchar.name+" ! I chcę Cię prosić o wybaczenie za to, co się stało na rafie. To jest... cóż, po prostu mi wybacz. Nie mogłem odejść, nie prosząc o przebaczenie.";
			link.l1 = "Przebaczam ci, Jessico. Czy naprawdę żyję?";
			link.l1.go = "soul_4";
		break;
		
		case "soul_4":
			dialog.text = "Jesteś... Nie martw się. Wkrótce się obudzisz. Chciałem się tylko pożegnać.";
			link.l1 = "Jesteś taka... piękna!";
			link.l1.go = "soul_5";
		break;
		
		case "soul_5":
			dialog.text = "Czy mnie lubisz? Tak, był czas, gdy najlepsi kawalerowie z Małych Antyli zabiegali o mnie, a co trzeci pirat z Isla Tesoro był gotów stanąć do pojedynku o mnie.";
			link.l1 = "Ale zawsze potrzebowałeś tylko jednego... Eh, rudy talizmanie! Powiedz mi tylko, dlaczego skończyłeś tak?";
			link.l1.go = "soul_6";
		break;
		
		case "soul_6":
			dialog.text = "Z powodu mojego gniewu. Z powodu mojej nienawiści. Z powodu niezdolności do zrozumienia, wybaczenia i zapomnienia. Mogłem zacząć nowe życie, ale wolałem poświęcić się głupiej i bezsensownej zemście. Uwolniłeś mnie. Dziękuję, "+pchar.name+"...";
			link.l1 = "Naprawdę mi przykro z powodu twojego życia...";
			link.l1.go = "soul_7";
		break;
		
		// здесь проверяем Мэри
		case "soul_7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{ // Мэри-офицер
				dialog.text = "Nie... Wciąż masz swój talizman imbiru...";
				link.l1 = "Moje co?";
				link.l1.go = "mary_1";
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CheckAttribute(pchar, "questTemp.LSC.marywait"))
			{ // Мэри осталась на острове
				dialog.text = "Nie... Wciąż masz swój talizman z imbirem...";
				link.l1 = "Moje co?";
				link.l1.go = "mary_3";
				break;
			}
			dialog.text = "Nie... Weź pod uwagę moje smutne doświadczenie i nie powtarzaj moich błędów. I nie pozwól, by ludzie, których kochasz, również je popełniali.";
			link.l1 = "Przemyślę to i na pewno nie popełnię tych samych błędów...";
			link.l1.go = "soul_8";
		break;
		
		case "mary_1":
			dialog.text = "Pomyśl trochę. Ona jest na twoim statku.";
			link.l1 = "Mary?!";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Tak. Ona jest najlepsza, jaką kiedykolwiek będziesz miał w swoim życiu. Pamiętaj o tym. Jej miłość jest czysta, jej oddanie jest nieskończone. Jest odważna, młoda, ale zdesperowana i niedoświadczona. Nie rozumie wielu rzeczy. Zadbaj o nią, chroń ją i nie pozwól nikomu stanąć między wami obojgiem. Ona jest twoim talizmanem...";
			link.l1 = "Ja... Nigdy jej nie opuszczę i będę chronił ją przed wszelkim niebezpieczeństwem.";
			link.l1.go = "soul_8";
		break;
		
		case "mary_3":
			dialog.text = "Jest na dziwnej wyspie zbudowanej z martwych statków... Nie jest tam sama, ale czuje się samotna. Każdy jej poranek zaczyna się myślą o tobie, każdego dnia modli się za ciebie, każdej nocy w jej kajucie pali się światło, a jej poduszka jest mokra od łez...";
			link.l1 = "Mary...";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "Między wami obojgiem jest córka. Córka kobiety, która kiedyś stała między mną a Lawrence'em. Los twojego talizmanu jest w twoich rękach. Nie mogą współistnieć razem, tak jak ja i Beatrice nie mogliśmy.";
			link.l1 = "Skąd to wiesz?";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Druga strona... Pokazuje wiele... To twój wybór, ale pamiętaj: Mary to najlepsza, jaką kiedykolwiek będziesz miał w swoim życiu. Jej miłość jest czysta, jej oddanie nieskończone. Jest odważna, młoda, ale zdesperowana i niedoświadczona. Nie rozumie wiele. Potrzebuje twojej ochrony, twojej opieki i twojej miłości. Jest twoim talizmanem.";
			link.l1 = "Rozważę to. Na pewno to zrobię...";
			link.l1.go = "soul_8";
		break;
		
		case "soul_8":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) sTemp = "";
			else sTemp = "And about the daughter of Beatrice, know that your noble actions on her behalf will be left unvalued. Soon you will see that for yourself. Be careful with her. Well...\n";
			dialog.text = ""+sTemp+"Muszę iść. Czas się pożegnać... Na serio tym razem. Nie zapomnij o Jessice i spróbuj czasem odwiedzić jej grób... Tylko ty wiesz, gdzie jest.";
			link.l1 = "Oczywiście, Jess. Odwiedzę to miejsce i będę się za ciebie modlił.";
			link.l1.go = "soul_9";
		break;
		
		case "soul_9":
			dialog.text = "Dziękuję. Do widzenia, "+pchar.name+"Do widzenia!";
			link.l1 = "Żegnaj, Jessico...";
			link.l1.go = "soul_10";
		break;
		
		case "soul_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_JessikaSoul_4", -1);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
