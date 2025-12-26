// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Bana bu soruyu daha önce de sormuştunuz...","Evet, dur bakayım... Yine aynı şeyleri mi dönüp duruyorsun?","Dinleyin, burada finans işlerini ben yürütüyorum, sorulara cevap vermem...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye gitti...","Doğru tahmin ettiniz, üzgünüm...","Anlıyorum...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Mynheer, biraz alışılmadık bir meselem var. Gaius Marchais adında bir Fransız korsanının size yakın zamanda iki eşsiz eşya sattığını biliyorum: altın bir monstrans ve altın bir buhurdan. Onları sizden satın almak istiyorum.";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(npchar, "quest.GOT_chest") && CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "Sana küçük bir sandık dolusu dublon getirdim.";
                link.l1.go = "guardoftruth_3";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Ah, evet! Onları tabii ki hatırlıyorum! Gerçekten de orijinal ve daha da önemlisi, pahalı parçalardı. Ama çok geç kaldınız kaptan, artık elimde yoklar. Onları çoktan sattım.";
			link.l1 = "İnanılır gibi değil! Peki, bu tür kilise eşyalarıyla kim ilgilendi? Efendim, onları kime sattınız? Geri almaya çalışmak isterim...";
			link.l1.go = "guardoftruth_1";
			npchar.quest.utensil = "true";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Hm, peki neden sana müşterilerimin isimlerini vermeliyim?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "self_win")
			{
				link.l1 = "Belki de Valilik Matthias Beck'in gözünde iyi bir dost olduğum içindir ve senin için uygun bir yaptırım isteme hakkım vardır?";
				link.l1.go = "guardoftruth_2_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "holl_win")
				{
					link.l1 = "Belki de Hollanda Batı Hindistan Şirketi ile mükemmel ilişkilerim olduğu ve takımadadaki birçok Hollandalı yerleşimciye büyük yardımlar sağladığım içindir?";
					link.l1.go = "guardoftruth_2_2";
				}	
				else
				{
					link.l1 = "Belki de bunun parasını ben ödeyeceğim için?";
					link.l1.go = "guardoftruth_2_3";
					npchar.quest.GOT_chest = "true";
				}
			}
		break;
		
		case "guardoftruth_2_1":
			dialog.text = "Ah, elbette öylesiniz "+GetFullName(pchar)+", Lucas Rodenburg'un suç komplosunu ortaya çıkaran, valinin bizzat dostu olan biri... Bunu nasıl unutabilirim ki? Elbette, size anlatacağım.";
			link.l1 = "O halde, sizi dinliyorum.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_2":
			dialog.text = "Ah, doğru, haklısınız "+GetFullName(pchar)+", korsan 'hayalet gemisinin' büyük fatihi. Bunu nasıl unutabilirim? Elbette, sana anlatacağım.";
			link.l1 = "O halde, tamamen sizi dinliyorum.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_3":
			dialog.text = "Pekâlâ, o zaman. Ağzına kadar altın doblonlarla dolu bir sandık için, senden önce satın alanlar hakkında sana bilgi verebilirim sanırım.";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "Buyurun. Bunlar benim için çok değerli eşyalar...";
				link.l1.go = "guardoftruth_3";
			}
			else
			{
				link.l1 = "Pekâlâ, istediğinizi size getireceğim. Bunlar benim için çok değerli eşyalar...";
				link.l1.go = "exit";
			}
		break;
		
		case "guardoftruth_3":
			RemoveItems(pchar, "chest", 1);
			Log_Info("You've given a chest of doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Harika. O halde, sizinle bazı bilgiler paylaşmaya hazırım.";
			link.l1 = "Tamamen sizi dinliyorum.";
			link.l1.go = "guardoftruth_4";
			DeleteAttribute(npchar, "quest.GOT_chest");
		break;
		
		case "guardoftruth_4":
			dialog.text = "Altın tütsülüğü Rolande Moses adında bir adam satın aldı, daha çok Şapkalı Rollie olarak bilinir. Neden bu kasap değerli bir kilise eşyasına ihtiyaç duydu, anlayamıyorum ama nedense buna tarif edilemez bir sevinçle sahip oldu... Bu arada, Rollie'nin kendisiyle karşılaşacağından şüpheliyim.";
			link.l1 = "Neden böyle?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Çünkü yalnız İngiliz tüccarlarını gözü dönmüşçe soyan bu adam, kısa süre önce şilebini Albay Fox'un pençelerine sürdü. Kim olduğunu biliyor musun? ";
			link.l1 = "Kesinlikle! Antigua'daki St. John's'ta 'Deniz Tilkileri'nin komutanı...";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Pekala, o zaman neden zavallı Rolande'ı bir daha asla göremeyeceğimizi anlıyorsun. Albay, onun şonerini ve hayatta kalan tüm tayfasını ele geçirdi ve onları St. Jones'a teslim etti; muhtemelen orada çoktan boyunlarına ip geçirilmiştir.";
			link.l1 = "Anladım. Peki ya monstrans?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Ostensuar çok yakın zamanda Cumana'dan Señora Belinda de Ribero tarafından satın alındı. Oldukça tanınmış bir hanımefendi, bizzat Cumana valisi Fernando de Villegas'ın akrabası. Sanırım onu kiliseye hediye olarak sunmak istemiş.";
			link.l1 = "Señora Belinda de Ribero? Onu Cumana'da bulabilirim, değil mi?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Kesinlikle. Willemstad'dan doğruca eve gideceğini kendi söyledi.";
			link.l1 = "Pekala. Teşekkürler, "+npchar.name+", bana çok yardımcı oldun!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Her zaman beklerim, efendim. Ara sıra uğrayın!";
			link.l1 = "Sana bol paralı, aklı kıt müşteriler dilerim... Ha-ha!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			AddQuestRecord("Guardoftruth", "23");
			pchar.questTemp.Guardoftruth.Usurer = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
