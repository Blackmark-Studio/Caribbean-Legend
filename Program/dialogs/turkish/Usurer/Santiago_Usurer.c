// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Bana bu soruyu kısa bir süre önce de sormuştunuz...","Evet, dur tahmin edeyim... Yine aynı şeyleri mi dönüp duruyorsun?","Dinle, burada finans işlerini ben yürütüyorum, soruları yanıtlamam...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Doğru tahmin ettiniz, üzgünüm...","Anladım...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит, Голландия
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				link.l1 = "Señor, ben kaptanım "+GetFullName(pchar)+", ve Lucas Rodenburg'dan bir iş için buradayım. Onun size gönderdiği bir paketi getirdim.";
				link.l1.go = "SantiagoTripBank";	
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripReturn")
			{
				link.l1 = "Señor Lucas Rodenburg'un cevabını almak için geldim.";
				link.l1.go = "SantiagoTripBank_3";	
			}
			//Голландский гамбит, Голландия
		break;
		
		case "SantiagoTripBank":
			if (GetCharacterItem(pchar, "Chest") >= 5)
			{
			dialog.text = "Hayal et... bir paket! Hadi, ver bakalım onu, señor.";
			link.l1 = "Ayrıca, Señor Rodenburg bunu size vermemi istedi...";
			link.l1.go = "SantiagoTripBank_1";
			RemoveItems(PChar, "NPC_Letter", 1);
			RemoveItems(PChar, "Chest", 5);
			DelLandQuestMark(npchar);
			}
			else
			{
			dialog.text = "Bildiğim kadarıyla, kaptan, paketten başka almam gereken başka bir şey daha vardı. Yani... nerede o? Ne demek istediğimi anlıyor musunuz?";
			link.l1 = "Elbette! Sandıklar gemimde güvenli bir şekilde korunuyor. Hemen size teslim edeceğim.";
			link.l1.go = "exit";
			}
		break;
		
		case "SantiagoTripBank_1":
			dialog.text = "Hm-m... ilginç. Yani, 'özürlerini iletiyor'. Pekâlâ, pekâlâ. Gerçi, señor Rodenburg'un özürleri oldukça etkileyici, inkâr etmek zor. Señor, uygun bir cevap yazmak biraz zaman alacak, yarın öğle civarı tekrar gelip cevabı alabilir misiniz? Bir handa dinlenin, şehirde dolaşın. Santiago'nun sunacak çok şeyi var.";
			link.l1 = "Pekala, yarın öğleye doğru tekrar geleceğim. O zaman görüşürüz, señor.";
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
			dialog.text = "Evet, elbette... ama yazılı formalitelere gerek kalmadan anlaşabileceğimize inanıyorum. Sadece ona şu sözleri iletin: 'bu adam ölmeli.' Bu adil olur, ve alınan özürlerin 'değerini' göz önünde bulundurursak hiçbir sorun yaşamayız. Olay da tamamen kapanmış sayılır.";
			link.l1 = "Pekala, bunu aklımda tutacağım, señor. Başka bir isteğiniz var mı?";
			link.l1.go = "SantiagoTripBank_4";
			DelLandQuestMark(npchar);
		break;
		
		case "SantiagoTripBank_4":
			dialog.text = "Evet, elbette. Söylediklerim Giraldi ailesinin iradesidir. Ve tabii ki, en iyi dileklerimi Señor Lucas'a iletebilirsiniz. Size de iyi rüzgarlar dilerim, kaptan "+GetFullName(pchar)+".";
			link.l1 = "Anladım. Hoşça kalın, señor "+npchar.name+".";
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
