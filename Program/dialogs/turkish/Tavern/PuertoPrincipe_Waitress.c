// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Sorular, "+GetAddress_Form(NPChar)+"?","Size nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hm, neyin peşindesin, "+GetAddress_Form(NPChar)+"? ","Yine tuhaf sorularla mı geldin? Canım, git biraz rom falan iç...")+"","Bugün boyunca bu soruyu üçüncü kez gündeme getiriyorsun..."+GetSexPhrase(" Bunlar bir ilgi göstergesi mi?","")+"","Sanırım daha fazla sorunuz var, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim","Şu anda konuşacak bir şeyim yok."),"Hayır, hayır, güzelim...","Olmaz, canım...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_2"))
			{
				link.l1 = "Sana birkaç soru sormam lazım. Cin fıçısının kaybolduğu gün tavernada çalışıyordun, değil mi? O gün burada neler olduğunu bana anlatabilir misin?";
				link.l1.go = "OS_Tavern2_1";
			}
			//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern2_1":
			dialog.text = "Ben... Ben ne diyeceğimi bilmiyorum. Her şey normaldi, olağanüstü hiçbir şey yoktu.";
			link.l1 = "Öyle mi? Hiçbir tuhaflık yok mu? Peki ya seni rahatsız eden 'Deniz Canavarı' gemisinden o denizci? Sanki geceyi onunla geçirmek isteyeceğinden emindi.";
			link.l1.go = "OS_Tavern2_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern2_2":
			dialog.text = "Ah, o mu! O... sadece biraz fazla içti, hepsi bu. Burada sıkça olur böyle şeyler, bilirsiniz. Elbette onu teşvik etmedim, ama o bana asılmaya başladı. Ben de haddini bildirdim.";
			link.l1 = "Hiç mi cesaretlendirme yok? O başka bir hikaye anlatıyor. Neden bu sefer böyle bir kargaşa çıkardın da, diğer zamanlarda çıkarmadın?";
			link.l1.go = "OS_Tavern2_3";
		break;

		case "OS_Tavern2_3":
			dialog.text = "Ben... Ben sana başka ne söyleyebilirim ki! Gerçekten hiçbir şey bilmiyorum! Ben... bütün akşam göz önündeydim! Hiçbir şey görmedim, hiçbir şey duymadım! Fıçıya gelince... Ona ne olduğunu bilmiyorum! Neden bu sorgu? Ben sadece... her zamanki gibi işimi yapıyordum!";
			link.l1 = "Bir şeyler sakladığından şüpheleniyorum. Işıksız ve yiyeceksiz bir geceyi geminin ambarında geçirmek, hafızayı tazeler. Denemek ister misin? Yoksa düzgünce konuşacak mıyız?";
			link.l1.go = "OS_Tavern2_4_HO";
			link.l2 = "Bence bana anlattıklarından çok daha fazlasını biliyorsun. Şu anda nadir bir fırsatın var — bana her şeyi anlatırsan, bu küçük oyundaki rolünü kendime saklarım. Ama sessiz kalırsan — senin için işler daha da kötüleşir. Gerçeği senin yardımınla ya da sensiz ortaya çıkaracağım.";
			link.l2.go = "OS_Tavern2_4_harizma";
		break;

		case "OS_Tavern2_4_HO":
			dialog.text = "Ben... ben... her şeyi anlatacağım! Bütün suç benim... talibim Jack'in. Jack Veils! Beni 'Deniz Canavarı'ndan herhangi bir denizciyi kandırmam için ikna etti. Sonra bana kur yapmaya başlayınca, ben de ortalığı karıştırıp meyhaneciyi tezgâhın arkasından çıkarmalıydım. Ortalık biraz yatışınca, iki denizci kavga çıkarıp onu ana salonda oyalayacaktı. Tam olarak böyle oldu\nO sırada, 'Deniz Canavarı'nın kaptanı fıçıyı çalmayı başardı. Bildiğim... bildiğim her şey bu, "+GetSexPhrase("bey","hanımefendi")+"! Lütfen, beni ihbar etme! Ben sadece... Sadece... Jack’in bana sonunda biraz saygı göstermesini istedim! Sonuçta ona yardım ettim...";
			link.l1 = "Birine yardım ederken, diğerini gözünü kırpmadan kurda kuşa yem ettin ha?! Yine de sözümde duruyorum — bu işteki payını açığa çıkarmayacağım. Ama yaptıklarınla yaşamayı sen göze alacaksın! Aptallığın yüzünden meyhaneci büyük bir tehlikeye girebilirdi. Bu Jack denen adamını nerede bulabilirim? Unutma: bana yalan söylersen, geri dönerim. Dönüşümden hiç memnun kalmayacağına emin olabilirsin.";
			link.l1.go = "OS_Tavern2_5";
			AddComplexSelfExpToScill(40, 40, 40, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;

		case "OS_Tavern2_4_harizma":
			dialog.text = "Ben... ben... her şeyi anlatacağım! Her şey benim... talibim Jack'in suçu. Jack Veils! Beni, 'Deniz Canavarı'ndan herhangi bir denizciyi kandırmam için ikna etti. Sonra bana kur yapmaya başlayınca, ben de bir olay çıkarıp meyhaneciyi tezgâhın arkasından çıkarmalıydım. Ortalık biraz yatışınca, iki denizci kavga başlatıp onu ana salonda oyalayacaktı. Tam olarak böyle oldu\nO sırada, 'Deniz Canavarı'nın kaptanı fıçıyı çalmayı başardı. Bildiğim... bildiğim her şey bu, "+GetSexPhrase("bey","hanımefendi")+"! Lütfen beni ele verme! Ben sadece... Sadece... Sadece... Jack'in bana sonunda biraz saygı göstermesini istedim! Sonuçta ona yardım ettim...";
			link.l1 = "Birine yardım ederken diğerini gözünü kırpmadan kurda kuşa yem ettin ha?! Yine de sözümde duruyorum — bu işteki payını açığa çıkarmayacağım. Ama yaptıklarınla yaşamayı sen bileceksin! Aptallığın yüzünden meyhaneci büyük bir tehlikeye girebilirdi. Şu senin Jack nerede bulunur? Unutma: bana yalan söylersen geri dönerim. Ve bana güven, dönüşüm hiç hoşuna gitmez.";
			link.l1.go = "OS_Tavern2_5";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "OS_Tavern2_5":
			dialog.text = "Bu kadar ciddi olduğunu fark etmemiştim! Sonuçta sadece bir fıçı... Jack karşı sokakta oturuyor. Oradaki evi kiralıyor, ben... Daha fazlasını bilmiyorum! Lütfen beni affedin! Kaptan, yemin ederim bir daha asla böyle bir şey yapmayacağım!";
			link.l1 = "İşine geri dön, sakın ağlamaya kalkma — meyhaneci hiçbir şeyden şüphelenmemeli.";
			link.l1.go = "OS_Tavern2_6";
		break;
		
		case "OS_Tavern2_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_2");
			AddQuestRecord("OS", "4");
			
			//
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.cask_gin = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.map_full = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.jewelry2 = 10;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.GunPowder = 50;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.bullet = 50;
			
			PChar.quest.OS_Zasada.win_condition.l1 = "item";
			PChar.quest.OS_Zasada.win_condition.l1.item = "cask_gin";
			PChar.quest.OS_Zasada.function = "OS_Zasada";
			
			SetFunctionLocationCondition("DWH_Close_House", "PuertoPrincipe_QuestHouse_1", false);
		break;
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
