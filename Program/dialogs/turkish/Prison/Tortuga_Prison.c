// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Konuş, dinliyorum";
			link.l1 = "Yanılmışım. Hoşça kal.";
			link.l1.go = "Exit";
		break;
		
		case "tonzag_bail":
			NextDiag.TempNode = "First_officer";
		
			dialog.text = "Tortuga'ya geliş amacınız nedir, Kaptan?";
			link.l1 = "Sana yalvarıyorum! Yoldaşıma yardım et, tüm sorularını cevaplayacağım!";
			link.l1.go = "tonzag_bail_a";
			link.l2 = "Sen böylesine önemli bir insansın ve tüm hapishane bir silah sesi duyduktan hemen sonra buraya tek başına, hiçbir koruma olmadan geldin, öyle mi?!";
			link.l2.go = "tonzag_bail_b";
		break;
		
		case "tonzag_bail_a":
			dialog.text = "Cevabını geciktirirken, o kan kaybediyor. Soruyu tekrar ediyorum.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_b":
			dialog.text = "Ne olduğunu yeterince biliyorum. Sorumu tekrar ediyorum.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Son şansın, Kaptan.";
			link.l1 = "Genel valinin bana verdiği görevi yerine getiriyorum!";
			link.l1.go = "tonzag_bail_truth";
			link.l2 = "Biliyorsunuz ki kendi gemimin kaptanıyım ve sözleşmeli olarak çalışıyorum. Ayrıca güzel adanızı yılda birkaç kez ziyaret ediyorum!";
			link.l2.go = "tonzag_bail_lies";
		break;
		
		case "tonzag_bail_truth":
			dialog.text = "Şüphelerim vardı ama tamamen emin değildim. Şanslısın ki birkaç gün önce Capsterville'de önemli bir toplantı yapıldı. Çok etkili bazı kişiler bir anlaşmaya varmayı başardı. Böylece artık benim düşmanım değilsin.";
			link.l1 = "Bize yardım edecek misiniz?";
			link.l1.go = "tonzag_bail_truth_1";
			
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
		case "tonzag_bail_truth_1":
			dialog.text = "Seni hemen serbest bırakacağım. Arkadaşın gemiye nakledilecek ve tedavi görecek.";
			link.l1 = "Teşekkür ederim...";
			link.l1.go = "tonzag_bail_truth_2";
		break;
		
		case "tonzag_bail_truth_2":
			dialog.text = "Az kalsın karaya oturuyordun, Charles! Git ve en az bir ay Tortuga'ya geri dönme. Ortalık yatışsın, öfkeler dinsin.";
			link.l1 = "Bunu yapacağım. Hoşça kal!";
			link.l1.go = "exit";
			link.l2 = "Hiçbir şey açıklamayacak mısın? Azıcık bile mi? ...";
			link.l2.go = "tonzag_bail_truth_3";
		break;
		
		case "tonzag_bail_truth_3":
			dialog.text = "Biri seni ihbar etti. Sözde, güzel adamıza kasıtlı olarak onurlu valisini öldürmek için gelmiş fanatik bir Katolikmişsin.";
			link.l1 = "Ben fanatik değilim!";
			link.l1.go = "tonzag_bail_truth_4";
		break;
		
		case "tonzag_bail_truth_4":
			dialog.text = "Usta işi yazılmış, inan bana. Bu işlerde iyiyimdir – en iyi iftiralar içinde en azından bir parça gerçek barındıranlardır.";
			link.l1 = "Raporu kim yazdı?";
			link.l1.go = "tonzag_bail_truth_a";
			link.l2 = "Kim katili hapishaneye soktu?";
			link.l2.go = "tonzag_bail_truth_b";
		break;
		
		case "tonzag_bail_truth_a":
			dialog.text = "Biri seni hemen La Roche'un bodrumundaki Huguenotların işkence masasına göndermek yerine birkaç günlüğüne hapiste tutmak istemiş.\nYeter, Charles. Git şimdi. Önce karşındaki meseleyle ilgilen, sonra... ne demek istediğimi anladın!";
			link.l1 = "Evet. Yapacağım. Hoşça kalın, Komutan.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail_truth_b":
			dialog.text = "Yaptım.";
			link.l1 = "Buradan ayrılmadan önce bir başkasını çağırtsan iyi edersin.";
			link.l1.go = "tonzag_bail_truth_b_threat";
			link.l2 = "Sizi dinliyorum, komutan.";
			link.l2.go = "tonzag_bail_truth_b_charm";
		break;
		
		case "tonzag_bail_truth_b_threat":
			AddComplexSelfExpToScill(100, 100, 100, 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "Sana hiçbir şey açıklamak zorunda değilim, Charles. Benim elime düştüğüne sevin, doğrudan amirimin eline değil. Ve şuna da sevin ki, tüm bu rahatsızlıkların bedelini bana sen değil, patronun ödeyecek.";
				link.l1 = "Tabiiiii... Patronumu benim kadar tanımıyorsun. Hoşça kal, komutan.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "Biliyor musun? Sanırım sana anlatacağım. Özel garnizon emeklilik fonuna cömert ve vergisiz bir bağış yapıldı. Minnettarlık göstergesi olarak, bağışçıya ünlü bir suçlunun hızlı ve yasal infazına katkıda bulunma izni verildi!";
				link.l1 = "Subayım mı?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "Arkadaşım mı?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_charm":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "Sana hiçbir şey açıklamak zorunda değilim, Charles. Benim elime düştüğüne sevin, üstlerimin eline değil. Ve şuna da sevin ki, tüm bu rahatsızlıkların bedelini bana sen değil, patronun ödeyecek.";
				link.l1 = "Tabiiiii... Patronumu benim kadar tanımıyorsun. Hoşça kal, komutan.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "Biliyor musun? Sanırım sana anlatacağım. Özel garnizon emeklilik fonuna cömert ve vergisiz bir bağış yapıldı. Minnettarlık göstergesi olarak, bağışçıya azılı bir suçlunun hızlı ve yasal infazına katkıda bulunma ayrıcalığı tanındı!";
				link.l1 = "Subayım mı?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "Arkadaşım mı?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_1":
			dialog.text = "Çık dışarı, Charles. Ve bu pisliği de yanında götür. Seçtiğin yoldaşlar... hayal kırıklığı yaratıyor.";
			link.l1 = "En azından bana şu... hamini nerede bulacağımı söyle?";
			link.l1.go = "tonzag_bail_truth_b_2";
		break;
		
		case "tonzag_bail_truth_b_2":
			dialog.text = "Anakarada. Hoşça kal, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.TonzagQuest.KnowMain = true;
			AddQuestRecord("Tonzag", "3.2");
		break;
		
		case "tonzag_bail_lies":
			dialog.text = "Hakkınızda bir şikayet yapıldı. Hem de çok ağır bir suçlama. Kaptan, açıkça tuzağa düşürülmüşsünüz ama... Sizi burada birkaç hafta daha tutmaya ve arkadaşınızı ölüme terk etmeye tamamen yetkim var. Tabii ki, eğer...";
			link.l1 = "Ne kadar?";
			link.l1.go = "tonzag_bail_lies_a";
			link.l2 = "Bana tuzak kuran kimdi? Katili hapishaneye sen mi aldın?";
			link.l2.go = "tonzag_bail_lies_b";
			
			AddDialogExitQuestFunction("Tonzag_Bailed");
		break;
		
		case "tonzag_bail_lies_a":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Lütfen Tortuga garnizonunun emeklilik fonuna, yerel sarrafa beş yüz dublon yatırın.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" Ve bu adada yüksek rütbeli bir hanımla işlere karışıp çıkardığın eski belalar için de yüz dublon daha ekleyelim.";
			}
			link.l1 = "Şu lanet kapıyı artık aç!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bail_lies_b":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Zaten yeterince vaktimi aldın. Git tefeciye ve Tortuga garnizonunun emeklilik fonuna beş yüz dublon yatır.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" Ve bu adada yüksek rütbeli bir hanımla işlere karışıp çıkardığın eski belalar için de yüz dublon daha ekleyelim.";
			}
			link.l1 = "Şu lanet kapıyı artık aç!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bailed":
			dialog.text = "";
			link.l1 = "Paralar yatırıldı. Hercule nerede?";
			link.l1.go = "tonzag_bailed_1";
		break;
		
		case "tonzag_bailed_1":
			dialog.text = "We gave him first aid and sent him to your ship. The scoundrel is tough; he'll most likely pull through. Farewell, Captain, and don't let me catch you on our island for a while!";
			link.l1 = "Böyle bir karşılamadan sonra buradan uzak duracağım! Elveda, Komutan.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
