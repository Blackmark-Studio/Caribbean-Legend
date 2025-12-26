// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Devam et, ne istiyorsun?","Biz de tam bundan bahsediyorduk. Herhalde unuttunuz...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Bakın, burası bir dükkân. İnsanlar burada alışveriş yapar. Beni rahatsız etmeyin!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+", belki bir dahaki sefere.","Doğru, nedense unuttum...","Evet, gerçekten de üçüncü kez...","Hm, yapmayacağım...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason --> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Findcloves" && !CheckAttribute(npchar, "quest.Portugal"))
			{
   				link.l1 = "Dinle, şık kıyafetlere ihtiyacım var. Pahalı olanlardan, gerçek bir soylu gibi görünmek istiyorum. Bu tarz bir şeyin var mı?";
				link.l1.go = "Portugal_cloves";
			}
			//<-- Португалец
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten")
			{
				link.l1 = "Yakın zamanda 'Admirable' adında bir kalyon size bir parti deri getirdi. Bunu hatırlıyor musunuz?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		//Jason --> Португалец
		case "Portugal_cloves":
			dialog.text = "Asil kıyafetler mi? Tabii, burada bir takımım var: pantolon, yelek, ipek gömlek ve çizmeler. Fiyatı 20.000 peso. Kıyafetler çok kaliteli, rahat ve gerçekten dikkat çekici görünüyorlar, bu yüzden daha ucuza vermem.";
			if (sti(pchar.money) >= 20000)
			{
				link.l1 = "Harika! Ver bakalım.";
				link.l1.go = "Portugal_cloves_1";
			}
			link.l2 = "Hm... Şu anda o kadar param yok.";
			link.l2.go = "Portugal_cloves_nomoney";
		break;
		
		case "Portugal_cloves_nomoney":
			dialog.text = "O zaman paran olunca geri gel.";
			link.l1 = "Pekala. Geri döneceğim!";
			link.l1.go = "exit";
		break;
		
		case "Portugal_cloves_1":
			AddMoneyToCharacter(pchar, -20000);
			GiveItem2Character(pchar, "suit_1");
			Log_Info("You've received expensive clothing");
			PlaySound("interface\important_item.wav");
			dialog.text = "Buyurun.";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "exit";
			npchar.quest.Portugal = "true";
			sld = characterFromId("PortugalDoctor");
			sld.dialog.currentnode = "Portugal_doctor_4";
			DelLandQuestMark(characterFromId("Marigo_trader"));
			AddLandQuestMark(characterFromId("PortugalDoctor"), "questmarkmain");
			QuestPointerDelLoc("marigo_town", "reload", "reload6_back");
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		//<-- Португалец
		case "guardoftruth":
			dialog.text = "Evet. Zamanında geldi, malları boşalttı ve anlaştığımız gibi ödemesini yaptım. Neden soruyorsunuz?";
			link.l1 = "O geminin kaptanı Gaius Marchais, eski bir tanıdığımdır. Bu yüzden onu bulmaya çalışıyorum. Bana ondan sonra ne yaptığını söyleyebilir misiniz? Belki ona ek yük verdiniz ya da nereye gittiğinden bahsetti?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Nothing of that. I didn't offer him any freight; he didn't even ask for it. He didn't share his plans for the future with me. I don't even remember all the details, do you know how many people have come in and out of here since that time? He unloaded and sailed off and that's all I can say about him.";
			link.l1 = "Pekala. Yine de teşekkürler. Her şey gönlünüzce olsun!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "11");
			pchar.questTemp.Guardoftruth = "maarten1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
