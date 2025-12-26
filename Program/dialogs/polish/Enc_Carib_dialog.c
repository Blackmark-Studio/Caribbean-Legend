void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, iMush, qty;
	string sGroup, sLink, sText;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "First time":
			dialog.text = "Gratulacje! To jest błąd. Skontaktuj się z Jasonem i powiedz mu, jak i gdzie go znalazłeś. Pokój!";
			link.l1 = "Zrobię to natychmiast!";
			link.l1.go = "exit";
			Diag.TempNode = "First time";
		break;

		case "exit_fight":
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_peace":
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}	
			ChangeIndianRelation(1.00);
		break;
		
		// военные индеи - карибы
		case "war_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				dialog.text = LinkRandPhrase("Chwała tobie, synu morza! Słyszałem o tobie. Możesz spokojnie stąpać po naszej ziemi.",""+npchar.name+"wita cię, blade twarzy bracie. Cieszymy się, że możemy cię gościć.","Witam cię, odważny blednolicy wojowniku!"+npchar.name+" cieszy się na spotkanie z przyjacielem Indian. Idź w pokoju!");
				link.l1 = RandPhraseSimple("Powitaj z tobą, bracie o czerwonej skórze! Dobrej polowania ci życzę!","Pozdrowienia, dzielny wojowniku! Niech bogowie błogosławią tobie i twojej rodzinie!");
				link.l1.go = "exit_peace";
				if (CheckCaribGuns())
				{
					npchar.quest.count = 0;
					link.l2 = RandPhraseSimple("Mam coś, co może być dla ciebie interesujące, czerwonoskóry bracie. Chcesz handlować?","Mogę zaproponować ci zakup czegoś interesującego, dzielny wojowniku. Chcesz handlować?");
					link.l2.go = "war_indian_trade";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Stój, bladej twarzy! Z jakim prawem chodzisz po mojej ziemi?","Stój, biały człowieku! Jesteś na ziemi moich przodków i mojej ziemi!","Stop, blada twarz! Nie należysz do mojej ziemi");
				link.l1 = RandPhraseSimple("Twoja ziemia? Zgub się, ty czerwona morda!","Spójrz na niego - mówiąca małpa! Znikaj, teraz!");
				link.l1.go = "war_indian_1";
				link.l2 = RandPhraseSimple("Przybyłem w pokoju, czerwonoskóry wojowniku. Nie powinniśmy walczyć bez powodu.","Nie jestem wrogiem dla ciebie i twojej ziemi, wojowniku. Przybyłem w pokoju.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/3)) > hrand(80)) link.l2.go = "war_indian_2_1";
				else link.l2.go = "war_indian_2_2";
				link.l3 = RandPhraseSimple("Przybyłem handlować z tobą, nie walczyć.","Nie walczę z Indianami. Handluję z nimi.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/6)+makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE)/6)) > hrand(90)) link.l3.go = "war_indian_3_1";
				else link.l3.go = "war_indian_3_2";
			}
		break;
		
		case "war_indian_1":
			dialog.text = RandPhraseSimple("Żałujesz, że się urodziłeś, blado twarzowy piesku... Wytnę twoje serce i usmażę na ogniu!","Zmuszę cię do jedzenia kamieni, bladolicy pieseł! Śmiejemy się, kiedy błagasz o śmierć na kolanach, biały kundlu!");
			link.l1 = RandPhraseSimple("Czy nadal nie możesz zamknąć swojego smrodliwego pyska, pomalowany strach na wróble? Zepchnę cię z powrotem do dżungli, skąd przyszedłeś!","Zarzucasz mi groźby, padlino?! Cóż, teraz będziesz wspinać się z powrotem na drzewo, z którego właśnie zszedłeś!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_2_1":
			dialog.text = RandPhraseSimple("Słyszę, że twój głos mówi prawdę. Nie wyciągamy przeciwko tobie naszych toporów tego dnia. Idź w pokoju, bladatwarz.","Białotwarz rzadko przynosi pokój, ale widzę w twoich oczach, że mówisz prawdę. Idź teraz.");
			link.l1 = RandPhraseSimple("Mądra decyzja, wojowniku. Powodzenia tobie.","Cieszę się, że doszliśmy do porozumienia, wojowniku.");
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_2_2":
			dialog.text = RandPhraseSimple("Kłamiesz, blady psie! Przybyłeś tu, aby zabić Indian! Gotowy na bitwę, blady?","Zabijasz Indian. Biała mowa to kłamliwa mowa. Obetnę ją i usmażę na ogniu!");
			link.l1 = RandPhraseSimple("Cóż, kumple, nie obwiniaj mnie potem. Bóg wie, że starałem się tego uniknąć...","Cóż, sam o to prosiłeś, wojowniku.");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_3_1":
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				dialog.text = "Handel? Potrzebujemy broni białych ludzi. Jednoręczna ognista broń bladolicznych! W zamian oferujemy nasze towary! Masz ognistą broń do wymiany?";
				link.l1 = "Hmm. Mam. A co mi dasz w zamian?";
				link.l1.go = "war_indian_trade";
				link.l2 = "Ty łotrzyku! A potem będziesz strzelać do kolonistów z moich pistoletów? Nie, to się nie wydarzy! A co do was, szakale, teraz was wszystkich posiekam...";
				link.l2.go = "exit_fight";
			}
			else
			{
				dialog.text = "Nie masz tego, czego chcemy, bladotwarz... Staniesz się naszym trofeum wojennym!";
				link.l1 = "Spróbuj, jeśli masz odwagę, strach na wróble...";
				link.l1.go = "exit_fight";
			}
		break;
		
		case "war_indian_3_2":
			dialog.text = RandPhraseSimple("Nie handlujemy z bladymi psami. Zabijamy i zabieramy!","Nie jesteśmy brudnymi miskito czy arawakami, nie handlujemy z bladymi twarzami! Zabijamy ich i zdobywamy trofea wojenne!");
			link.l1 = RandPhraseSimple("No to spróbuj mnie obrabować, łotrzyku!","Najpierw musisz zabrać ode mnie mój szabla, ty szumowino!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_trade":
			iGun = 1;
			dialog.text = "Pokaż co masz, a my powiemy, co za to damy.";
			for (i=6; i>=1; i--)
			{
				if (GetCharacterFreeItem(pchar, "pistol"+i) > 0)
				{
					sLink = "l"+iGun;
					link.(sLink) = "Offer "+XI_ConvertString("pistol"+i)+".";
					link.(sLink).go = "gun_"+i;
					iGun++;				
				}
			}
		break;
		
		case "gun_1":
			npchar.quest.gun = "pistol1";
			if (hrand(1) == 0)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(1)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(9)+14);
				iTotalTemp = hrand(2)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "Hej-ho! Dajemy ci za to "+sText+".";
			link.l1 = "Zgoda!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nie. Nie ma mowy.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_2":
			npchar.quest.gun = "pistol2";
			if (hrand(3) < 2)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(3)+1);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "Hej-ho! Sprytne oręż... Damy ci za to "+sText+".";
			link.l1 = "Zgoda!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nie. Absolutnie nie.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_3":
			npchar.quest.gun = "pistol3";
			if (hrand(5) < 3)
			{
				qty = rand(1)+2;
				npchar.quest.item = "jewelry5"+qty;
				iTotalTemp = hrand(6)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful pearl";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(2)+2);
				iTotalTemp = hrand(2)+5;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  this beautiful stone";
			}
			dialog.text = "Hej-ho! Potężna broń! Zabiła wiele-wiele wrogów! Damy ci za to "+sText+".";
			link.l1 = "Zgoda!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nie. Nie ma mowy.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_4":
			npchar.quest.gun = "pistol4";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(10)+qty*30;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "obereg_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hej-ho! Straszna broń... Damy ci za to "+sText+".";
			link.l1 = "Ugoda!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nie. Nie ma mowy.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_5":
			npchar.quest.gun = "pistol5";
			if (hrand(7) < 7)
			{
				if (hrand(10) < 8)
				{
					npchar.quest.item = "jewelry7";
					iTotalTemp = 2+hrand(1);
				}
				else
				{
					npchar.quest.item = "jewelry8";
					iTotalTemp = hrand(4)+10;
				}
				qty = hrand(1)+1;
				npchar.quest.item = "jewelry"+(qty+6);
				if (qty == 1) iTotalTemp = 2;
				else iTotalTemp = hrand(5)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful and precious petrified tar";
			}
			else
			{
				npchar.quest.item = "indian_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hej-ho! Piękna i potężna broń! Zabije wiele-wiele wrogów! Damy ci ją za to "+sText+".";
			link.l1 = "Zgoda!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nie. Nie ma mowy.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_6":
			npchar.quest.gun = "pistol6";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(8)+qty*20;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "amulet_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hej-ho! Wygodna broń... Damy ci za to "+sText+".";
			link.l1 = "Zgoda!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nie. Nie ma mowy.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "war_indian_trade_agree":
			ChangeIndianRelation(1.00);
			npchar.quest.count = sti(npchar.quest.count)+1;
			TakeNItems(pchar, npchar.quest.item, iTotalTemp);
			RemoveItems(pchar, npchar.quest.gun, 1);
			Log_Info("You have given "+XI_ConvertString(npchar.quest.gun)+"");
			Log_Info("You have received "+XI_ConvertString(npchar.quest.item)+" in amount of "+FindRussianQtyString(iTotalTemp)+"");
			PlaySound("interface\important_item.wav");
			if (sti(npchar.quest.count) > 3+hrand(2));
			{
				dialog.text = "Dobrze. Tutaj twoje towary. Nie handlujemy już. Przyjdź później. Lepiej ognista broń, więcej damy za to. Teraz idź!";
				link.l1 = "Żegnaj, czerwonoskóry wojowniku.";
				link.l1.go = "exit_peace";
			}
			else
			{
				dialog.text = "Dobrze. Tutaj twoje towary. Masz więcej ognistych broni do wymiany?";
				if (CheckCaribGuns())
				{
					link.l1 = "Mam. Kupisz?";
					link.l1.go = "war_indian_trade";
				}
				link.l2 = "Nie. Następnym razem przyniosę więcej.";
				link.l2.go = "war_indian_trade_exit";
			}
		break;
		
		case "war_indian_trade_exit":
			dialog.text = "Przynieś. Lepsza ognista broń, więcej damy za to. Teraz idź!";
			link.l1 = "Do widzenia, wojowniku...";
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_trade_bad":
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				DialogExit();
				sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
				for(i = 0; i < iTemp; i++)
				{
					sld = CharacterFromID(sTemp + i);
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sGroup);
					LAi_SetImmortal(sld, false);
					LAi_CharacterDisableDialog(sld);
				}	
			}
			else
			{
				dialog.text = "Wtedy bierzemy wszystko za darmo, bladolicy!";
				link.l1 = "Możesz spróbować...";
				link.l1.go = "exit_fight";
			}
		break;
		
		// мирные индеи - мискито
		case "peace_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase("Cześć, biały człowieku. Czego potrzebujesz w naszej dżungli?","Nasza dżungla jest bardzo niebezpieczna. Co tu robisz?","Co cię tutaj przynosi, odważna blada twarzy?");
			link.l1 = RandPhraseSimple("Tylko przechodziłem, przyjacielu o czerwonej skórze. Wierzę, że na tej ścieżce jest wystarczająco dużo miejsca dla nas obojga?","Pozdrowienia, synu dżungli! Jestem tutaj w interesach i nie walczę przeciwko Indianom.");
			link.l1.go = "peace_indian_1";
			link.l2 = RandPhraseSimple("A dlaczego musisz wiedzieć? Idź swoją drogą i trzymaj się z dala od kłopotów!","Pójdź swoją drogą, czerwonoskóry. Nie mam czasu z tobą rozmawiać.");
			link.l2.go = "peace_indian_2";
		break;
		
		case "peace_indian_1":
			dialog.text = RandPhraseSimple("Jesteśmy pokojowym ludem. Nie jesteśmy wrogami białych ludzi. Idź, ale bądź ostrożny na naszej ziemi!","Cieszę się, że spotkałem bladotwarzego przyjaciela Indian. Idź w pokoju, synie morza!");
			link.l1 = RandPhraseSimple("Powodzenia tobie też, synu selvy...","Żegnaj, czerwonoskóry przyjacielu.");
			link.l1.go = "exit_peace";
		break;
		
		case "peace_indian_2":
			dialog.text = RandPhraseSimple("My jesteśmy pokojowi łowcy. Ale nie pozwolimy, gdy blada twarz tak mówi na naszej ziemi!","Nie walczymy z białymi ludźmi, ale jeśli biali ludzie nas obrażą, odpowiadamy tak, jak nauczyli nas nasi przodkowie!");
			link.l1 = RandPhraseSimple("Czy nadal nie możesz zamknąć swojego śmierdzącego pyska, pomalowany strachu? Wygonię cię z powrotem do dżungli, z której wyszedłeś!","Ośmielasz się grozić mi, szumowino?! Teraz wrócisz na to drzewo, z którego właśnie zszedłeś!");
			link.l1.go = "exit_fight";
		break;
	}
}
