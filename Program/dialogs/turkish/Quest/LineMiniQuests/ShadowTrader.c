// Бесчестный конкурент
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bu bir hata. Geliştiricilere haber verin";
			link.l1 = "Tabii!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShadowGuarder":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Sen   "+pchar.questTemp.Shadowtrader.Guardername+"? Yerel tüccar beni gönderdi. Şu anda sabırsızlıkla sizi bekliyor.";
			link.l1.go = "ShadowGuarder_1";
			DelLandQuestMark(npchar);
		break;
	
		case "ShadowGuarder_1":
			dialog.text = "A-ah, ama onu burada bekliyordum! Bana meyhaneye geleceği söylendi! Üzgünüm, hemen gidiyorum.";
			link.l1 = "Pekala!";
			link.l1.go = "ShadowGuarder_2";
		break;
	
		case "ShadowGuarder_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("ShadowGuarder");	
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", pchar.questTemp.Shadowtrader.City +"_store", "goto", "goto2", "OpenTheDoors", 6);
			pchar.questTemp.Shadowtrader = "begin";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowAgent":
			dialog.text = "İyi akşamlar, kaptan. Ucuz mal mı arıyorsun, ha? Takip et beni!";
			link.l1 = "Önden git.";
			link.l1.go = "ShadowAgent_1";
		break;
	
		case "ShadowAgent_1":
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS4", "CommonFlamHouse", "barmen", "stay", "Shadow_inRoom", 40);
		break;
	
		case "ShadowTrader":
			dialog.text = "İyi akşamlar, efendim. Yeni bir müşteriyle tanışmak ne hoş, ha! Kendimi tanıtayım: Ben "+GetFullName(npchar)+" . Bu kasabadaki en ucuz mallar bende, sana temin ederim.";
			link.l1 = "Sonunda, karşılaştık..."+npchar.name+". Sanırım sizi hayal kırıklığına uğratacağım: Sizi ticaret için değil, bu pis işinizi bitirmek için arıyordum. Önemli bir adamın başına büyük bir bela oldunuz. Bu bela öyle büyüdü ki, sizi durdurmak için her yolu denemeye hazır...";
			link.l1.go = "ShadowTrader_1";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "Olduğun yerde kal, suçlu! Ticari bir işletme yürütmek için vergi ödemen gerektiğini bilmiyor muydun? Benim gözetimimde kimse yasaları çiğneyemez! "+GetFullName(npchar)+", kanunu çiğnedin ve çaldığın mallara artık el konuldu! Kapının hemen dışında silahlı askerler var, o yüzden sakın aptal numarası yapmaya kalkma!";
				link.l2.go = "ShadowTrader_2";
			}
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowTrader_1":
			dialog.text = "Gerçekten mi? Beklemiyordum... Sen de kimsin?! Bu bir tuzak! Bunu kimin yaptığını sanırım biliyorum! Ne pahasına olursa olsun... çocuklar, öldürün onu!";
			link.l1 = "Haydi dans edelim, alçak!";
			link.l1.go = "ShadowTrader_fight";
			NextDiag.currentnode = "ShadowTrader_6";
		break;
	
	case "ShadowTrader_2":
		dialog.text = "Aman Tanrım... subay, dinle! Anlaşalım. Sen akıllı ve merhametli bir adamsın! Sana beş bin sekizlik ödeyeyim, bizi ikinci kattan kaçır. Malları da alırsın, onlara ihtiyacın var, değil mi? Beni ne yapacaksın ki? Hemen şimdi şehirden ayrılırım, bir daha kimse bizi görmez. Hem paranı da alırsın. Ne dersin, subay?";
		link.l1 = "Gerçekten mi sanıyorsun, pislik, böyle önemsiz bir para için görevimi lekeleyeceğimi?";
		link.l1.go = "ShadowTrader_3";
		break;
	
	case "ShadowTrader_3":
		dialog.text = "Pekala, pekala, memur bey, al ne varsa al - 10.000 peso. Hepsi bu kadar, yemin ederim!";
		link.l1 = "Hm... Eğer seni tutuklarsam, tüm paran el konulacak... Peki öyle olsun! Bu kaçakçılık noktası kapatıldı ve bütün mallara el konuldu... Parayı ver ve defol. Bir daha burada gözükme!";
		link.l1.go = "ShadowTrader_4";
		break;
		
	case "ShadowTrader_4":
			dialog.text = "Teşekkür ederim, teşekkür ederim, teşekkür ederim, memur! İşte paranız, beni burada bir daha görmeyeceksiniz. Hadi gidelim!";
			link.l1 = "Defol yoksa seni tutuklamak zorunda kalacağım!";
			link.l1.go = "ShadowTrader_escape";
		break;
	
		case "ShadowTrader_fight":
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				sld.nation = PIRATE;
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "ShadowTrader_afterfight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	
		case "ShadowTrader_escape"://напугали
			AddMoneyToCharacter(pchar, 10000);
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			}
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 9.0);
			pchar.questTemp.Shadowtrader.End.Escape = "true";
			AddQuestRecord("Shadowtrader", "8");
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 250);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
	
		case "ShadowTrader_6":
			dialog.text = "Ah! Merhamet et, beni öldürme! Sana sahip olduğum her şeyi veririm!";
			link.l1 = "Tüm mallarına yetkililer tarafından el konulacak. Burada olanlardan sonra sana acıyacağımı gerçekten mi sandın?";
			link.l1.go = "ShadowTrader_7";
		break;
	
		case "ShadowTrader_7":
			dialog.text = "Ben... Ben sana bütün paramı ve eşyalarımı vereceğim! Yeter ki beni bırak! Bugün adadan ayrılırım, bir daha da beni burada görmezsin!";
			link.l1 = "Pekâlâ. Üzerinde ne varsa hepsini ver ve kaybol. Bir daha burada iş yapmaya kalkarsan, bir dahaki sefere o zavallı hayatını bağışlamam, seni haydut.";
			link.l1.go = "ShadowTrader_free";
			link.l2 = "Yok artık, alçak herif, beni satın alamazsın. Senin gibilerle başa çıkmanın tek yolu soğuk çelik ve sıcak kurşundur!";
			link.l2.go = "ShadowTrader_killed";
		break;
		
		case "ShadowTrader_free"://отпустили
			AddMoneyToCharacter(pchar, 20550);
			TakeNItems(pchar, "jewelry1", rand(5));
			TakeNItems(pchar, "jewelry2", rand(20));
			TakeNItems(pchar, "jewelry5", rand(20));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received items");
			LAi_SetPlayerType(pchar);
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 7.0);
			pchar.questTemp.Shadowtrader.End.Free = "true";
			AddQuestRecord("Shadowtrader", "9");
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddComplexSelfExpToScill(70, 70, 70, 70);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
	
		case "ShadowTrader_killed":
			DialogExit();
			AddDialogExitQuestFunction("ShadowTrader_KillToTrader_kino");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
