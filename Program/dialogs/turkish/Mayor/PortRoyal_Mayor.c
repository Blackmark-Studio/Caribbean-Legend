// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsunuz? Sorunuzu sorun.","Sizi dinliyorum, sorun nedir?"),"Bu ikinci kez sormaya çalışıyorsunuz...","Bu üçüncü kez sormaya çalışıyorsunuz...","Bu ne zaman bitecek?! Ben sömürge işleriyle meşgul, yoğun bir adamım ve sen hâlâ beni rahatsız ediyorsun!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şimdi değil. Yeri ve zamanı değil."),"Doğru... Ama sonra, şimdi değil...","Birazdan soracağım... Ama şimdi değil...","Üzgünüm, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_8")
			{
				link.l1 = "Ekselansları, bu adada yasa dışı ticaret faaliyetleri olduğunu bildirmek isterim.";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_12")
			{
				link.l1 = "İpek yelken bezi kaçakçılığıyla ilgili görevinizin raporunu dinlemek isterim.";
                link.l1.go = "Mtraxx_4";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_10_continue" && !CheckAttribute(npchar, "quest.slaveships"))
			{
				link.l1 = "Vali-General Phillipe de Poincy adına geldim. Görevim, Hollandalılardan ele geçirilen köleleri teslim etmek, doğru mu?";
                link.l1.go = "patria_Sl";
			}
			if (CheckAttribute(npchar, "quest.slaveships.wait") && GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000)
			{
				link.l1 = "Söz verdiğim gibi köleleri getirdim.";
                link.l1.go = "patria_Sl_2";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_start" && CheckAttribute(pchar, "questTemp.Patria.Curacao.DoilyReady"))
			{
				link.l1 = "Genel Vali Phillipe de Poincy'nin talimatıyla, Hollandalılara karşı Curaçao'ya düzenlenecek ortak bir sefere katılmak üzere geldim.";
                link.l1.go = "patria_Sl_4";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_wait" && GetCompanionQuantity(pchar) < 3)
			{
				link.l1 = "Filom azaldı, şimdi yola çıkabiliriz.";
                link.l1.go = "patria_Sl_6";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "İlginç. Kulak kesildim.";
			link.l1 = "Güvenilir bir kaynağımdan aldığım bilgiye göre, İngiliz bayrağı altında seyreden Hollanda brigantini 'Utrecht', bir süredir Portland Körfezi'nde büyük miktarda ipek yelken bezi boşaltıyor. Bir yılı aşkın süredir, her ayın 10'u ile 15'i arasında, geceleri faaliyet gösteriyorlar.";
			link.l1.go = "Mtraxx_1";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Kaynağınıza gerçekten güvenebilir misiniz?";
			link.l1 = "Bazen kendime bile güvenemem, ancak bu bilgiyi veren adam güvenilirdir. Ayrıca, yalan söylemesi için hiçbir nedeni yoktu.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
			string sTemp = "this";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
            dialog.text = "Pekâlâ, kaptan. Bu ciddi bir mesele ve bana sunulan bilgilere göre hareket etmeliyim, muhbiriniz yalan söylemiş ya da sadece yanılmış olsa bile. Belirtilen saatte sahil devriyesi göndereceğim ve verdiğiniz bilgiler doğrulanırsa cömertçe ödüllendirileceksiniz. Bu tür yasa dışı faaliyetler kesinlikle bastırılmalıdır.";
			link.l1 = "Seni göreceğim "+sTemp+" ayın 16'sında. O zamana kadar durum mutlaka çözülecektir.";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_11";
			int month = sti(pchar.questTemp.Mtraxx.month);
			pchar.quest.mtr_silk_smuggler.over = "yes";
			pchar.quest.mtr_silk_smuggler_over.over = "yes";
			DeleteQuestCondition("Mtraxx_SilkCreateSmuggler");
			DeleteQuestCondition("Mtraxx_SilkSmugglerFail");
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.hour  = 6;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.day   = 16;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.function = "Mtraxx_SilkSmugglerPatrol";
			sTemp = "this";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
			AddQuestRecord("Roger_2", "19");
			AddQuestUserData("Roger_2", "sDate", sTemp);
			if (CharacterIsAlive("Mtr_Utreht"))
			{
				sld = CharacterFromID("Mtr_Utreht");
				sld.lifeday = 0;
			}
		break;
		
		case "Mtraxx_4":
            dialog.text = "Bilgileriniz doğru çıktı, kaptan. Suçluları alışveriş sırasında pusuya düşürdük. 'Utrecht' kaçmaya çalıştı ve karşılık verdi, ancak devriye korvetimiz tarafından batırıldı. Dört alıcı tutuklanmaya direndi. Biri vurularak öldürüldü, diğer üçü ise ormana kaçtı. Seksen top ipeğin tamamı Port Royal hazinesine aktarıldı. Bu ağın başındaki kişiyi tespit edemesek de, ölen kişi kimliği belirsiz ve diğerleri kaçmış olsa da, bu operasyonu tam bir başarı olarak ilan ediyorum. Bu alçakların bir daha buraya dönmeye cesaret edeceklerini sanmıyorum.\nDikkatli davranıp sahtekârları ortaya çıkardığınız için bize büyük bir iyilik yaptınız, kaptan. İşte ödülünüz olarak 10.000 peso.";
			link.l1 = "Çok teşekkür ederim, Ekselansları. Her şeyin planladığımız gibi gitmesine ve kaçakçıların hak ettiklerini bulmasına sevindim. Şimdi izninizi istiyorum. Size iyi günler dilerim.";
			link.l1.go = "Mtraxx_5";
		break;
		
		case "Mtraxx_5":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_13";
			AddQuestRecord("Roger_2", "20");
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		// Jason НСО
		case "patria_Sl":
			if (GetSquadronGoods(pchar, GOOD_SLAVES) < 500)
			{
				dialog.text = "Doğru. Kaç köle getirdiniz?";
				link.l1 = "Hâlâ üzerinde çalışıyorum. Sonuçlarla yakında döneceğim.";
				link.l1.go = "patria_Sl_wait";
				break;
			}
			dialog.text = "Doğru. Kaç köle getirdiniz?";
			link.l1 = ""+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000) link.l1.go = "patria_Sl_2";
			else link.l1.go = "patria_Sl_1";
		break;
		
		case "patria_Sl_wait":
			DialogExit();
			npchar.quest.slaveships.wait = "true";
		break;
		
		case "patria_Sl_1":
			dialog.text = "Hmm, Şövalye en az 3.000 köle olacağına dair söz vermişti";
			link.l1 = "Evet, doğru. Bu benim hatam: kölelerin bir kısmı düşman gemisinin top ateşiyle öldü, bazıları ise yolda hayatını kaybetti. Hatalarımı telafi edip size geri döneceğim. Her şey anlaşmaya uygun şekilde yapılacak.";
			link.l1.go = "patria_Sl_wait";
		break;
		
		case "patria_Sl_2":
			DeleteAttribute(npchar, "quest.slaveships.wait");
			dialog.text = "Mükemmel! Chevalier de Poincy ile gerçekten iş yapılır. Genel Vali'ye, Curaçao saldırısı için filomun bir ay içinde hazır olacağını söyleyin. Eminim bu sefer için sizi bana gönderecektir, o halde yakında görüşürüz, Monsieur de Maure.";
			link.l1 = "Sizi tekrar görmekten memnuniyet duyarım, Albay. Ve şimdi müsaadenizle veda edeyim.";
			link.l1.go = "patria_Sl_3";
		break;
		
		case "patria_Sl_3":
			DialogExit();
			npchar.quest.slaveships = "true";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, GetSquadronGoods(pchar, GOOD_SLAVES));
			AddQuestRecord("Patria", "57");
			pchar.questTemp.Patria = "epizode_10_return";
			pchar.quest.Patria_SlaveShipsJamaicaTimeOver.over = "yes"; //снять таймер на доставку рабов
			SetFunctionTimerCondition("Patria_CuracaoDoilyReady", 0, 0, 30, false); // таймер на 1 месяц на готовность эскадры д'Ойли
			SetFunctionTimerCondition("Patria_CuracaoTimeOver", 0, 0, 62, false); // таймер на 2 месяца на туда-обратно к Пуанси
			SaveCurrentQuestDateParam("questTemp.Patria.Curacao.Date"); // запоминаем дату
			// меняем отношение наций
			pchar.questTemp.Patria.Friend = "true";
			LaunchNationLegend();
			DeleteAttribute(pchar, "questTemp.Patria.Friend");
			DoQuestCheckDelay("sea_victory", 0.2);
		break;
		
		case "patria_Sl_4":
			dialog.text = "Sen olacağından hiç şüphem yoktu. Daha da iyi! Filomuz hazır. Bir birinci sınıf savaş gemisi ve iki dördüncü sınıf gemi. Tüm filonun toplam mevcudu beş gemiyi aşmamalı.";
			if (GetCompanionQuantity(pchar) > 2)
			{
				link.l1 = "O zaman fazladan gemileri iskelede bırakıp sadece iki tanesini alacağım. Sonunda beş gemimiz olacak.";
				link.l1.go = "patria_Sl_5";
			}
			else
			{
				link.l1 = "Evet, tam olarak beş, daha fazla değil. Harekete geçmeliyiz.";
				link.l1.go = "patria_Sl_6";
			}
		break;
		
		case "patria_Sl_5":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_wait";
		break;
		
		case "patria_Sl_6":
			dialog.text = "Mükemmel. Şimdi sana nasıl hareket edeceğimizin planını açıklayacağım: belki değiştirmek ya da eklemek istediğin bir şey olur, sonra da bunu tartışırız.";
			link.l1 = "Sizi dinliyorum, Albay.";
			link.l1.go = "patria_Sl_7";
		break;
		
		case "patria_Sl_7":
			dialog.text = "Curacao'yu ele geçirmenin bir anlamı yok: Burası takımadadaki başlıca Hollanda kolonisi ve Willemstad kalesinde onların bayrağını indirip yerine İngiliz ya da Fransız bayrağı çeksek bile adayı elde tutmak çok zor olacaktır. Hollandalılar adayı geri almak için ellerinden geleni yapacak ve askeri filolarını oraya yönlendireceklerdir. Genel olarak, zorunlu olmadığı için ele geçirmenin bir anlamı yok. Bizim için asıl önemli olan, Stuyvesant'ı bizim için avantajlı şartlarda anlaşmayı imzalamaya zorlamak; bunun için de düşmanın ana savunmalarını yok etmek ve Hollandalıları Willemstad kolonisinin tamamen yok edilmesi tehdidiyle karşı karşıya bırakmak yeterli olacaktır.";
			link.l1 = "Antlaşma ne hakkında olacak?";
			link.l1.go = "patria_Sl_8";
		break;
		
		case "patria_Sl_8":
			dialog.text = "Antlaşma, bizzat benim ve Chevalier de Poincy tarafından hazırlandı. Ticaretin çeşitli yönlerini, Şirket ile İngiltere arasındaki 'ticaret savaşının' sona ermesini, Stuyvesant'ın Sint Maarten adası üzerindeki iddialarının reddini ve sizi pek ilgilendirmeyen diğer siyasi meseleleri kapsıyor.";
			link.l1 = "Anlaşıldı.";
			link.l1.go = "patria_Sl_9";
		break;
		
		case "patria_Sl_9":
			dialog.text = "Here's the plan: first, with all our forces, we'll attack the fort and destroy it. The Dutch will expect a landing of troops, but we won't do that; the greatest casualties are usually suffered when storming a bastion from the sea. Instead, we will land assault teams at two points on the island: Cape Santa Maria and the Blanca lagoon, and we will advance overland to the city gate of Willemstad. I have ordered that field artillery be brought with us on the ships – there are no impenetrable thickets in Curaçao, and we will be able to wheel the cannons across the ground without any difficulty. While the Dutch are left puzzled as to what is happening, we will take the town under our sights from the jungle and block any chance of reinforcements arriving from the fort by land. After that, we will bombard the town with cannon fire. Surely, the garrison of the fort will attempt a sortie, but they will be powerless against field cannons and our musketeers, and even if their cannons in the fort remain operational, they won't be able to bring them into the jungle. In addition, our ships will simulate preparations for a seaborne landing to strike fear into the enemy and sap their morale. After some time, when the Dutch fully realise the hopelessness of their situation, we will summon their parliamentarians for negotiations. What do you think, captain?";
			link.l1 = "Harika bir plan! Ve en güzel yanı, kale duvarlarında hiçbir askerimizi kaybetmeyecek olmamız.";
			link.l1.go = "patria_Sl_10";
		break;
		
		case "patria_Sl_10":
			dialog.text = "Fikirlerimi beğenmene sevindim. O halde devam edelim!";
			link.l1 = "Hadi gidelim!";
			link.l1.go = "patria_Sl_11";
		break;
		
		case "patria_Sl_11":
			DialogExit();
			chrDisableReloadToLocation = true;
			pchar.questTemp.Patria = "epizode_11_continue";
			AddQuestRecord("Patria", "60");
			pchar.quest.Patria_CuracaoTimeOver.over = "yes"; // снять таймер 2 месяца
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "PortRoyal_townhall", "goto", "goto4");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 7.0);
			Patria_CuracaoSail();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
