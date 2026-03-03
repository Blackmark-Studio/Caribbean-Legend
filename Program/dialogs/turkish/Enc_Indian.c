//Jason диалог индейцев в джунглях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int iQty;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Solgun surat","Beyaz kadın")+" konuşmak mı istiyor?","Yine sen, "+GetSexPhrase("solgun surat","beyaz kadın")+".",""+GetSexPhrase("Solgun suratlı konuşmayı seviyor. Tipi bir Kızılderili kadınına benziyor.","Beyaz kadın konuşmayı seviyor.")+"","Beni buraya ruhlar getirdi, soluk yüzlü "+GetSexPhrase("kardeşim.","kız kardeş")+".","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Evet.","Evet, yine ben.","Çok şiirsel.","Seni görmekten ben de memnun oldum.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Selam, beyaz kardeş. Kızılla konuşmak mı istiyorsun?";
				link.l1 = "Ormanın oğlu, selamlar. Seninle tanıştığıma memnun oldum, fakat yoluma devam etmeliyim.";
				link.l1.go = "exit";
				link.l2 = "Evet. İlginç şeyler sattığını duydum. Satılık bir şeyin var mı?";
				link.l2.go = "select_trade";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "select_trade": //индейская торговля
			switch (hrand(7))
			{
				case 0: // торговля через интерфейс
					dialog.text = "Şanslısın, beyaz kardeş. "+npchar.name+" satılık bazı malları var. Bir göz at.";
					link.l1 = " Mallarını göster... ";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Dur bir dakika. Satacak bir şeyim var. Mangarosa adında bir bitki. Bu şeyleri sevdiğini duydum...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 1: // не торгует
					dialog.text = "Hayır, beyaz kardeş. "+npchar.name+" ticaret yapmıyor. "+npchar.name+"  bir savaşçı.";
					link.l1 = "Anladım. Peki, hoşça kal, kızıl derili kardeşim.";
					link.l1.go = "exit";
				break;
				
				case 2: // жемчуг большой
					npchar.quest.item.qty = 25+hrand(25);
					npchar.quest.item.price = 30+hrand(10);
					dialog.text = ""+npchar.name+" tanrıların gözyaşlarına sahip. Büyük olanlardan, beyaz kardeş. O kadar çok ki "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Onları almak mı istiyorsun? Şu fiyata satarım: "+FindRussianMoneyString(sti(npchar.quest.item.price))+" birine. ";
					link.l1 = "Hayır, ilgilenmiyorum.";
					link.l1.go = "exit";
					link.l2 = "Elbette! Böyle bir fiyata onları memnuniyetle alırım.";
					link.l2.go = "big_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Dur bir dakika. Satacak bir şeyim var. Adı Manga Rosa olan bir bitki. Bu şeyleri sevdiğini duydum...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 3: // жемчуг малый
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 10+hrand(5);
					dialog.text = ""+npchar.name+" tanrıların gözyaşları var. Küçük olanlardan, beyaz kardeşim. Şu miktarda "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Onları almak ister misin? Şu fiyata satarım: "+FindRussianMoneyString(sti(npchar.quest.item.price))+" birine.";
					link.l1 = "Hayır, ilgilenmiyorum.";
					link.l1.go = "exit";
					link.l2 = "Elbette! Böyle bir fiyata seve seve alırım.";
					link.l2.go = "small_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Dur bir dakika. Satacak bir şeyim var. Adı Manga Rosa olan bir bitki. Bu şeyleri sevdiğini duydum...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 4: //золотые самородки
					npchar.quest.item.qty = 20+hrand(20);
					npchar.quest.item.price = 90+hrand(20);
					dialog.text = ""+npchar.name+" siz soluk yüzlülerin çok sevdiği sarı metale sahip. Şu miktarda: "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Sadece  için satarım "+FindRussianMoneyString(sti(npchar.quest.item.price))+" birine.";
					link.l1 = "Hayır, ilgilenmiyorum.";
					link.l1.go = "exit";
					link.l2 = "Elbette! Böyle bir fiyata memnuniyetle alırım.";
					link.l2.go = "gold";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Dur bir dakika. Satacak bir şeyim var. Adı Manga Rosa olan bir bitki. Bu şeyleri sevdiğini duydum...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 5: // серебряные самородки
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 40+hrand(10);
					dialog.text = ""+npchar.name+" beyaz metali var, siz soluk yüzlülerin çok sevdiği. O kadar çok ki "+FindRussianQtyString(sti(npchar.quest.item.qty))+". Sadece  için satarım "+FindRussianMoneyString(sti(npchar.quest.item.price))+" birine.";
					link.l1 = "Hayır, ilgilenmiyorum.";
					link.l1.go = "exit";
					link.l2 = "Elbette! Böyle bir fiyata onları memnuniyetle satın alırım.";
					link.l2.go = "silver";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Dur bir dakika. Satacak bir şeyim var. Adı Manga Rosa olan bir bitki. Bu şeyleri sevdiğini duydum...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 6: // повтор через интерфейс
					dialog.text = "Şanslısın, beyaz kardeş. "+npchar.name+" satılık bazı malları var. Bir göz at.";
					link.l1 = "Bana mallarını göster...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Dur bir dakika. Sana satacak bir şeyim var. Adı Manga Rosa olan bir bitki. Bu şeyleri sevdiğini duydum...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 7: // повтор не торгует
					dialog.text = "Hayır, beyaz kardeş. "+npchar.name+"  ticaret yapmıyor. "+npchar.name+" -  bir savaşçı.";
					link.l1 = "Anladım. Peki, hoşça kal, kızıl derili kardeşim.";
					link.l1.go = "exit";
				break;
			}
		break;
		
		case "torg":
			DialogExit();
			if (CheckNPCQuestDate(npchar, "Torg_date"))
			{
                SetNPCQuestDate(npchar, "Torg_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = "First time";
			LaunchItemsTrade(NPChar, 0);
			ChangeIndianRelation(1.00);
		break;
		
		// большой жемчуг
		case "big_pearl":
			dialog.text = "Kaç damla gözyaşı almak istiyorsun?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "big_pearl_qty";
		break;
		
		case "big_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Şaka mı yapıyorsun, solgun yüzlü? Tanrıların gözyaşlarına ihtiyacın yok mu? O halde elveda.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Sana kaç damla gözyaşım olduğunu söyledim. Kızılla dalga mı geçiyorsun, soluk yüzlü? O zaman hoşça kal.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" gözyaşları mı? Peki. Bana ver bakalım "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", beyaz kardeş.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Al paran burada, kızıl derili kardeşim.";
				link.l1.go = "big_pearl_1";
			}
			link.l2 = "Şu anda yeterince param yok. Üzgünüm, incilerini satın alamam.";
			link.l2.go = "exit";
		break;
		
		case "big_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry52", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Al onları, beyaz kardeş. Artık seninler.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// малый жемчуг
		case "small_pearl":
			dialog.text = "Kaç damla gözyaşı satın almak istiyorsun?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "small_pearl_qty";
		break;
		
		case "small_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Şaka mı yapıyorsun, solgun yüzlü? Tanrıların gözyaşlarına ihtiyacın yok mu? O halde elveda.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Sana kaç gözyaşım olduğunu söyledim. Kızılla dalga mı geçiyorsun, soluk yüzlü? O zaman hoşça kal.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" gözyaşları mı? Peki. Bana veriyorsun "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", beyaz kardeş.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Al paran burada, kızıl derili kardeşim.";
				link.l1.go = "small_pearl_1";
			}
			link.l2 = "Şu anda yeterince param yok. Üzgünüm, incilerini satın alamam.";
			link.l2.go = "exit";
		break;
		
		case "small_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry53", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Al onları, beyaz kardeş. Artık seninler.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// золотые самородки
		case "gold":
			dialog.text = "Kaç tane almak istiyorsun?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "gold_qty";
		break;
		
		case "gold_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Şaka mı yapıyorsun, beyaz surat? Metale ihtiyacın yok mu? O zaman güle güle.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Sana kaç tane olduğunu söyledim. Kızılderiliyle alay mı ediyorsun, soluk yüz? O zaman hoşça kal.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" parçalar mı? Senden mi "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", beyaz kardeş.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Al paran burada, kızıl derili kardeşim.";
				link.l1.go = "gold_1";
			}
			link.l2 = "Şu anda yeterli param yok. Üzgünüm, altınını satın alamam.";
			link.l2.go = "exit";
		break;
		
		case "gold_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry5", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Al onları, beyaz kardeş. Artık seninler.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// серебряные самородки
		case "silver":
			dialog.text = "Kaç tane almak istiyorsun?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "silver_qty";
		break;
		
		case "silver_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "Şaka mı yapıyorsun, solgun surat? Metale ihtiyacın yok mu? O halde hoşça kal.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "Kaç tane olduğunu söyledim. Kızılderiliyle dalga mı geçiyorsun, soluk yüz? O zaman güle güle.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" parçalar mı? Şey, senden "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", beyaz kardeş.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Al paran burada, kızıl derili kardeşim.";
				link.l1.go = "silver_1";
			}
			link.l2 = "Şu anda yeterli param yok. Üzgünüm, gümüşünü satın alamam.";
			link.l2.go = "exit";
		break;
		
		case "silver_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry6", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Al onları, beyaz kardeş. Artık seninler.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// мангароса
		case "mangarosa":
			dialog.text = "Mangarosa mı? Görmek istiyorum.";
			link.l1 = "Al, bir bak...";
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			npchar.quest.mangarosa = "indian_"+(hrand(10)+1);
			dialog.text = "Evet. Bunun bir adı da Manga Rosa. Onu sana veririm, karşılığında muska isterim. Çok iyi bir muskadır, onun da bir adı var - "+XI_ConvertString(npchar.quest.mangarosa)+". Ticaret mi yapıyorsun?";
			link.l1 = "Dinle, kızıl derili kardeşim, bu bitki hakkında daha fazla şey öğrenmek istiyorum. Bana neden bu kadar çok ihtiyacın olduğunu anlatır mısın?";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			dialog.text = ""+npchar.name+" Anlamıyorum. Eğer takas yapmak istiyorsan, tılsımı Manga Rrosa karşılığında veririm. Yoksa, giderim.";
			link.l1 = "Eh, peki. Hadi takas yapalım.";
			link.l1.go = "mangarosa_3";
			link.l2 = "Hayır. Bu bitkiyi bir muska için vermem.";
			link.l2.go = "exit";
		break;
		
		case "mangarosa_3":
			Log_Info("You have received an amulet");
			GiveItem2Character(pchar, npchar.quest.mangarosa);
			RemoveItems(pchar, "cannabis7", 1);
			dialog.text = "Al götür "+XI_ConvertString(npchar.quest.mangarosa)+". İşe yarar.";
			link.l1 = "Hiç şüphe yok. Sana bol şans, kızıl tenli dostum.";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Kaderle oynama, solgun surat! Kılıcını indir!","Dinle, solgun surat, silahını indir ve konuşalım, bela istemiyorum.");
			link.l1 = LinkRandPhrase("Pekala.","Pekâlâ.","Dediğiniz gibi...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
