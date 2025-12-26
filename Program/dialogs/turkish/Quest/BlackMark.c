void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Ne istiyorsunuz?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;
		
		case "BM_Contra_1":
			dialog.text = "Sen kimsin, ve ne halt etmeye burada dolanıyorsun?!";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Sakin ol dostum. Sadece geçiyordum. Senin... her neyse, işine karışmayacağım.";
			}
			else
			{
				link.l1 = "Ha? Bu deniz feneri senin mi? Bir dahaki sefere, palmiye ağaçlarından birine adını yazan bir tabela as ya da lanet bir çit dik.";
			}
			link.l1.go = "BM_Contra_2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Contra_2":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Defol buradan! Eğer bir müşteriyi korkutup anlaşmayı bozarsan, ben...";
			}
			else
			{
				dialog.text = "Dinle evlat, benim ve adamlarımın seni çağırıp kılıcının dilin kadar keskin olup olmadığını görmemizi isteme. Sadece kaybol ve...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosPatrolPribegaet");
		break;
		
		case "BM_Contra_3":
			dialog.text = "Peki Frankie, hangisi?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_3_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay12", "1", 1.9);
		break;
		case "BM_Contra_3_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_4", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_4":
			dialog.text = "Hayır... Kahretsin, ama o suratların hiçbirini tanımıyorum.";
			link.l1 = "...";
			link.l1.go = "BM_Contra_4_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay15", "1", 1.9);
		break;
		case "BM_Contra_4_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_5", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_5":
			dialog.text = "Ne?! Emin misin?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_5_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolZhitel"));
		break;
		case "BM_Contra_5_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_6", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_6":
			dialog.text = "Sence ben kör müyüm?! Sana söylüyorum, ne...";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			CharacterTurnByChr(CharacterFromID("BM_PatrolOff"), CharacterFromID("BM_PatrolZhitel"));
			AddDialogExitQuest("BM_BarbadosMayakVystrel");
		break;
		
		case "BM_Contra_7":
			dialog.text = "Ne oluyor lan?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay9", "1", 1.9);
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_7_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_8", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_8":
			dialog.text = "Kim ateş etti?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_8_1";
			locCameraFromToPos(-84.11, 6.33, -62.68, true, -78.07, 3.20, -66.67);
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 1.9);
		break;
		
		case "BM_Contra_8_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_9", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_9":
			dialog.text = "Bizi aptal mı sandınız, pislikler? Hepiniz silahlarınızı yere bırakın! Sen de!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_9_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_9_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_10", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_10":
			dialog.text = "Sakin ol, subay. Biz değiliz, görmüyor musun? Silahlarımız yerlerinde duruyor. Sen de sakın kendi silahına davranma!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_10_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		case "BM_Contra_10_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_11", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_11":
			dialog.text = "Bana emir mi veriyorsun, seni alçak?! Hepsini hemen tutuklayın!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_11_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_11_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_12", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_12":
			dialog.text = "Siktir git! Bu olmayacak. Çocuklar, silah başına!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosMayakBoinya");
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		
		case "BM_Irons_1":
			dialog.text = "Hey, hey, dikkat et! O demiri böyle savurmaya devam edersen birinin başı fena halde belaya girebilir.";
			link.l1 = "Ha, kim?";
			link.l1.go = "BM_Irons_2";
			LAi_SetCurHPMax(npchar);
			SetOfficerToMushketer(npchar, "mushket1", true);
		break;
		
		case "BM_Irons_2":
			dialog.text = "Tabii ki, ben.";
			link.l1 = "Ne oluyor...? Sen de kimsin, lanet olsun?";
			link.l1.go = "BM_Irons_4";
			link.l2 = "Ben de tam olarak bunu yapmaya çalışıyorum. Devam edelim mi?";
			link.l2.go = "BM_Irons_3";
		break;
		
		case "BM_Irons_3":
			DialogExit();
			AddDialogExitQuestFunction("BM_Irons_DlgExit_1");
		break;
		
		case "BM_Irons_4":
			if (startHeroType == 4)
			{
				dialog.text = "Ben Tommy'yim! Tommy Irons. Sanırım. Sen kimsin? Cesur bir kadınsın, söyleyeyim, böyle dolaşıyorsun ortalıkta, hehehe.";
				link.l1 = "Gerçekten cesursun. Ve gerekirse senin çeneni kapatmaktan da çekinmem. Burası sıcak bir yer, o yüzden hafif giyiniyorum – seni ya da senin gibileri memnun etmek için değil. Adım Helen MacArthur. Arkadaşlarım bana Rumba der, ama sen kesinlikle onlardan biri değilsin. Ve o 'sanırım' lafı da neydi?";
				link.l1.go = "BM_Irons_5";
			}
			else
			{
				dialog.text = "Ben Tommy'yim! Tommy Irons. Sanırım. Ya sen?";
				link.l1 = ""+GetFullName(pchar)+".   Peki   'sanırım'   derken   tam   olarak   ne   demek   istiyorsun?";
				link.l1.go = "BM_Irons_5";
			}
			LAi_SetCurHPMax(pchar);
		break;
		
		case "BM_Irons_5":
			dialog.text = "Bu dediğim tam olarak dediğim şey. Hafızamı kaybettim – bir savaşta fena halde dayak yedim. Bazen her şeyini kaybedersin, bilirsin. Yine de şanslıyım. Sadece adımı unuttum. Neyse ki boynumda 'Thomas' yazılı bir kolye var. Ama ben Tommy demeyi tercih ederim. Ve Irons. Cromwell için Ironsides birliğinde savaştım, bunu unutma. Ama 'Ironsides' fazla uzun. Irons çok daha iyi.";
			link.l1 = "Senin derdinin ne olduğunu anlıyorum, Tommy. Söylesene - neydi mesele? Özellikle birini mi hedef aldın? Hedefini vurdun mu? Yoksa sadece eğlencesine mi ateş ettin? Hiç şaşırmam.";
			link.l1.go = "BM_Irons_6";
		break;
		
		case "BM_Irons_6":
			dialog.text = "Vurdum, hem de sağlam vurdum! Her anlamda. O süslü pantolonu hatırlıyor musun? İzimi sürdü ve yanında askerler getirdi. Sırf karısıyla yattım diye koca bir manga peşimdeydi.";
			link.l1 = "Gerçekten de yakaladın, heh. Sanırım sizi iş üstünde mi bastı?";
			link.l1.go = "BM_Irons_7";
		break;
		
		case "BM_Irons_7":
			dialog.text = "Ha! İnanmazsın – hayır. Kadın sonradan itiraf etti. Suçluluk duygusu mu, yoksa benim kadar keyif almadı mı, kim bilir, hehe. Kadınların kafasında neler döner, kim anlayabilir? Umurumda da değil, ha-ha-ha!";
			link.l1 = ""+GetSexPhrase("Hmm, tuhaf biri o.","Erkekler... Bir an kafamızda ne var anlamaya çalışıyorsunuz, sonra da umurunuzda değil diyorsunuz. Ama bir konuda haklısınız – onun yaptığı gerçekten tuhaftı. Gitmeli ve kötü bir rüya gibi unutmalıydı. Eğer bana olsaydı, ben de aynen öyle yapardım.")+"";
			link.l1.go = "BM_Irons_8";
		break;
		
		case "BM_Irons_8":
			dialog.text = "Kesinlikle! İnsanlar benimle ilgili bir tuhaflık olduğunu söylüyor. Ölen askerler için üzülüyorum. O duyguyu bilirim, ben de bir zamanlar sıradan bir askerdim. Sana söylememiş miydim?";
			link.l1 = "Evet, yaptın. Ironsides'dan. Cromwell.";
			link.l1.go = "BM_Irons_9";
		break;
		
		case "BM_Irons_9":
			dialog.text = "Gerçekten mi? Yaptım mı, yapmadım mı hatırlamıyorum. Yeni Dünya'ya nasıl geldiğimi biliyor musun? Anlatmamı ister misin?";
			link.l1 = "Hayır, ve bu beni ilgilendirmezdi, Tommy.";
			link.l1.go = "BM_Irons_10";
		break;
		
		case "BM_Irons_10":
			dialog.text = "Olurdu, olurdu. Sana anlatacağım.";
			link.l1 = "Pekala, yeter artık, ateş et. Yani, devam et.";
			link.l1.go = "BM_Irons_11";
		break;
		
		case "BM_Irons_11":
			dialog.text = "Beni o zaman bölme! Nerede kalmıştım? Ha, evet, yaralanmıştım, anlıyor musun? Kazanan tarafta olduğum için resmi olarak istifa ettim. Ama o masa başı farelerinin suratlarını görmeliydin! Sanki numara yapıyormuşum gibi baktılar, hafızamı kaybetmişim gibi davranıyormuşum sandılar. Sürekli ailem hakkında sorular sordular.";
			link.l1 = "Peki, onlara ne söyledin?";
			link.l1.go = "BM_Irons_12";
		break;
		
		case "BM_Irons_12":
			dialog.text = "Onlara ne dedim? Hafızamda bir şey olmadığını söyledim. Ve yalan söylemedim – ailemi hiç tanımadım ki. Sokaklarda, kenar mahallelerde işçiler ve hizmetkarlar arasında büyüdüm. Devrime onlar için katıldım. Ama insanların nankörlüğü gerçekten şaşırtıcı – bir kolumu ya da bacağımı kaybetmiş olsaydım, benim gibi bir kahramana hemen emeklilik vermek zorunda kalırlardı. Hem de az kalsın başımı kaybediyordum, hem de kelimenin tam anlamıyla!";
			link.l1 = "Peki, savaş kahramanı, Yeni Dünya'ya nasıl düştün?";
			link.l1.go = "BM_Irons_13";
		break;
		
		case "BM_Irons_13":
			dialog.text = "Bunda şüphen mi var? Halk için savaşmak - bunda kahramanca olmayan ne var? Umarım bir gün senin gibi korkaklar gerçek özgürlüğün ne olduğunu anlar!";
			link.l1 = "Özgürlük güzel bir şey ama sen bunu bir tehdit gibi söyledin nedense. Peki Tommy, devam et.";
			link.l1.go = "BM_Irons_14";
		break;
		
		case "BM_Irons_14":
			dialog.text = "Evet. Devrim kazanıldıktan sonra istifamı aldım, sonra da fark ettim ki başka bir şey yapamıyorum; sadece silah kullanıp insanlara yumruk atabiliyorum. Ordudan tekrar katılamazsın tabii—sana gülerler, özellikle de istifam için bu kadar uğraştıktan sonra. Heh, bana kalırsa gerçekten bir kolumu ya da bacağımı kaybetmiş olsam bile, o masa başı fareleri yine de çıkış belgemi alınca onları bir yerlerde saklayıp sonra tekrar dikmek için sakladığımı düşünürlerdi, ha-ha-ha!";
			link.l1 = "Bu komik. Ama hâlâ buraya nasıl geldiğini anlatmadın.";
			link.l1.go = "BM_Irons_15";
		break;
		
		case "BM_Irons_15":
			dialog.text = "Ah, ne kadar da sıkıcısın. Sana hiç sabretmeyi öğretmediler mi, "+GetSexPhrase("delikanlı","kızım")+"? Evde yapacak bir şeyim yoktu, sadece ördek ve geyik avlıyordum, bu yüzden Yeni Dünya'ya gittim. Bir süre eğlence olsun diye korsanlarla denize açıldım, ama o başıbozukluktan sıkılınca paralı asker oldum.";
			link.l1 = "Pek de özgün bir hikaye değil.";
			link.l1.go = "BM_Irons_16";
		break;
		
		case "BM_Irons_16":
			dialog.text = "Belki senin daha iyi bir fikrin vardır? Tesadüfen korumaya ihtiyacın yok mu? Çünkü... zayıf görünüyorsun. Endişeleniyorum, fazla ilerleyemezsin diye, hehe. Unutma, kralı kral yapan çevresidir. Kötü bir maiyet ise onu alaşağı edebilir.";
			link.l1 = "Ve ne tür bir "+GetSexPhrase("king","kraliçe")+" senin gibi bir maiyetle mi olurdum? "+GetSexPhrase("King","Kraliçe")+" gübre yığınının tepesinde mi?";
			link.l1.go = "BM_Irons_17";
		break;
		
		case "BM_Irons_17":
			dialog.text = "Hayır, hayır! Sana gerçek bir teklif yapıyorum, ve sen...";
			link.l1 = "Henüz bana bir teklif gelmedi. Hizmetlerin için ne kadar istiyorsun, Tommy?";
			link.l1.go = "BM_Irons_18";
		break;
		
		case "BM_Irons_18":
			dialog.text = "Önce 150 doblon peşin! Ciddi olduğunu ve bir sahtekâr olmadığını görmek için. Sonrasında da aylık bir ücret. Sanırım anlaşabiliriz.";
			link.l1 = "Ve sen yapmıyorsun...";
			link.l1.go = "BM_Irons_19";
		break;
		
		case "BM_Irons_19":
			dialog.text = "... cesaretin olduğunu mu sanıyorsun? Heh, seninle tartışmayacağım bile - deniz fenerindeki o alçağı nasıl indirdiğimi gördün mü? İlk atışta! Pazarlık da yok, aklından geçiriyorsan bile. Benim gibi bir profesyoneli tutabileceğini göstermen gerek.";
			if (PCharDublonsTotal() >= 150)
			{
				link.l1 = "Evet, yapabilirim! 150 altın. Buyurun.";
				link.l1.go = "BM_Irons_Hire1";
			}
			link.l2 = "O atışta şansın yaver gitti. Şimdi de övünerek değerini artırmaya çalışıyorsun. Senin gibi bir uzmana ihtiyacım yok. Bu kadar onur ve bu kadar para fazla.";
			link.l2.go = "BM_Irons_NoHire1";
			link.l3 = "Şu anda bunu karşılayamam, çünkü cebimde o kadar para yok. Burada kal ve hiçbir yere gitme – gemiden altını alıp döneceğim.";
			link.l3.go = "BM_Irons_Wait1";
		break;
		
		case "BM_Irons_Hire1":
			RemoveDublonsFromPCharTotal(150);
			
			dialog.text = "Beklediğim kadar kötü değilmişsin! Ama beni sıkmamaya dikkat etsen iyi olur. Yeteneklerimin boşa gitmesi yazık olurdu, değil mi? Tommy ve "+pchar.name+"! Karayipleri sarsalım!";
			link.l1 = "Emir komuta zincirine saygı duymayı öğren, Tommy. Ve ikincisi, bana kaptan diyeceksin. Anladın mı?";
			link.l1.go = "BM_Irons_Hire2";
		break;
		
		case "BM_Irons_Hire2":
			dialog.text = "Heh, biliyorum, Kaptan Sıkıcı, "+GetSexPhrase("beyefendi","özlemek")+".";
			link.l1 = "Ah, bundan şimdiden pişman olmaya başladım...";
			link.l1.go = "Irons_hire";
		break;
		
		case "Irons_Hire":
			DialogExit();
			AddDialogExitQuestFunction("BM_Irons_Hire");
			
			if (CheckAttribute(pchar, "questTemp.BM_hireInGrot"))
			{
				AddQuestRecord("BlackMark", "4");
			}
			else
			{
				AddQuestRecord("BlackMark", "1");
			}
		break;
		
		case "BM_Irons_NoHire1":
			dialog.text = "Pekala, sen bir aptalsın, genç "+GetSexPhrase("adam","kadın")+"! Ve tamamen sağduyudan yoksunsun. Bunu düzeltmeni tavsiye ederim, yoksa burada fazla dayanamazsın. Özellikle de Takımadalar'da.";
			link.l1 = "Sensiz de idare ederim, Tommy. Hoşça kal.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsGoodbye");
		break;
		
		case "BM_Irons_Wait1":
			dialog.text = "Ciddi misin? Bir grup asker burada az önce öldü, dahi! Muhtemelen yakında başka bir birlik gönderecekler. Hayır, fenerin kapısını kilitleyip savunma hazırlayabilirim, ama ister miyim? Hiç sanmıyorum.";
			link.l1 = "Peki, ne öneriyorsun?";
			link.l1.go = "BM_Irons_Wait2";
		break;
		
		case "BM_Irons_Wait2":
			dialog.text = "Ormanda bir mağarada buluşalım. Hizmetlerimin bedelini ödeyebilmen için sana birkaç gün veriyorum – kılıç kullanmayı biliyorsun, belki de başarabilirsin.";
			link.l1 = "Ciddi misin? Orada köşeye sıkışmış bir fare gibi olacaksın.";
			link.l1.go = "BM_Irons_Wait3";
		break;
		
		case "BM_Irons_Wait3":
			dialog.text = "Sadece özellikle beni ararlarsa, hem de büyük bir birlikle. O yüzden sanırım sorun olmayacak. Şimdi gitmeliyim - yakında burada olurlar. Sonra görüşürüz.";
			link.l1 = "Evet, ben de gitmeliyim, ne olur ne olmaz.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsToCave");
		break;
		
		case "BM_Irons_WaitInCave1":
			dialog.text = "Ha, işte buradasın! Artık para kazanamayacağını düşünmeye başlamıştım. Bazen senin gibi insanların bu yetenekle doğduğunu düşünüyorum. Eğer doğmamışlarsa, dürüst insanlar gibi bir gün bile çalışmadan yoksulluk içinde ölürler.";
			link.l1 = "Pekâlâ, Tommy. Mürettebatıma katılmak istemiyorsan, katılma. Görüyorum ki bu delikte yuva kurmaktan hoşlanıyorsun.";
			link.l1.go = "BM_Irons_WaitInCave2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Irons_WaitInCave2":
			dialog.text = "Belli ki İrlanda'da yağmurlu sezonda çukurlarda saklanmamışsın, "+GetSexPhrase("delikanlı","benim kızım")+"! Ama seninle gitmek burada saklanmaktan daha iyi. Şimdi, o altın meselesine gelelim...";
			if (PCharDublonsTotal() >= 150)
			{
				link.l1 = "Al altınların burada.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Henüz almadım. Başka bir yere gidip gitmediğini kontrol etmek istedim.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_Irons_HireInCave1":
			RemoveDublonsFromPCharTotal(150);
			pchar.quest.BM_IronsTimeOver.over = "yes";
			pchar.questTemp.BM_hireInGrot = true;
			
			dialog.text = "İşte şimdi konuşuyoruz! Peki, sırada ne var... Kaptan?";
			link.l1 = "Öncelikle, hadi şu nemli yerden çıkalım yoksa hapşırmaya başlayacağım.";
			link.l1.go = "BM_Irons_HireInCave2";
		break;
		
		case "BM_Irons_HireInCave2":
			dialog.text = "Ah, savaş görmelisin. Ben böyle yerlerde kendimi neredeyse evimde hissediyorum.";
			link.l1 = "Anladım, demek istifanı aldın ve saygıyı, hiyerarşiyi unuttun ha, Tommy? Merak etme, gerekirse sana bir ders daha vermekten çekinmem. Şimdi, hadi gidelim.";
			link.l1.go = "Irons_hire";
		break;
		
		case "BM_Irons_NoHireInCave1":
			NextDiag.TempNode = "BM_Irons_WaitInCave3";
			
			dialog.text = "Heh, Tommy Irons asla kaçmaz! O sözünde durur. Sen de kendi sözünü tutacak mısın?";
			link.l1 = "Üzerinde çalışıyorum.";
			link.l1.go = "Exit";
		break;
		
		case "BM_Irons_WaitInCave3":
			dialog.text = "Altını getirdin mi?";
			if (PCharDublonsTotal() >= 150)
			{
				link.l1 = "Altınların burada.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Henüz almadım. Başka bir yere gidip gitmediğini kontrol etmek istedim.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_IronsJungleUhodit":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsJungleUhodit");
		break;
		
		case "BM_IronsFirstJungle_1":
			dialog.text = "Dinle, Kaptan...";
			link.l1 = "Ne oldu, Tommy?";
			link.l1.go = "BM_IronsFirstJungle_2";
		break;
		
		case "BM_IronsFirstJungle_2":
			dialog.text = "Yanınızda fazladan bir fişek olur mu? Sadece bir mermi değil, düzgünce kağıda sarılmış bir kartuş lazım.";
			link.l1 = "Bu da senin şakalarından biri mi? Sana düzenli olarak mermi ve fişek veriyorum, neye ihtiyacın varsa. Peki neden tam olarak bir fişek istiyorsun, bir avuç değil de?";
			link.l1.go = "BM_IronsFirstJungle_3";
		break;
		
		case "BM_IronsFirstJungle_3":
			dialog.text = "Neden isteğimi bu kadar kötü karşılıyorsun? İstediğim kanlı inciler değil, sadece bir fişek. Hatta seni işinden alıkoymamak ya da deli gibi önüne çıkmamak için doğru anı bile bekledim, hehe. Ee... bir mermin var mı?";
			if (CheckCharacterItem(PChar, "cartridge") || CheckCharacterItem(PChar, "bullet"))
			{
				link.l1 = "Evet, bir tur aldım. Al bakalım. Ama o mermiyle bana aptalca bir şaka yapmaya kalkma. Anladın mı, Tommy?";
				link.l1.go = "BM_IronsFirstJungle_7";
			}
			link.l2 = "Şu anda yok, hayır. Cebimde bir fişek taşıyıp da, ya Tommy isterse diye düşünmüyorum ki...?";
			link.l2.go = "BM_IronsFirstJungle_4";
		break;
		
		case "BM_IronsFirstJungle_4":
			dialog.text = "Pekala, bu iyi bir nokta ve sen de çabuk kavrıyorsun, hehe. Ama korkarım ki yollarımız burada ayrılıyor.";
			link.l1 = "Ciddi misin? Bir kurşun yüzünden mi alındın? Hadi, gemiye gidelim, oradan alırız. O kadar acilse, sana bir tane, on tane, ne lazımsa getiririm.";
			link.l1.go = "BM_IronsFirstJungle_5";
		break;
		
		case "BM_IronsFirstJungle_5":
			dialog.text = "Hayır. Sonuçta sende özel bir şey yok. İyi bir kaptan, tayfasının ihtiyacı olan her şeyi sağlayabilir. O yüzden gidiyorum.";
			link.l1 = "Peki ya denizde olsak, romumuz bitse ve sen daha fazlasını istesen? Sandalı çözüp açılır mıydın? Yoksa suya mı atlardın?";
			link.l1.go = "BM_IronsFirstJungle_6";
		break;
		
		case "BM_IronsFirstJungle_6":
			dialog.text = "Ha-ha-ha! Güldüm ama, şu hüzünlü anda iyi bir şaka bile işe yaramaz. Hoşça kal, Kaptan Sıkıcı.";
			link.l1 = "Pekâlâ, cehenneme kadar yolun var Tommy. Hoşça kal.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsFirstJungle_7":
			dialog.text = "Hiçbir şeyin garantisini veremem, heh-heh. İyi bir şaka ortamı hafifletir. Ama yine de teşekkür ederim, tabii ki.";
			link.l1 = "Pekâlâ, hadi gidelim, seni şakacı.";
			link.l1.go = "BM_IronsFirstJungle_8";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
    			TakeItemFromCharacter(PChar, "cartridge");
			}
			else if (CheckCharacterItem(PChar, "bullet"))
			{
    			TakeItemFromCharacter(PChar, "bullet");
			}
		break;
		
		case "BM_IronsFirstJungle_8":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsFirstJungle");
		break;
		
		case "BM_IronsSecondJungle_1":
			dialog.text = "Hey, Kaptan!";
			link.l1 = "Evet, Tommy?";
			link.l1.go = "BM_IronsSecondJungle_2";
		break;
		
		case "BM_IronsSecondJungle_2":
			dialog.text = "Bir tane daha kağıt kartuşun var mı?";
			link.l1 = "Sonuncusuna ne oldu? Ve o kartuşla ilgili şaka neydi? İki haftadır senden aptalca bir şaka bekliyorum, ama hâlâ tık yok.";
			link.l1.go = "BM_IronsSecondJungle_3";
		break;
		
		case "BM_IronsSecondJungle_3":
			dialog.text = "Ah, bu harika bir şaka olacak, bana güven. Bayılacaksın, hehe. Sadece henüz tamamen toparlayamadım. Peki ya kartuş ne oldu?";
			if (CheckCharacterItem(PChar, "cartridge") || CheckCharacterItem(PChar, "bullet"))
			{
				link.l1 = "Al bakalım. Umarım bu seferki şakan gerçekten hoşuma gider. Peki, son fişeği nereye koydun? Sana bundan bolca verdim. Yoksa savaş için cephaneyi bir yerde, şakalar için olanı başka yerde mi saklıyorsun?";
				link.l1.go = "BM_IronsSecondJungle_7";
			}
			link.l2 = "Senin aptal şakaların için cephane taşımıyorum, Tommy! Sadece bir fişek istemek yerine iki hafta önce bütün bir kutu isteyebilirdin!";
			link.l2.go = "BM_IronsSecondJungle_4";
		break;
		
		case "BM_IronsSecondJungle_4":
			dialog.text = "Yaptım! Kaptanım olduğunu iddia eden biri, tayfasının ihtiyaçlarını her zaman karşılar diye düşündüm.";
			link.l1 = "Ben hiçbir şeymiş gibi davranmıyorum, Tommy. Uzun zaman önce kendim olmayı seçtim. Kim benimle rahatsa, ne âlâ. Değilse, o da sorun değil.";
			link.l1.go = "BM_IronsSecondJungle_5";
		break;
		
		case "BM_IronsSecondJungle_5":
			dialog.text = "Heh, bu konuda seninle benzeriz. Ama benim kaptanım için bazı şartlarım var. Ve artık onlara uymuyorsun, delikanlı. Yollarımız burada ayrılıyor.";
			link.l1 = "Ciddi misin? Sırf elimde lanet bir kartuş yok diye mi?";
			link.l1.go = "BM_IronsSecondJungle_6";
		break;
		
		case "BM_IronsSecondJungle_6":
			dialog.text = "Bu söz konusu bile olamaz. Genelde insanlara istediklerini yapmalarını ve hayattan dilediklerini almalarını tavsiye ederim. Ama sana, bundan sonra kendi insanlarını daha çok düşünmeni öneririm. Hoşça kal.";
			link.l1 = "Ve sana kafana dikkat etmeni tavsiye ederim – düşündüğünden daha fazla zarar vermişler. Hoşça kal, Tommy.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsSecondJungle_7":
			dialog.text = "Öğreneceksin. Her şeyin zamanı var, hehe.";
			link.l1 = "Ah, içime kötü bir his doğdu Tommy...";
			link.l1.go = "BM_IronsSecondJungle_8";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
    			TakeItemFromCharacter(PChar, "cartridge");
			}
			else if (CheckCharacterItem(PChar, "bullet"))
			{
    			TakeItemFromCharacter(PChar, "bullet");
			}
		break;
		
		case "BM_IronsSecondJungle_8":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsSecondJungle");
		break;
		
		case "BM_IronsThirdJungle_1":
			dialog.text = "Sana bir sorum var, Kaptan.";
			link.l1 = "Ne oldu Tommy, anlat bakalım?";
			link.l1.go = "BM_IronsThirdJungle_2";
		break;
		
		case "BM_IronsThirdJungle_2":
			dialog.text = "Anlayamadın mı? Tahmin etmek faydalı bir yetenektir, hehe. Sen, ben, orman... Yaklaşık iki hafta önce bu konuşmayı yapmıştık. Bir kağıt fişeğe daha ihtiyacım var.";
			if (CheckCharacterItem(PChar, "cartridge") || CheckCharacterItem(PChar, "bullet"))
			{
				link.l1 = "Bu artık neredeyse bir gelenek haline geliyor, değil mi? İki hafta oldu - Tommy yine fişek istiyor. Al bakalım. Şu şakan için daha kaç tane lazım sana?";
				link.l1.go = "BM_IronsThirdJungle_5";
			}
			link.l2 = "Daha ne kadar sürecek Tommy?! Bu iş daha ne kadar devam edecek? Siz Ironsides'lar her savaştan önce sadece bir fişek mi alırsınız?! Senin tuhaflıkların yüzünden üzerimde sürekli mermi taşımak zorunda değilim, bunu biliyorsun!";
			link.l2.go = "BM_IronsThirdJungle_3";
		break;
		
		case "BM_IronsThirdJungle_3":
			dialog.text = "Aslında, kaptanım olarak, bana savaş için gereken her şeyi ve fazlasını sağlamak senin görevin.";
			link.l1 = "Kafanı karıştırmışsın, Tommy. Senin görevin kaptanının emirlerine uymak. Size her zaman her şeyi sağlıyorum – ilaç, cephane, rom. İhtiyacın olanı zamanında almayıp sonra dilenci gibi davranman tamamen senin suçun!";
			link.l1.go = "BM_IronsThirdJungle_4";
		break;
		
		case "BM_IronsThirdJungle_4":
			dialog.text = "Çok zekisin ama burada şimdiye kadar neden kayda değer hiçbir şey başaramadın? Söyleyeyim nedenini. Çünkü önünü göremiyorsun ve hiçbir şeye hazırlıklı değilsin. Ne yaptığını bilmiyorsun, sıkıcısın. Böyle birini komutanım olarak kabul etmem, o yüzden hoşça kal.";
			link.l1 = "Ve sen hiç aklını kullanmıyorsun! Defol git, seni lanet ahmak!";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsThirdJungle_5":
			dialog.text = "Bu işimi görür, hehe.";
			link.l1 = "Sonunda her şeyi yoluna koydun, öyle mi? Ama ne için?";
			link.l1.go = "BM_IronsThirdJungle_6";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
   				TakeItemFromCharacter(PChar, "cartridge");
			}
			else if (CheckCharacterItem(PChar, "bullet"))
			{
    			TakeItemFromCharacter(PChar, "bullet");
			}
		break;
		
		case "BM_IronsThirdJungle_6":
			dialog.text = "Sana sadece bir şaka yapıyordum, eski huysuz haline dönecek misin diye bakıyordum. Hehe. Ama kartuş için sağ ol.";
			link.l1 = "Şakaların tuhaf, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_7";
		break;
		
		case "BM_IronsThirdJungle_7":
			dialog.text = "That was a joke too. I wasn't collecting them; I was selecting them. Needed a cartridge that was close to perfect. This one will do. Yeah, with this round, the bullet will go far and true. Just like when I blew old Reasley's head off, ha-ha-ha!";
			link.l1 = "Yaşlı Reasley, demiştin... Aldatılan Frankie, değil mi? Fenerde vurduğun adam? Demek birbirinizi uzun zamandır tanıyorsunuz, öyle mi?";
			link.l1.go = "BM_IronsThirdJungle_8";
		break;
		
		case "BM_IronsThirdJungle_8":
			dialog.text = "Ne? Ah, kahretsin, ağzımdan kaçırdım. Ama umurumda değil – yalan söylemekte ya da sır saklamakta hiç iyi olmadım.";
			link.l1 = "İkinci kurşunun özel birine yönelik olduğunu düşünüyorum, değil mi Tommy?";
			link.l1.go = "BM_IronsThirdJungle_9";
		break;
		
		case "BM_IronsThirdJungle_9":
			dialog.text = "Pekâlâ, dahi. Ben kendimi ve hedeflerimi biliyorum, bundan da utanmıyorum. O yüzden ne düşündüğün umurumda değil – sana her şeyi anlatacağım, neden olmasın.";
			link.l1 = "Peki, o zaman söyle bakalım. Ne peşinde olduğunu bilmekte zarar yok.";
			link.l1.go = "BM_IronsThirdJungle_10";
		break;
		
		case "BM_IronsThirdJungle_10":
			dialog.text = "Pekala, beni her zamanki gibi bölme. Benimle birlikte şirkette iki herif vardı - Francis Reasley ve Gabriel Callow. Gerçekten tam birer fare! Hatta bana istifamı vermeyen o masa başı farelerinden bile beterdiler, ki biliyorsun, o istifayı almak hiç de kolay değildi.";
			link.l1 = "Peki onlar ne yaptı? Özellikle ikincisi, Callow. Onun karısıyla da mı yattın? O da mı askerlerini peşine taktı?";
			link.l1.go = "BM_IronsThirdJungle_11";
		break;
		
		case "BM_IronsThirdJungle_11":
			dialog.text = "Ağzını kapa, olur mu? Gerçi... umurumda olmazdı, hehe. Ama hayır. O gün bize Kraliyetçiler saldırdı. Süvariler de vardı. Onlar bizden çok fazlaydı. Gabe ve Frankie korkmuş tavşanlar gibi kaçtı. Ama ben çocuklarla kaldım. Hayatta kalan tek kişi bendim. Çocukluğumun ve gençliğimin çoğunu unuttum, ama bunu asla.";
			link.l1 = "Ve sen intikam mı istiyorsun, çünkü onlar kaçtı? Herkes bir ideal uğruna savaşmaz. Herkes hayatta kalmak ister. Ya da neredeyse herkes. Biri Devrim için savaşıyor olsa bile, belki de tesadüfen katılmış ve sonra pişman olmuştur.";
			link.l1.go = "BM_IronsThirdJungle_12";
		break;
		
		case "BM_IronsThirdJungle_12":
			dialog.text = "Ha, eğer her korkağı avlasaydım, bütün dünyayı vurmak zorunda kalırdım. Korkaklar, cehenneme kadar yolları var. Ama bana ihanet ettiler. Herkese, devrime ihanet ettiğimi ve kralcıların emriyle tüm birliğimizi katlettiğimi söylediler. Sana bir konuda yalan söyledim, Kaptan.";
			link.l1 = "Ne oldu? Frankie'nin seni sadece karısıyla yaşadıkların yüzünden avladığı konusunda yalan söylediğinden başka?";
			link.l1.go = "BM_IronsThirdJungle_13";
		break;
		
		case "BM_IronsThirdJungle_13":
			dialog.text = "Hayır, hayır! Sana yalan söylemedim, sadece her şeyi anlatmadım. Arada fark var. Yalan söylediğim tek şey istifa meselesiydi. Aslında istifa falan olmadı. Bir mahkeme kuruldu. Ve şanslı Tommy - onu asmaya karar vermediler, güney kolonilerindeki taş ocaklarına gönderdiler. Barbados’a, tam olarak.";
			link.l1 = "Evet, bu bayağı şanstı. Orada kaç yıl çalıştın?";
			link.l1.go = "BM_IronsThirdJungle_14";
		break;
		
		case "BM_IronsThirdJungle_14":
			dialog.text = "Hiçbiri. Şu fareler yüzünden dünyevi mahkeme beni mahkûm etti ama yukarıdaki ilahi mahkeme beni bağışladı. Takımadalar'a adım atar atmaz havasını hissettik – gemimize korsanlar çıktı.";
			link.l1 = "Yani Barbados'un taş ocakları ve plantasyonları yerine, korsanlar tarafından köleliğe mi satıldın? Ama taş ocaklarında hiç çalışmadığını söylemiştin.";
			link.l1.go = "BM_IronsThirdJungle_15";
		break;
		
		case "BM_IronsThirdJungle_15":
			dialog.text = "Ben de aynısını söyledim – yukarıda biri beni kurtarmaya karar verdi. Ne kurtarılmaydı ama, hehe! Doğru bildin – korsanlar, zincire vurulmuş adamlara eziyet etmeyi sevenleri alt etti. Ama yine de çetin bir dövüştü, buranın güneşi kadar yakıcıydı. Ve kurtarıcılarımız da kayıplar verdi. Sonra da isteyen herkese aralarına katılmayı teklif ettiler.";
			link.l1 = "Ve onlara katıldın mı? Korsanlarla birlikte yelken açtığını söyledin.";
			link.l1.go = "BM_IronsThirdJungle_16";
		break;
		
		case "BM_IronsThirdJungle_16":
			dialog.text = "Kesinlikle! Hayatımın en güzel yıllarıydı. Jack Mills tam anlamıyla bir kaptandı – umarım bir gün sen de onun gibi olursun. Onun 'Crane' gemisinde yaklaşık iki yıl çalıştım, ta ki...";
			link.l1 = "...   kanunsuzluktan bıktığını söylemiştin ya?   Neden o yılların hayatının en güzel yılları olduğunu söylüyorsun?";
			link.l1.go = "BM_IronsThirdJungle_17";
		break;
		
		case "BM_IronsThirdJungle_17":
			dialog.text = "Eh... ta ki o iki hainin de Takımadalar'a düştüğünü duyana kadar. Evet, biliyorum, sana açık deniz korsanlığından ve tüm o işlerden bıktığımı söylemiştim. Ve sana ne düşündüğün umurumda değil demiştim zaten. Hâlâ öyle, ama ilk tanıştığımızda seni pek tanımıyordum. Nasıl tepki vereceğini bilmiyordum. O yüzden farklı şeyler söyledim.";
			link.l1 = "Yalancısın Tommy! Peki, neden 'Crane'den ayrıldın?";
			link.l1.go = "BM_IronsThirdJungle_18";
		break;
		
		case "BM_IronsThirdJungle_18":
			dialog.text = "Jack gerçek bir liderdi; bir adam için rotasını değiştirmeyeceğini, onu beklemeyeceğini, intikam peşine düşmeyeceğini ya da dolgun ticaret gemilerine saldırmak yerine İngiliz Donanması'nın önde gelen subaylarıyla uğraşmayacağını söyledi.";
			link.l1 = "Önemli subaylar mı? Frank sanırım sivildi.";
			link.l1.go = "BM_IronsThirdJungle_19";
		break;
		
		case "BM_IronsThirdJungle_19":
			dialog.text = "Eh, o her zaman öyle biri değildi. Hep biraz, bilirsin, karanlık tipti. Birine tuzak kurmaya kalkınca rezil olup kovuldu. Bir tüccarın gemisinde çalışmayı denedi, ama dürüst iş ona göre değildi. Sonunda buraya yerleşti.";
			link.l1 = "Hâlâ ona seçkin bir subay diyemezdim.";
			link.l1.go = "BM_IronsThirdJungle_20";
		break;
		
		case "BM_IronsThirdJungle_20":
			dialog.text = "Gabe'i unutma. Memlekette teğmen oldu. Burada, Port Royal'da ise 'Principio' gemisinin kaptanı olarak tayinini aldı.";
			link.l1 = "Pek İngilizceye benzemiyor.";
			link.l1.go = "BM_IronsThirdJungle_21";
		break;
		
		case "BM_IronsThirdJungle_21":
			dialog.text = "Doğru söyledin! Gemi liman yosması gibi elden ele geçti, neler görmedi ki. Ama hâlâ denize dayanıklı. Bir de Gabe var, kahretsin, usta bir kaptandır.";
			link.l1 = "Ve Jack onunla başa çıkmaktan korktu mu? Gerçekten dediğin kadar iyi mi?";
			link.l1.go = "BM_IronsThirdJungle_22";
		break;
		
		case "BM_IronsThirdJungle_22":
			dialog.text = "Pekala, pekala! Aslında benim için zaman harcamak istemedi. Jack'ten bahsetmişken, ondan ilk kez gördüğüm birkaç geleneği beğenmiştim – tahta yürütme ve kara işaret dağıtma. O zamanlar bu bana komik bir fikir vermişti.";
			link.l1 = "Siyah... işaretler mi? Siyah nokta demek istiyorsun, değil mi? Peki neydi bu, Tommy? Ona siyah bir nokta versen ne yapacağını bileceğini sanmıyorum. Gerçekten öyle mi oldu? Sen ona vermek istedin, o da seni görür görmez saldırdı, sen de deniz fenerine koştun, o ise yanında bir grup asker götürüp onlara senin korsan olduğunu mu söyledi?";
			link.l1.go = "BM_IronsThirdJungle_23";
		break;
		
		case "BM_IronsThirdJungle_23":
			dialog.text = "Buna kara leke demeyi tercih ediyorum. Kulağa daha hoş geliyor. Basit bir kara leke ona hiçbir şey anlatmazdı. Ama şirketimizin ayırt edici özelliği olan ipek mendilimizden yapılmış bir kara leke – işte onu anlardı. Mendili gizlice cebine bıraktım. Sonra da fenere doğru gittiğimi görmesini sağladım. Gerisini biliyorsun.";
			link.l1 = "Ve kaçakçılar?";
			link.l1.go = "BM_IronsThirdJungle_24";
		break;
		
		case "BM_IronsThirdJungle_24":
			dialog.text = "Yanlış yerde, yanlış zamanda. Onlara az da olsa acıdım. Ama sadece biraz, hehe.";
			link.l1 = "Ya Frankie için?";
			link.l1.go = "BM_IronsThirdJungle_25";
		break;
		
		case "BM_IronsThirdJungle_25":
			dialog.text = "Şimdi kimin umurunda? Daha büyük dertlerimiz var. Geriye Gabe kaldı. O biraz zor olacak. Şimdi şunu yapmamız lazım...";
			link.l1 = "Biz mi?";
			link.l1.go = "BM_IronsThirdJungle_26";
		break;
		
		case "BM_IronsThirdJungle_26":
			dialog.text = "İlginç bir hikaye dinlemek başka, kendi hikayeni yazmak bambaşka! Planımız şöyle: Gabe’e bir özel siyah işaret daha bırakmamız gerekiyor – ben bir tane hazırladım bile. Sonra izini Portland Cove’a kadar süreceğiz ve orada ondan iz bırakmadan kurtulacağız.";
			link.l1 = "Peki, bunu nereye dikeceğiz?";
			link.l1.go = "BM_IronsThirdJungle_27";
		break;
		
		case "BM_IronsThirdJungle_27":
			dialog.text = "Ha ha ha, işte tam da bunu demek istemiştim, Keşke Jack gibi olsaydın, Kaptan. Hadi ama, sıkıcı olma, gözlerinin nasıl parladığını görüyorum!";
			link.l1 = "Aslında, hikayeni oldukça merak ettim.";
			link.l1.go = "BM_IronsThirdJungle_28";
		break;
		
		case "BM_IronsThirdJungle_28":
			dialog.text = "Tabii ki evinde! Ne biçim soru bu? Port Royal'de yerleşmiş. Yani seninle birlikte koya yanaşacağız, işler ters giderse adadan çıkabilelim diye.";
			link.l1 = "Evini nerede bulabilirim?";
			link.l1.go = "BM_IronsThirdJungle_29";
		break;
		
		case "BM_IronsThirdJungle_29":
			dialog.text = "Hayır.   Ama öğrenmek zor değil.   Sarhoşlara sorarız – onlara bir iki içki ısmarlasan annelerini bile satarlar.   Peki, planım hakkında ne düşünüyorsun?";
			if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) > 24 && GetSummonSkillFromName(pchar, SKILL_GRAPPLING) > 24 && GetSummonSkillFromName(pchar, SKILL_SAILING) > 24)
			{
				link.l1 = "Eğer Jamaika'ya giden bir geminin kaptanıysa, sürekli adanın sularında devriye geziyor demektir. Şehirde bir şey denemektense, sahte bayrak altında saldırmak daha iyidir.";
				link.l1.go = "BM_IronsThirdJungle_Sea1";	// Морской вариант
				notification("Skill Check Passed", SKILL_SAILING);
				notification("Skill Check Passed", SKILL_ACCURACY);
				notification("Skill Check Passed", SKILL_GRAPPLING);
			}
			else
			{
				if (GetSummonSkillFromName(pchar, SKILL_SAILING) < 25) notification("Skill Check Failed (25)", SKILL_SAILING);
				if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) < 25) notification("Skill Check Failed (25)", SKILL_ACCURACY);
				if (GetSummonSkillFromName(pchar, SKILL_GRAPPLING) < 25) notification("Skill Check Failed (25)", SKILL_GRAPPLING);
			}
			link.l2 = "Kusursuz değil, pek çok şeyi şansa bırakıyorsun. Ama genel olarak, yapılabilir. Ben seninleyim, Tommy. Birinden kurtuldun, diğerini bırakamazsın, değil mi?";
			link.l2.go = "BM_IronsThirdJungle_Land1";	// Сухопутный вариант
			link.l3 = "İntikamına karışmam ya da bu kadar çok şeyin şansa bağlı olduğu bu macera için İngiltere ile ilişkimi riske atmam, Tommy.";
			link.l3.go = "BM_IronsThirdJungle_Otkaz1";	// Отказ
		break;
		
		case "BM_IronsThirdJungle_Sea1":
			dialog.text = "Sen cesur birisin, Kaptan! Sana ısınmaya başladım. Ama eski 'Principio'daki Gabe kolay lokma değildir – o, böyle bir gemideki diğer kaptanlardan çok daha tehlikelidir.";
			link.l1 = "Beni ne sanıyorsun, korkak mı Tommy? Onu kendimiz ele geçireceğiz, sen de onunla baş başa konuşabilirsin. Tahttan indirilmeden hemen önce ona kara lekeyi verirsin.";
			link.l1.go = "BM_IronsThirdJungle_Sea2";
		break;
		
		case "BM_IronsThirdJungle_Sea2":
			dialog.text = "Heh, belki sen korkak değilsin ama o kesinlikle öyle, gerçi akıllı biridir. Asla bir askere ya da kendisinden büyük bir gemisi olan bir korsana saldırmaz. Ufukta böyle birini görürse, hemen kalenin gölgesine saklanır.";
			link.l1 = "Hmm, peki ya ticaret gemileri?";
			link.l1.go = "BM_IronsThirdJungle_Sea3";
		break;
		
		case "BM_IronsThirdJungle_Sea3":
			dialog.text = "Evet, bu işe yarayabilir! Ama tekrar söylüyorum, barque ya da barquentine'den daha büyük bir şey olmasın! Gabe sadece korkak değil – tedbiri elden bırakacak kadar açgözlü de olmadı hiçbir zaman.";
			link.l1 = "Umarım işe yarar, Tommy. Yani, İspanyol ya da Hollanda bayrağı taşıyan beşinci sınıf bir barque ya da barquentine. Eski savaş arkadaşınla buluşmaya hazır ol!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SeaVariant");
		break;
		
		case "BM_IronsThirdJungle_Land1":
			dialog.text = "Sana güvenebileceğimi biliyordum! Belki bir gün Jack’ten bile daha iyi bir kaptan olursun. Şansa gelince... Beni buraya kadar getirdi, yine ona güveneceğim. O halde, gidelim mi?";
			link.l1 = "Evet, bunu fazla uzatmayalım. Ne kadar çabuk biterse, o kadar iyi.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_LandVariant");
		break;
		
		case "BM_IronsThirdJungle_Otkaz1":
			dialog.text = "Heh, başka türlü olmasını ummuştum ama bunu bekliyordum - böyle işlere cesaretin yok, "+GetSexPhrase("delikanlı","kızım")+". Gerçek bir kaptanın başından en az birkaç kez böyle şeyler geçmiştir; lağım fareleriyle gizlice hesaplaşmak zorunda kalmıştır. Bazen de kendi fareleriyle.";
			link.l1 = "Sanırım bu kışkırtmaya kapılıp fikrimi değiştirdiğimi ve gerçek bir kaptan olduğumu kanıtlayacağımı söylememi bekliyorsun, değil mi Tommy? Ama intikam arzusunu anlıyorum. Seni Jack'in yaptığı gibi tayfadan ayrılmaya zorlamayacağım. Bunun için ne kadar zamana ihtiyacın var? O zamana kadar Jamaika'ya varmış olurum.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz2";
		break;
		
		case "BM_IronsThirdJungle_Otkaz2":
			dialog.text = "Ha ha ha, büyüyorsun. Buna kanmadığın için sana neredeyse saygı duyacağım. Ama bekleyip beni sonra almak zorunda değilsin - bunu kendim halledeceğim. Sonuçta, tek istediğim kaptanım olarak benim için bir şeyler yapmaya istekli biriydi. O halde hoşça kal. İngiltere'ye iyi bak, ha-ha.";
			link.l1 = "Gerçekten tuhafsın. Ama nasıl istersen. Hoşça kal! Ve intikamında bol şans, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz3";
		break;
		
		case "BM_IronsThirdJungle_Otkaz3":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsThirdJungle_Otkaz");
		break;
		
		case "BM_IronsJamaicaShore1":
			dialog.text = "Harika, gerekirse buradan hızlıca çekilebiliriz. Al bunu – Gabe’in nerede yaşadığını ve ne zaman evde olduğunu öğrendiğinde ona bu notu ve kara işareti ver.";
			link.l1 = "Ha, şimdi komutayı sen mi ele aldın Tommy. Ama unutma, hâlâ senin kaptanınım. Ben şehirdeyken ne yapmayı düşünüyorsun?";
			link.l1.go = "BM_IronsJamaicaShore2";
		break;
		
		case "BM_IronsJamaicaShore2":
			dialog.text = "Heh, bunu nasıl unuturum, Kaptan Sıkıcı? Gabe beni sokakta görürse ya alarmı verir ya da o lanet korkak adadan kaçar. Merak etme, tam burada pusu kuracağım, hehehe.";
			link.l1 = "Pusu diyorsun ha. Peki Tommy. Eski savaş arkadaşına layık bir buluşma yapalım, ha ha ha ha!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsJamaicaGo");
		break;
		
		case "BM_Pyanitsa_0":
			dialog.text = "Hık! Bu müthiş bir rom! Hık... Şerefe!";
				link.l1 = "Dinle dostum, buralarda Kaptan Gabriel Callow hakkında ne konuşuluyor?";
			link.l1.go = "BM_Pyanitsa_1";
			DelLandQuestMark(npchar);	//Удаляем квестмарку
		break;
		
		case "BM_Pyanitsa_1":
			dialog.text = "Yaşlı Gabe mi?! Hep iyi şeyler! Şey, hık, ne oldu?";
			link.l1 = "Gerçekten mi? Bunu duyduğuma sevindim. Şey, bir korsanla başımız dertte. Komutan genellikle kara işlerine bakar, ben de Ekselanslarını rahatsız etmek istemem.";
			link.l1.go = "BM_Pyanitsa_2";
		break;
		
		case "BM_Pyanitsa_2":
			dialog.text = "O zaman hemen Gabe'e git, diyorum sana! Şehirde Gabe'den daha dürüst ya da cesur bir kaptan yok. Albay Doyley bile ona büyük saygı duyar. Bir zamanlar bizzat Nicolas Sharp'a ait olan bir gemiyi yönetiyor, inanabiliyor musun?";
			link.l1 = " Henüz buna inanacak kadar sarhoş değilim, dostum.";
			link.l1.go = "BM_Pyanitsa_3";
		break;
		
		case "BM_Pyanitsa_3":
			dialog.text = "E-Evet, ama sensin! Bu Principio! Bir şey çağrıştırıyor mu, ha?";
			link.l1 = "Bir İspanyol ödül gemisi, öyle mi? Neden?";
			link.l1.go = "BM_Pyanitsa_4";
		break;
		
		case "BM_Pyanitsa_4":
			dialog.text = "En son ne zaman kendi gözlerinle pembe bir tane gördün, ha? Ne dediğimi biliyorum, cık!";
			link.l1 = "Pekala, geminin tasarımı o kadar da sıradışı mı, emin değilim.";
			link.l1.go = "BM_Pyanitsa_5";
		break;
		
		case "BM_Pyanitsa_5":
			dialog.text = "Ama gerçekten öyle! Şimdi kimse böyle hurda bir gemiye komuta etmez, etrafta bu kadar yeni tasarım varken! Tersanelerde bu tipleri yapmayı neredeyse otuz yıl önce bıraktılar! Nic onu bizzat kullanmış, söylüyorum sana.";
			link.l1 = "Pekâlâ, alıyorum. Yani, o gemi bu mu? Bu harabe nasıl hâlâ dağılmamış?";
			link.l1.go = "BM_Pyanitsa_6";
		break;
		
		case "BM_Pyanitsa_6":
			if (sti(pchar.basenation) == ENGLAND) sStr = "our";
			else sStr = "your";
			dialog.text = "Eh, en parlak zamanlarındaki kadar hızlı değil artık – tıpkı benim bir kadeh daha içtikten sonraki halim gibi, ha-ha-ha! Ama iyi bir kaptan bu yaşlı hanımdan hâlâ bir şeyler çıkarabilir. Gabe de onu ateş hattına sokmamaya çalışıyor zaten.";
			link.l1 = "Peki neden geminin adı değiştirilmedi? Belki de Majestelerinin Gemisi Thrashing, mesela, altında "+sStr+" eski düzen mi?";
			link.l1.go = "BM_Pyanitsa_7";
		break;
		
		case "BM_Pyanitsa_7":
			dialog.text = "Gelenek... Ge-ge-gelenek, ah! Nic, Küba'daki bir İspanyol plantasyonundan kaçtıktan sonra gemisinin adını hiç değiştirmedi. O yaşadıklarını asla unutmak istemedi - İspanyollar da öyle! Sana söyleyeyim, Tendales kıyısındaki o çarpışma...";
			if (startHeroType == 4)
			{
				link.l1 = "Tendales, değil mi? Hıh, bu ismi en son çocukken duymuştum. Şimdi terk edilmiş o kayaları hâlâ bilen ya da hatırlayan birinin kaldığını sanmazdım.";
				link.l1.go = "BM_Pyanitsa_8";
			}
			else
			{
				link.l1 = "Tendales mi? Orası neresi?";
				link.l1.go = "BM_Pyanitsa_8";
			}
		break;
		
		case "BM_Pyanitsa_8":
			dialog.text = "Yoksa, şey, Highrock muydu? H-hayır, kesinlikle orası değildi... Neyse, önemli değil! Nic o pembe gemide savaşıp kazandı, Desmond Ray Beltrop, Korsan Baronu'nun peşine taktığı Cuttlefish adlı brigantine karşısında inanılmaz bir zafer elde etti. Uzun süre birbirlerinin kanını döktüler, ta ki Nic bizzat Desmond'u yere serene kadar.";
			if (startHeroType == 4)
			{
				link.l1 = "Vay canına, bu gerçekten etkileyici! Gerçi Nicholas'tan başka türlü bir şey beklenmezdi. Eh, Sharps ve Beltrops hep birlikte, sonra ayrı – demek ki tarih bazen gerçekten tekerrür ediyor.";
				link.l1.go = "BM_Pyanitsa_9";
			}
			else
			{
				link.l1 = "Etkileyici. Peki, Sharp gemiden nasıl ayrıldı? Onu tersanede mi sattı?";
				link.l1.go = "BM_Pyanitsa_9";
			}
		break;
		
		case "BM_Pyanitsa_9":
			dialog.text = "Yok. O çatışmadan sonra su almaya başladı, Nic de onu terk etti. Sonra büyük gelgitle birlikte, pembe olan kıyıya vurdu, tam kasabanın yanına.";
			link.l1 = "Sanki o harabeyle ilgilenen biri varmış gibi.";
			link.l1.go = "BM_Pyanitsa_10";
		break;
		
		case "BM_Pyanitsa_10":
			dialog.text = "Ah, ama Donanma ilgilendi! Pratik adamlardır. İngiliz bayrağı altında ama İspanyol ismiyle bir gemi görünce meraklandılar. Nic birkaç yıl sonra öldü, ama gemisi yoluna devam etti, el değiştirdi, her seferinde kanlı bir şekilde.";
			link.l1 = "Bu sadece başka bir hayalet gemi hikayesi, oysa Gabe'in kaptanlığı gayet gerçek. O yüzden, sanırım gidip onunla konuşacağım. Nerede yaşadığını biliyor musun?";
			link.l1.go = "BM_Pyanitsa_11";
		break;
		
		case "BM_Pyanitsa_11":
			dialog.text = "Ha-ha! Tabii ki, hık, biliyorum! Herkes bilir! Yaşlı Gabe eski yel değirmeninin yanında yaşar. Mehanenin etrafından dolaşıp yukarı bak... hık!";
			link.l1 = "Ne zaman evde olur? Anlaşılan meşgul bir adama benziyor.";
			link.l1.go = "BM_Pyanitsa_12";
		break;
		
		case "BM_Pyanitsa_12":
			dialog.text = "Doğru söylüyorsun dostum! Yapacak çok işi var. Eve ancak akşamları, saat ondan sonra geliyor. Ve her sabah tam altıda, kendi kendine kalkıyor. Demir gibi bir disiplin!";
			link.l1 = "Çok teşekkür ederim! Şimdilik bu korsan hikayelerinden bıktım artık.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SearchGabeHouse");
		break;
		
		case "BM_Callow1":
			if (startHeroType == 4) 
			{
				dialog.text = "Gerçekten... Rumba mısın? Adını duydum... ama kendi insanlarına hiç sırtını dönmemiştin!";
				link.l1 = "Ve etmedim de. Benim meselem ülkemle değil. Seninle, Gabe.";
				link.l1.go = "BM_Callow_Helena1";
			}
			else
			{
				dialog.text = "Sen bir tüccar değilsin...";
				link.l1 = "Sürpriz, Gabe! Duyduğuma göre tedbirli, hatta korkak biriymişsin. Açgözlülük aklını bulandırmış, değil mi? Hiçbir tüccar, benim yaptığım gibi güverteye çıkmayı istemezdi.";
				link.l1.go = "BM_Callow2";
			}
		break;
		
		case "BM_Callow_Helena1":
			dialog.text = "Benimle mi? Sorun ne? Benim yerimde ya da senin yerinde, güzelce konuşabilirdik. Kaptanlar gibi, ve... SEN burada ne yapıyorsun?!";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_Callow2":
			dialog.text = "Gerçekten öyle. Peki, sen kimsin? Yok, boşver seni. O kim...";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_IronsClone1":
			dialog.text = "Thomas, bu sen misin...?";
			link.l1 = "Ah evet, Gabe. Ve o gün bana yaptıklarının cezasını vermeye geldim.";
			link.l1.go = "BM_IronsClone2";
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			CharacterTurnByChr(sld, CharacterFromID("IronsClone"));
			sld = CharacterFromID("IronsClone");
			CharacterTurnByChr(sld, &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]);
		break;
		
		case "BM_IronsClone2":
			dialog.text = "Beni mi cezalandıracaksın?! Dikkatli konuş, Thomas! Aramızda cezayı hak eden biri varsa, o sensin! Takviye getireceğini söyledin! Biz de bekledik, Kral'ın süvarilerinin kurşunları ve kılıçları altında can verdik!";
			link.l1 = "Yardım getirmek için can havliyle koştum! Ama başka bir lanet kuvvet tarafından yakalandım! Charles'ın kahrolası destekçileri her yerdeydi! Beni köşeye sıkıştırdılar, neredeyse ölüyordum! Neyse ki öldüğümü sandılar. Ama ne gördüğümü biliyor musun, Gabe?!";
			link.l1.go = "BM_IronsClone3";
		break;
		
		case "BM_IronsClone3":
			dialog.text = "Ne oldu Tom? Bu adamın sana inanmasını sağlamak için aklına gelen her hikayeyi uydurmaya hazır mısın?!";
			link.l1 = "Heh, o adam beni zaten satmaz. Bazı insanlar gibi hain değildir.";
			link.l1.go = "BM_IronsClone4";
		break;
		
		case "BM_IronsClone4":
			dialog.text = "Başka seçeneği yok! İngiliz Donanması'nın bir gemisine saldırmak!";
			link.l1 = "Ah, başından beri bir seçeneği vardı. Ve bana yardım etmeyi seçti. Senin ve Frankie'nin de bir seçeneği vardı. Ölmemek için kaçmayı seçtiniz. Sonra geri geldiniz ve beni yarı ölü buldunuz. Ve mahkemede o iğrenç yalanlarınızı söylediniz. Kafama darbe aldığım ve hafızamı kaybettiğim için kimsenin bana inanmayacağını biliyordunuz!";
			link.l1.go = "BM_IronsClone5";
		break;
		
		case "BM_IronsClone5":
			dialog.text = "Sana zaten kimse kulak asmazdı. Sen her zaman bir... harabeydin, Thomas.";
			link.l1 = "Demek o gün yaptıklarını saklamıyorsun. Sana bir şeyim var, Gabe. Kara bir işaret. Ama şimdi gemi ele geçirildi ve bağırsaklarını deşmek üzereyken sana bunu vermenin ne anlamı var, hee hee hee hee hee hee...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("BM_IronsClone5_function"); // здесь переход на кейс с боёвкой
		break;
		
		case "BM_IronsClone8":
			dialog.text = "Eh, Gabe tahttan indirildi, hehe. Bunu uzun zamandır söylemek istiyordum. Yazık ki artık duyamıyorsun, dostum. Ama dur! Belki duyarsın - Cehennem’den.";
			link.l1 = "Hadi ama Tommy. Duymamış olsa bile, gördü ve bunun tam olarak senin oyunun ve intikamın olduğunu anladı. Ve bununla ilgili hiçbir şey yapamadı.";
			link.l1.go = "BM_IronsClone9";
		break;
		
		case "BM_IronsClone9":
			if (startHeroType == 4) 
			{
				dialog.text = "Heh, haklısın! Hem de nasıl! Bu işte bana yardım ettiğin için sağ ol. Biliyor musun, seni sadece süslü kıyafetler içinde şımarık bir kız sanmıştım, keyfine gemi sürenlerden. Ama sen gerçekten iyi bir kaptansın! Bahse girerim Jack’i bile zor durumda bırakırsın.";
			}
			else
			{
				dialog.text = "Heh, haklısın! Hem de fazlasıyla! Bu işte bana yardım ettiğin için sağ ol. Biliyor musun, bence sen de Jack kadar iyi bir kaptansın. Hatta belki ondan da iyisin!";
			}
			link.l1 = "Ah, şimdi bana iltifat ediyorsun. Teşekkür ederim. Sanırım.";
			link.l1.go = "BM_IronsClone10";
		break;
		
		case "BM_IronsClone10":
			dialog.text = "Hiç de öyle değil. Hiçbir şekilde yağcılık yapmıyorum. Fark ettiysen, ben çok nadiren birini böyle överim. O yüzden çeneni kapa ve senin hakkında böyle düşündüğüm için mutlu ol";
			link.l1 = "Söylediklerini beğendiğimi söyleyemem, ama beni genel olarak iyi bir kaptan olarak görmene sevindim. Ama... komuta zinciri, Tommy, komuta zinciri.";
			link.l1.go = "BM_IronsClone11";
		break;
		
		case "BM_IronsClone11":
			if (startHeroType == 4) 
			{
				dialog.text = "Ah, hadi ama! Bunca yaşadığımız şey bizi birbirimize daha da yakınlaştırdı, Ellie. Sadece kaptan ve subay olmaktan fazlası olabiliriz. Kabul et - sadece kendine bile olsa, sen de hissediyorsun bunu.";
				link.l1 = "Sadece hayallerinde görebilirsin, Tommy. Ve adım Helen, Ellie değil. Ama sanırım artık bana Rumba diyebilirsin.";
				link.l1.go = "BM_IronsClone12";
			}
			else
			{
				dialog.text = "Ah, hadi ama, ne sıkıcısın! Artık sadece bir kaptan ve subayı değil, en gerçek dostlar olduğumuzu düşünüyorum. Sence de öyle değil mi?!";
				link.l1 = "Heh. Belki de. Senin dostun olmak, düşmanın olmaktan iyidir. Ve görgü kuralları pek umurunda olmadığına göre, sanırım buna alışmam gerekecek.";
				link.l1.go = "BM_IronsClone12";
			}
		break;
		
		case "BM_IronsClone12":
			dialog.text = "Sana bir... hediyem var, Kaptan.";
			link.l1 = "Vay canına, şuna bak! Kara işaret mi? Beni de devirmek mi istiyorsun, ha Tommy? Kaptan olmak istiyorsun yani? Ha-ha-ha-ha! Hani biz dosttuk diyordun.";
			link.l1.go = "BM_IronsClone13";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_IronsClone13":
			dialog.text = "Bu bir kara İŞARET, seni gerizekalı. Biliyor musun, bu atkıya kafatası ve kemikleri işlediğim anda bana şans getirmeye başladığını düşünüyorum. Açıklayamıyorum. Al bunu. Ayrıca... istersen, her zaman güvenilir kılıcımı ve zırhımı ödünç alabilirsin... geriye ne kaldıysa, ha-ha! İşine yarar! Çok yol kat edeceksin. Ve ben de buna tanık olmak istiyorum. Rastgele bir kurşunla ölmeni istemem.";
			link.l1 = "Sağ ol dostum! Elimden gelenin en iyisini yapacağım. Sen de izle ve hayran kal, ha-ha-ha!";
			link.l1.go = "BM_IronsClone14";
		break;
		
		case "BM_IronsClone14":
			dialog.text = "Hayran ol, tabii, ha-ha-ha. Evet. Peki, bu gemiyle ne yapmaya karar verdin? Bir yandan, artık pek bir işe yaramıyor. Öte yandan, bunun gibisi de kalmadı. Sanmıyorum ki bir daha böyle bir gemi olsun.";
			if (startHeroType == 4) 
			{
				link.l1 = "Henüz karar vermedim... Biliyor musun Tommy, bu gemiye karşı bir bağ hissediyorum. Açıklayamam. Önce şu pis cesedi buradan çıkaralım. Ambarında sızıntı yoksa, muhtemelen bu güzeli kendime alırım.";
			}
			else
			{
				link.l1 = "   Bilmiyorum, Tommy. Henüz karar vermedim. Bu arada, Gabe’in cesedinden kurtulalım. Gemiyi elimizde tutmaya karar verirsek diye, ne olur ne olmaz.";
			}
			link.l1.go = "BM_IronsClone15";
		break;
		
		case "BM_IronsClone15":
			DialogExit();
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		case "BM_IronsPinkPotopil1":
			dialog.text = "Vallahi, o eski gemiyle harika bir iş çıkardın, Kaptan! Gabe'i kendi ellerimle bitirmek isterdim ama bu zaferi küçümseyerek Yaradan'ı kızdırmak istemem.";
			link.l1 = "Bu gereksiz olurdu, Tommy. Umarım ruhun şimdi huzur bulmuştur.";
			link.l1.go = "BM_IronsPinkPotopil2";
		break;
		
		case "BM_IronsPinkPotopil2":
			if (startHeroType == 4) 
			{
				dialog.text = "Ellie, yaşadıklarımız bizi birbirimize daha da yakınlaştırdı gibi hissediyorum. Sadece kaptan ve subaydan fazlası olabiliriz. Kabul et - sadece kendine bile olsa, sen de bunu hissediyorsun.";
				link.l1 = "Ancak hayallerinde görebilirsin, Tommy. Ve adım Helen, Ellie değil. Ama sanırım artık bana Rumba diyebilirsin, yeter ki pohpohlamayı bırak.";
			}
			else
			{
				dialog.text = "Hayatımda hiç bu kadar mutlu olmamıştım! Bana bu süreçte yardımcı olduğun için teşekkür ederim. Biliyor musun, bence sen de en az Jack kadar iyi bir kaptansın. Hatta belki daha da iyisin!";
				link.l1 = "Ah, beni onurlandırıyorsunuz. Karşılaştırma için de teşekkür ederim, sanırım.";
			}
			link.l1.go = "BM_IronsPinkPotopil3";
		break;
		
		case "BM_IronsPinkPotopil3":
			if (startHeroType == 4) 
			{
				dialog.text = "Hiç de öyle değil. Hiçbir şekilde yağcılık yapmıyorum. Fark etmişsindir, ben pek kimseyi böyle övmem. O yüzden sus ve senin hakkında böyle düşündüğüme sevin.";
				link.l1 = "Bunu söylediğin şekilde beğendiğimi söyleyemem, ama genel olarak beni iyi bir kaptan olarak gördüğüne sevindim. Ama... komuta zinciri, Tommy, komuta zinciri.";
			}
			else
			{
				dialog.text = "Hiç de öyle değil. Hiçbir şekilde yağcılık yapmıyorum. Fark etmişsindir, ben pek kimseyi böyle övmem. O yüzden sus ve senin hakkında böyle düşündüğüme sevin.";
				link.l1 = "Bunu söylediğin şekli pek beğendiğimi söyleyemem, ama genel olarak beni iyi bir kaptan olarak görmene sevindim. Ama... hiyerarşi var Tommy, hiyerarşi.";
			}
			link.l1.go = "BM_IronsPinkPotopil4";
		break;
		
		case "BM_IronsPinkPotopil4":
			if (startHeroType == 4) 
			{
				dialog.text = "Ah, hadi ama, ne sıkıcısın! Bence artık seninle sadece bir kaptan ve subayı değil, gerçek dost olduk. Sence de öyle değil mi?!";
				link.l1 = "Heh. Belki. Senin düşmanın olmaktansa dostun olmak daha iyi. Ve madem görgü kuralları pek umurunda değil, sanırım buna alışmam gerekecek.";
			}
			else
			{
				dialog.text = "Ah, hadi ama, sıkıcı olma! Bence artık seninle sadece bir kaptan ve subayı değil, gerçek dostlar olduk. Sence de öyle değil mi?!";
				link.l1 = "Heh. Belki de. Senin dostun olmak, düşmanın olmaktan iyidir. Ve madem görgü kuralları sana göre değil, sanırım buna alışmam gerekecek.";
			}
			link.l1.go = "BM_IronsPinkPotopil5";
		break;
		
		case "BM_IronsPinkPotopil5":
			if (startHeroType == 4) 
			{
				dialog.text = "Sana bir... hediyem var, Kaptan.";
			}
			else
			{
				dialog.text = "Sana bir... hediyem var, Kaptan.";
			}
			link.l1 = "Vay canına, şuna bak! Kara leke mi? Beni de görevden almak mı istiyorsun, ha Tommy? Kaptan olmak istiyorsun yani? Ha-ha-ha-ha! Hani biz dosttuk?";
			link.l1.go = "BM_IronsPinkPotopil6";
		break;
		
		case "BM_IronsPinkPotopil6":
			dialog.text = "Bu bir kara İŞARET, seni aptal. Biliyor musun, bu atkıya kafatası ve kemikleri işlediğim anda bana şans getirmeye başladığını düşünmeye başladım. Açıklayamıyorum. Al bunu. Ayrıca... istersen, her zaman güvenilir kılıcımı ve zırhımı ödünç alabilirsin... geriye ne kaldıysa, ha-ha! İşine yarar! Çok yol kat edeceksin. Ve ben de buna tanık olmak istiyorum. Rastgele bir kurşunla ölmeni istemem.";
			link.l1 = "Sağ ol dostum! Elimden geleni yapacağım. Sen de izle ve hayran kal, ha-ha-ha!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_PinkPotopil_4");
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabeHouseGood1":
			Notification_Reputation(true, 71, "low");
			if (startHeroType == 4)
			{
				dialog.text = "Böyle bir şeye kim inanır ki... Üzgünüm, hanımefendi. "+TimeGreeting()+". Size nasıl yardımcı olabilirim? Çok endişeli görünüyorsunuz.";
			}
			else
			{
				dialog.text = "Ne? Bu saatte kim gelir? Oldukça endişeli görünüyorsunuz, efendim. Size nasıl yardımcı olabilirim?";
			}
			link.l1 = "Rahatsızlığınız için özür dilerim, Kaptan Callow. Benim adım "+GetFullName(pchar)+", ve ben eski silah arkadaşlarından birinin adına geldim.";
			link.l1.go = "BM_GabeHouseGood2";
		break;
		
		case "BM_GabeHouseGood2":
			dialog.text = "Hangi yoldaş? Hem Eski Dünya'da hem de Yeni Dünya'da çok yoldaşım oldu.";
			link.l1 = "Başta, sadece sandıklarından birine bir şey bırakmak istemiştim. Ya da belki masanın üstüne, böylece daha çabuk fark ederdin. Geçmişinden bir adamla ilgili. Al, bak ve kendin oku.";
			link.l1.go = "BM_GabeHouseGood3";
		break;
		
		case "BM_GabeHouseGood3":
			dialog.text = " Kara leke mi? Dostlarım arasında korsan olduğunu hatırlamıyorum. Yoksa bazıları o yola mı saptı? Siyah ipek mi? Gerçekten mi... Ah, Thomas. Senin gibi bir adamın o herifle iş tuttuğuna şaşırdım.";
			link.l1 = "Üzgünüm, ama ona alçak demek sana düşmez. Savaş alanından kaçtın ve Tom'a iftira attın. Belki sonra pişman olup burada, Takımadalar'da örnek bir subay oldun, ama bu geçmişi değiştirmez.";
			link.l1.go = "BM_GabeHouseGood4";
		break;
		
		case "BM_GabeHouseGood4":
			dialog.text = "Sana bunu mu söyledi? Hiç şaşırmadım – hikâyelerini anlatacak doğru insanı bulmayı her zaman bilirdi. Thomas lafını iyi kullanırdı. Onu tanımıyorsun, gerçek hikâyeyi de bilmiyorsun, neye bulaştığından da haberin yok. Sana anlatabilirim – zaten artık uyuyamayacağım.";
			link.l1 = "Dinlemek asla kötü bir fikir değildir. Devam et, Kaptan Callow.";
			link.l1.go = "BM_GabeHouseGood5";
		break;
		
		case "BM_GabeHouseGood5":
			dialog.text = "Yani, Thomas benim kaçtığımı ve sonra ona iftira attığımı mı söylüyor? Bilmelisin ki, aslında tam tersi oldu! Kralın süvarileri yaklaşırken, Tom takviye getireceğini söyledi. Biz de geri çekilmedik - bekledik. Bütün birliğimiz öldü! Eğer onun söz verdiği takviyeleri beklemeseydik, geri çekilip hayatta kalabilirdik! Sonunda sadece ben, Frankie ve lanet Thomas hayatta kaldık.";
			link.l1 = "Yani demek istediğin...";
			link.l1.go = "BM_GabeHouseGood6";
		break;
		
		case "BM_GabeHouseGood6":
			dialog.text = "Ben diyorum ki, bizim çocukların kanı Tom'un ellerinde de en az Kraliyetçiler kadar. Sürgün cezasına çarptırıldığı için şanslı, asılmadığına dua etsin! Şimdi de yüzü var, kin tutuyor, bana düello teklif ediyor! O buna layık bile değil!";
			link.l1 = "Yani gitmeyeceksin? Bunun ne anlama geldiğini biliyorsun. Onur yasaları herkes için yazılmıştır.";
			link.l1.go = "BM_GabeHouseGood7";
		break;
		
		case "BM_GabeHouseGood7":
			dialog.text = "Elbette biliyorum. Ve bu yüzden gideceğim. Tom'un geçmişteki askeri başarıları yüzünden cumhuriyet mahkememizin tamamlayamadığını bizim bitirmemiz gerek. Ve sen... sen düzgün birine benziyorsun. Sana tavsiyem, dostlarını daha akıllıca seçmen olurdu. Tom ve onun gibilerle işin olmasın.";
			link.l1 = "Ama Thomas artık benim emrimde, gemimde bir subay. "+GetSexPhrase("Onu gözümün önünden ayırmam ve seninle karşılaşmasından sağ çıkarsa kendini daha fazla rezil etmesine izin vermem.","")+"";
			link.l1.go = "BM_GabeHouseGood_Tommi1";
			link.l2 = "Benim yerimde olsaydınız ne yapardınız, Kaptan Callow?";
			link.l2.go = "BM_GabeHouseGood_Gabe1";
		break;
		
		case "BM_GabeHouseGood_Tommi1":
			dialog.text = "Eh, Tom seni hikayesiyle ikna edebildiyse, bunu tekrar yapmakta hiç zorlanmaz.";
			link.l1 = ""+GetSexPhrase("Ama onur yasalarına göre, ona ihanet edemem. Ben","Ben")+" adamlarımın sorumluluğu bende... Onun gibi olmayacağım. Ve eğer hayatta kalırsa, bundan sonra ona karşı daha dikkatli ve sorgulayıcı olacağım.";
			link.l1.go = "BM_GabeHouseGood_Tommi2";
		break;
		
		case "BM_GabeHouseGood_Tommi2":
			dialog.text = "Zor bir karar. Ama fikrini değiştirmeye çalışmayacağım. Peki, hoşça kal, "+GetSexPhrase("beyefendi","özlemek")+" - Tom'la buluşmaya hâlâ hazırlanmam gerekiyor.";
			link.l1 = "Hoşça kal, Kaptan Callow.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_GabeHouseGood_Gabe1":
			dialog.text = "Adalet yerini bulsun! Bana yardım et, Thomas'ı devirelim, "+pchar.lastname+". Nadir bir alçak ve korkak, ama çok iyi nişancı - bu kolay olmayacak. Ama birlikte...";
			link.l1 = "Hmm, Thomas'ı yenmene yardım etmemi mi istiyorsun? Böyle bir düelloda ne kadar onur var ki? Bunu aranızda halledin, ben karışmayacağım.";
			link.l1.go = "BM_GabeHouseGood_Gabe2";
		break;
		
		case "BM_GabeHouseGood_Gabe2":
			dialog.text = "Onu tanıyan biri olarak, adil bir düello olacağından şüpheliyim. Tarafsız kalmakla sadece haksızlığa göz yumuyorsun. Yanılıyor muyum?";
			link.l1 = "Anlaşılan Tom'u benden daha iyi tanıyorsun ve onun gerçekte nasıl biri olduğunu biliyorsun. Haklısın – şimdiden Portland Körfezi'nde bir pusu kuruyor ve benim yardımımı bekliyor – tıpkı senin şimdi benden beklediğin gibi.";
			link.l1.go = "BM_GabeHouseGood_Gabe3";
		break;
		
		case "BM_GabeHouseGood_Gabe3":
			dialog.text = "O zaman bu bir düello değil, bir kavga. Ama Thomas'ı öldürmeyi önermiyorum. Onu tutuklayacağız! Askerleri getireceğim ve Eski Dünya'da başaramadığımızı burada tamamlayacağız. Eğer onu yine aklamaya kalkarlarsa, Albay'a yazacağım ya da onu bizzat buraya getirip yargılatacağım. Thomas silahlarını bırakmazsa, bu onun kendi suçu olur.";
			link.l1 = "Bu kulağa çok daha iyi geliyor.";
			link.l1.go = "BM_GabeHouseGood_Gabe4";
		break;
		
		case "BM_GabeHouseGood_Gabe4":
			dialog.text = " Bunu duyduğuma sevindim, "+pchar.lastname+"! Böyle bir karar vermenin senin için kolay olmayabileceğini anlıyorum, ama emin ol, doğru seçimi yaptın. Ve bunu garantiye almak için, sana başka bir konuda da yardımcı olacağım.";
			link.l1 = "Ne oldu, Kaptan Callow?";
			link.l1.go = "BM_GabeHouseGood_Gabe5";
		break;
		
		case "BM_GabeHouseGood_Gabe5":
			dialog.text = "Al, bunu al. Hediye değil, ödünç - dediğim gibi, Thomas çok iyi bir dövüşçüdür ve onunla karşılaşırken elinde paslı bir demir parçası değil, düzgün bir silah olsun. Bu güzelliği bana bizzat Albay Doyley verdi, ama gerçek bir dövüşte her zaman pala kılıcı tercih ederim.";
			link.l1 = "Gerçekten de harika bir rapier. Teşekkür ederim.";
			link.l1.go = "BM_GabeHouseGood_Gabe6";
			GiveItem2Character(PChar, "blade_40");
		break;
		
		case "BM_GabeHouseGood_Gabe6":
			dialog.text = "Bana teşekkür etme - sana ödünç veriyorum, hediye etmiyorum, unutma. Şimdi koya git ve sevgili Tom'la rolünü oyna, ben de takviye kuvvetleri toplayacağım. Orada görüşürüz.";
			link.l1 = "Orada görüşürüz, Kaptan Callow.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_GabePlan");
		break;
		
		case "BM_GabeHouseNeutral1":
			Notification_Reputation(false, 71, "low");
			if (startHeroType == 4)
			{
				dialog.text = "Sen kimsin, bayan? Sanırım yanlış geldiniz. Ben, şey, gece servisi falan da sipariş etmedim.";
				link.l1 = "Helen MacArthur. Ve arzularınızı kontrol altında tutun, Bay Callow. Ben namuslu bir kızım. Bu iklim beni geceleri bile bunaltıyor. Böyle bir şeyi yabancı bir kıza söylemeye utanmadınız mı? Sizin örnek bir subay olduğunuz söylendi bana.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
			else
			{
				dialog.text = "Sen kimsin, ne istiyorsun? O sırıtışını hiç beğenmedim, bayım.";
				link.l1 = ""+GetFullName(pchar)+". Ve pek misafirperver değilsiniz, Bay Callow.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
		break;
		
		case "BM_GabeHouseNeutral2":
			dialog.text = "Bu saatte yabancıları farklı mı selamlıyorsun?";
			link.l1 = "Sana başka zamanlarda evde olmadığın söylendi.";
			link.l1.go = "BM_GabeHouseNeutral3";
		break;
		
		case "BM_GabeHouseNeutral3":
			dialog.text = "Elbette değilim - hizmetim, görevim ve dürüst emeğim var, ki bunlar senin görünüşüne bakılırsa sana yabancı kavramlar.";
			link.l1 = "Böylesine bir özgüven! Ama zaten, aksi halde Albay Doyley ve diğerlerini dürüstlüğüne inandıramazdın. Senden hiçbir şey istemiyorum Gabe, ama eski bir tanıdığın istiyor. Al bakalım.";
			link.l1.go = "BM_GabeHouseNeutral4";
		break;
		
		case "BM_GabeHouseNeutral4":
			dialog.text = "İkna oldun mu? Gabe? Şunu söyleyeyim! Kara işaret mi? Demek korsansın? Bir dakika... siyah ipek... yoksa bu... Ah, anladım. Thomas, seni lanet olası herif, hâlâ seni Frank'le birlikte ihbar ettiğimiz için bize kızgınsın, ha ha ha ha!";
			link.l1 = "Hey! Tom benim gemimde subaydır ve saygıyı hak eder. O, Takımadaların en iyi nişancılarından biridir.";
			link.l1.go = "BM_GabeHouseNeutral5";
		break;
		
		case "BM_GabeHouseNeutral5":
			dialog.text = "Onun kötü bir nişancı olduğunu söylemedim. Ama Thomas'ı pek tanımadığın belli. Bizi hepimizi satan oydu. Ama seninle tartışmanın anlamı yok, görüyorum ki birbirinize tam anlamıyla uygunsunuz.";
			link.l1 = "Umurumda değil. Masallarını Doyley ve o saf aptallara sakla. Eğer dedikleri kadar cesur ve onurluysan, meydan okumayı kabul eder ve şimdi gelirsin. Peki, kabul ediyor musun?";
			link.l1.go = "BM_GabeHouseNeutral6";
		break;
		
		case "BM_GabeHouseNeutral6":
			dialog.text = "Evet, evet. Şimdi muhafızları çağırmadan evimden defol.";
			link.l1 = "Memnuniyetle, Gabe.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_IronsJamaicaJungle1":
			if (CheckAttribute(pchar, "questTemp.BM_GabePlan"))
			{
				dialog.text = "Neden bu kadar tedirginsin? Korkuyor musun, yoksa ne?";
				link.l1 = "Bir adamın elinde tüfekle üstüne koştuğunu gören herkes tedirgin olurdu – seni başta tanıyamadım. Burada ne yapıyorsun, Tommy?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_2";
			}
			else
			{
				dialog.text = "Nasıl geçti? Hey, hey, neden bana öyle bakıyorsun? Korkuttun beni, hehehe.";
				link.l1 = "Kim kimi korkutuyor! Kim öyle kaçıp gidiyor?! Misafirleri koyda karşılayacaktık!";
				link.l1.go = "BM_IronsJamaicaJungle2";
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_2":
			dialog.text = "Heh, belki de. Beklemekten yoruldum – hem sevgili misafirlerimiz hem de senden. Ve buranın gerçek bir pusu için daha uygun olduğuna karar verdim. Sonuçta ben bir avcıyım, düellocu değil.";
			link.l1 = "Anladım.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_3";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_3":
			dialog.text = "Evet. Peki, hediyemi Gabe'in evine bıraktın mı? Beklettin beni. Şehre girebilsem ben çoktan halletmiştim. Ne o, Kaptan? Gözlerin neden dalgın? Bir sorun mu var?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Güvenilir) Endişeliyim. Gabe korkaktır ama aptal değildir. Ya onun yerine buraya koca bir asker birliği gelirse? Ya da koya yaklaşıp önce gemimizi batırırlarsa?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD1";
				Notification_Perk(true, "Trustworthy");
			}
			else
			{
				link.l2 = "Gabe beni gördü. Kaçmak zorunda kaldım.";
				link.l2.go = "BM_IronsJamaicaJungle_GabePlan_4";
				Notification_Perk(false, "Trustworthy");
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD1":
			dialog.text = "Heh, anlıyorum - bunun işe yarayacağından ben de tam emin değilim. Böyle büyük bir şey başına ilk kez geliyor, değil mi? Sorun değil, olur böyle şeyler. Her şeyi düşündüm. Askerler Gabe olmadan gelirse, hemen kaçarız. Gabe'le gelirlerse, gözünün ortasına bir kurşun sıkarım, yine kaçarız. Eğer körfeze bir gemi yanaşırsa, Maroon Kasabası'na koşarız - oraya gitmeye cesaret edemezler, sonra da ne yapacağımıza karar veririz.";
			link.l1 = "Her şeyi gerçekten düşünmüşsün, Tommy.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD2";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD2":
			dialog.text = "Elbette yaptım. Şimdi misafirimizi bekleyelim...";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe");
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_4":
			dialog.text = "Ha ha, sen de benim kadar iyi bir hırsızsın, ben ne kadar kralcıysam. Ama neden gözlerime bakmıyorsun... Kaptan? Gabe'le konuşuyordun, değil mi?";
			link.l1 = "Hayır, ne diyorsun sen? Onunla neden konuşayım ki?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_5";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_5":
			dialog.text = "Çünkü hepiniz laf ebesisiniz. Sadece konuşuyorsunuz. Peki, sevgili Gabe size ne anlattı?";
			link.l1 = "Önemli mi, Tommy?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_6";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_6":
			dialog.text = "Açıkçası, hayır. Eğer arkamdan iş çevirmezsen olurdu. Ama görüyorum ki bunu zaten yapmışsın. Onun tarafını tutman için seni kandırdı, değil mi?";
			link.l1 = "Hayır. Tam olarak değil. Silahı indir, Tommy. Sana söz veriyorum, telafisi olmayan bir şey yaşanmak zorunda değil. Belki taş ocaklarında çalışırsın. Gabe'den merhamet göstermesini isteyeceğim. Gerekirse Albay Doyley'den bile rica ederim.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_7";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_7":
			dialog.text = "Ne kadar da iyi bir insansın. Yıllarımı taş ocağında geçirdikten sonra ciğerlerimi öksürebilmem için bana merhamet mi gösteriyorsun? O zindan gemilerine bir daha asla dönmem. Asla. Ve sen... Senin de diğerlerinden farksız olduğunu anlamalıydım. Bakışlarında bir tuhaflık var. Önce seninle ilgileneceğim, böylece Gabe sonrasında daha kolay olacak.";
			link.l1 = "Bize başka seçenek bırakmıyorsun!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaSTommi");
		break;
		
		case "BM_GabePlan_TommiMertv":
			dialog.text = "Pekala, görüyorum ki bunu zaten yapmışsın, "+GetSexPhrase("bey","kaçırmak")+". Ben de bir ekip topluyordum, sayıca üstün olursak Tom iki kere düşünür ve silahını bırakır diye düşünerek.";
			link.l1 = "Ve sen de bayağı geciktin, Kaptan Callow.";
			link.l1.go = "BM_GabePlan_TommiMertv2";
		break;
		
		case "BM_GabePlan_TommiMertv2":
			dialog.text = "Sana söylemiştim, adam topluyordum. Garnizonumuzun en iyileri. Tom zaten deneyimli bir asker. Ama ben bunları kime anlatıyorum ki? Aferin, "+GetSexPhrase("Bey.","özlemek")+" "+pchar.lastname+". "+GetSexPhrase("Seninle gurur duyuyorum, delikanlı","İtiraf etmeliyim ki, genç hanım, sende güzellik, zeka ve yetenek eşit derecede var")+". Sana ilk tanıştığımızda da söylediğim gibi, doğru kararı verdin. Şimdi adalet yerini buldu.";
			link.l1 = "Senin için çok iyi sonuçlandı. Gururlu musun?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict";
			link.l2 = "Eh, ben bir savaş gazisi değilim ama dövüşebilirim, az önce fark etmiş olabilirsiniz. Yine de teşekkür ederim, efendim. Adalet benim için boş bir kelime değil.";
			link.l2.go = "BM_GabePlan_TommiMertv_Mir";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir":
			dialog.text = "Ve bu da takdire şayan, "+GetSexPhrase("genç adam","genç hanım")+"Ancak, bu güzel günü tamamlamak için hâlâ yapmamız gereken bir şey daha var.";
			link.l1 = "Hmm, peki o nedir? Sonuçta Tom zaten yenildi.";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir2":
			dialog.text = "Bana ait olan bir şey sende. Güzel İtalyan rapierimi geri ver lütfen. Sonuçta o sadece bir kürdan değil, bir hatıra – bizzat Albay Doyley’den bir hediye.";
			if (!CheckCharacterItem(PChar, "blade_40"))
			{
				link.l1 = "Eh... Şöyle bir durum var, Kaptan Callow... rapier kayboldu. Onu kaybettim. Üzgünüm.";
				link.l1.go = "BM_GabePlan_TommiMertv_Poteryal";			//Потеряли Рапиру
				break;
			}
			if (CheckCharacterItem(PChar, "blade_40"))
			{
				link.l2 = "Ah, tabii. Lütfen. Çalmak istememiştim. Ama yalan söylemeyeceğim – onu kendime saklamak isterdim. Ama işte, Kaptan Callow, buyurun.";
				link.l2.go = "BM_GabePlan_TommiMertv_Soglasen";			//Согласен
			}
			if (CheckCharacterItem(PChar, "blade_42"))
			{
				link.l3 = "Sana daha iyi bir teklifim var, Kaptan.";
				link.l3.go = "BM_GabePlan_TommiMertv_Obmen";			//Обмен
			}
			link.l4 = "Ama az önce ona kürdan dedin. Ayrıca, rapierleri sevmediğini de söyledin. Öte yandan, ben bir ödülü hak ediyorum.";
			link.l4.go = "BM_GabePlan_TommiMertv_Otkaz";				//Отказ
		break;
		
		case "BM_GabePlan_TommiMertv_Soglasen":
			dialog.text = "Bu güzelliği herkes elinde tutmak isterdi! Onu bana geri getirdiğin için teşekkür ederim. Senin yerinde olan çoğu insan inat ederdi.";
			link.l1 = "Senin oldu. Sanırım burada işimiz bitti?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_40");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen":
			dialog.text = "İlgilenmiyorum. Sadece rapier'i geri ver, iyi ayrılalım, "+GetSexPhrase("Bayım.","miss")+" "+pchar.lastname+".";
			link.l1 = "Bu rapierin senin için değerli olduğunu, tarihi olan silahları sevdiğin için mi düşünüyorum? Bende de aynısından var, ve sen bunu çekmecede saklamak yerine yanında taşımayı tercih edersin, değil mi?";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen2";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen2":
			dialog.text = "Öyle mi? Anlaşmaya varacağımızı garanti edemem ama dinliyorum. Gerçekten de tarihi olan silahlara ilgim var. Fakat bu rapier Albay'dan bir hediyeydi. Bu yüzden benim için çok değerli.";
			link.l1 = "Geniş kılıçları sevdiğini söylemiştin. Al, bu bizim sevgili Tommy'mize aitti. Yıllar boyunca bu silahın neler yaşadığını bir düşün. Ve seninle daha neler yaşayacağını...";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen3";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen3":
			dialog.text = "Çok ikna edicisin, delikanlı! Thomas'ın kılıcını sallıyorsun... ne ironik. Neyse, al rapier'i. Ama bil ki, onu kolay kolay vermiyorum.";
			link.l1 = "Anlaşabildiğimize sevindim. Sanırım bu bir veda, Kaptan Callow?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_42");
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Commerce", 500);
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal":
			dialog.text = "NE?! Nasıl olur da... Koca kılıcı nasıl kaybedersin?! Gerçekten aptalsın!";
			link.l1 = "Sakin ol! Sadece bir rapier bu. Zaten asla kullanmazdın. Tom öldü – şimdi önemli olan tek şey bu değil mi?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal2";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal2":
			dialog.text = "Sadece bir rapier mi?! O benim hazinemdi! Albay Doyley'in bizzat kendisinin hediyesi! Hiç kullanmamış olmam umurumda değil!";
			link.l1 = "O zaman bana vermemeliydin, değil mi?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal3";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal3":
			dialog.text = "Şimdi çeneni kapalı tutsan iyi olur, "+GetSexPhrase("Bey.","özlemek")+" "+pchar.lastname+". Barışçıl bir şekilde yollarımızı ayırabilirdik. Ama şimdi... şimdi sana bir ders vermek istiyorum, "+GetSexPhrase("genç adam","genç hanım")+".";
			link.l1 = "Senin gibi öğretmenlerle mezarlıklar dolu.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz":
			dialog.text = "Elbette yapıyorsun. Ama bir subaya yardım ettin diye onun kişisel silahını öylece alamazsın, değil mi?";
			link.l1 = "Katılıyorum, ama zaten sen kullanmıyorsun. Odanda bir çivide asılı kalacak sadece. Oysa bende işe yarar bir kullanım bulur. Albay Doyley onu kaybettiğini kontrol edecek değil ya, öyle değil mi?";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz2";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz2":
			dialog.text = "Bu konu tartışmaya açık değil, genç adam. En başından beri söyledim, bu bir hediye değil. Rapier'i bana ver. Şimdi.";
			link.l1 = ""+GetSexPhrase("Ben senin oyuncak askerlerinden biri değilim","Ben senin liman fahişelerinden biri değilim")+", senden emir almak için burada değilim. Ben de senin gibi bir gemi kaptanıyım. Rapier bende kalacak, ister hoşuna gitsin ister gitmesin.";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz3";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz3":
			dialog.text = "Görünüşe bakılırsa Thomas seni epey etkilemiş. O zaman, eğer bu kadar istiyorsan, bunun için öl.";
			link.l1 = "Ben de aynı şeyi düşündüm!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Platok":
			dialog.text = "Al, bunu da al. Hiç ihtiyacım yok. Bugünün hatırası olarak sende kalsın. Bundan sonra biraz daha az saf olmayı dene. Ve Thomas gibi hergelelerin seni pis işlerine bulaştırmasına izin verme.";
			link.l1 = "Heh, bana kara lekeyi mi veriyorsun, Kaptan Callow?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok2";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabePlan_TommiMertv_Platok2":
			dialog.text = "Pekâlâ, ikimiz de korsan değiliz, değil mi, "+pchar.name+"? Bu sana bir hatırlatma olsun. Kendine dikkat et, Takımadalar senin gibi adamlara ihtiyaç duyuyor. "+GetSexPhrase("Belki de Donanma'ya katılmanı öneririm ve Albay Doyley'e bir tavsiye mektubu yazarım...","")+"";
			link.l1 = "Üzgünüm, teklifinizi kabul edemem, Kaptan.";
			if (startHeroType == 3)
			{
				link.l1 = "Hm. Bunu bir düşüneceğim. Hem de iyice.";
			}
			if (startHeroType == 4)
			{
				link.l1 = "Elveda, efendim.";
				link.l1.go = "exit";
				AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
				break;
			}
			link.l1.go = "BM_GabePlan_TommiMertv_Platok3";
		break;
		
		case "BM_GabePlan_TommiMertv_Platok3":
			dialog.text = "Sen bilirsin. Peki, hoşça kal. "+GetSexPhrase("Bayım.","özlemek")+" "+pchar.lastname+". Ironsides'ın geriye kalanını taşımayı hak ediyorsun. Elveda.";
			link.l1 = "Elveda, efendim.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict":
			dialog.text = "Senin konuşma tarzını beğenmiyorum, "+GetSexPhrase("bayım","miss")+". Ne demek istiyorsun?";
			link.l1 = "Bilerek oyalandın, en iyi adamlarını topladın. Neden? Tek bir adamı yakalamak için mi? Şehirde devriye gezen birkaç askeri yanına alıp hemen yardımıma gelmeliydin!";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict2";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict2":
			dialog.text = "Top yemi mi getiriyorsun?! Tom onlar gibi sıradan bir şehir muhafızı değildi. Onun eğitimi ve tecrübesi bambaşkaydı - o da benim gibi lanet olası bir Zırhlı! Bunu nasıl fark etmiyorsun?";
			link.l1 = "Tam tersine, bunun gayet farkındayım. Bu yüzden seninle buradaydık – Tom'la kılıçlarımızı çaprazlayıp, adamların onu canlı yakalamasını sağlamak için. Üstelik sen de Ironclad’sın. Aynı şirkettensiniz. Onunla yüz yüze dövüşmekten bu kadar mı korktun?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict3";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict3":
			dialog.text = "Beni korkaklıkla suçlamaya nasıl cüret edersin, genç "+GetSexPhrase("adam","özlemek")+"   İstediğine sor, bu şehir için yaptığım işleri uzun uzun anlatırlar. ";
			link.l1 = "Henüz bitirmedim. Bu ‘başarıların’ gerçekten senin elinden çıkıp çıkmadığını merak etmeye başladım. Tom’la beni birbirimize düşürüp tüm övgüyü kendine almak istedin. Daha önce de böyle yapmıştın, değil mi?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict4";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict4":
			dialog.text = "Suçlamalarından bıktım artık, "+GetSexPhrase("Bey.","özlemek")+" "+pchar.lastname+". Kavga mı istiyorsun? Alacaksın. Hem de şimdi.";
			link.l1 = "Gerçek acıtır, değil mi Gabe?";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Conflict = true;
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_1":
			dialog.text = "";
			link.l1 = "Gabe! Ne zamandır görüşmedik, kaç tane kasvetli kış geçti! Şuna bak, hâlâ o kendini beğenmiş sırıtışın yüzünde, kahretsin seni!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_2":
			dialog.text = "Thomas! Bugün, yıllardır adaletimizin başaramadığını kendi ellerimle başaracağım için memnun olmalıyım. Üstelik keyfim yerinde olduğundan, silahlarını bırakıp bizimle gelmene izin vereceğim. Belki de tekrar kürek mahkûmluğuna gönderilirsin. O durumda, seni bizzat oraya ben götüreceğim.";
			link.l1 = "Heh, hadi durdur da görelim! Yanında duran birkaç adamın beni engelleyeceğini mi sanıyorsun!!!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_3";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_3":
			dialog.text = "Onlarla birlikte olan tek kişi onların kendisi mi sanıyorsun? Şu anda yanında duran kişiden bahsediyorum.";
			link.l1 = "Ne?";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_4";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_4":
			dialog.text = "Thomas, Thomas, Thomas... her zamanki gibi, bu dünyada yine yalnızsın. Neredeyse sana acıyacağım!";
			link.l1 = "Lanet olası fareler! Kahrolası herifler!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_5";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_5":
			StartInstantDialog("Irons", "BM_GabePlan_GazgovorTommiAndGabe_6", "Quest\BlackMark.c");
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_6":
			dialog.text = "Bu ne demek oluyor?! O bununla ne demek istedi?!";
			link.l1 = "Tommy, dinle...";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_7";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_7":
			dialog.text = "Tam da bunu yapıyorum! Bana onun yalan söylediğini söyle!";
			link.l1 = "Maalesef, o haklı. Silahlarınızı bırakın. Bugün kimsenin ölmesine gerek yok. Sizin için bizzat iyi bir söz söyleyeceğim, böylece asılmaktan kurtulursunuz. Belki bir gün dürüst bir hayata da dönebilirsiniz.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_8";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_8":
			dialog.text = "Buna sen karar veremezsin! Hem de kesinlikle sen! Böyle bir komutanın varken düşmana ne gerek var! Bir başka lanet fare daha.";
			link.l1 = "Hadi ama Tommy. Senin gibi insanlar için temiz bir kaçış yoktur.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_9";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_9":
			dialog.text = " Mürettebatında, geminde bir yer... Başlangıç için yeterli olurdu, eğer adamlarının arkasında durmaya cesaretin olsaydı! Ama artık bunun bir önemi yok. Kahrolun, hepiniz! Korkak bağırsaklarınızı yere dökeceğim, seni küçük fare. Ve sen, Gabe, seni de yanıma almaya çalışacağım...";
			link.l1 = "Bekle, Tommy, hayır!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe_Fight");
		break;
		
		case "BM_GabePlan_GabeWin_1":
			dialog.text = "Tebrikler, "+GetSexPhrase("genç adam","genç hanım")+"! Thomas'a her şeyin onun planına göre gidiyormuş gibi hissettirmeyi başardığına gerçekten hayran kaldım - ihaneti hemen sezerdi.";
			link.l1 = "Ah, elbette, teşekkür ederim, Kaptan Callow.";
			link.l1.go = "BM_GabePlan_GabeWin_2";
		break;
		
		case "BM_GabePlan_GabeWin_2":
			dialog.text = "Bir şey mi canını sıkıyor, "+GetSexPhrase("Bayım.","özlemek")+" "+pchar.lastname+"?";
			link.l1 = "Tom... sadece senin tarafında olmama kızgın değildi. Sesinde gerçek bir umutsuzluk ve anlam verememe vardı, sanki...";
			link.l1.go = "BM_GabePlan_GabeWin_3";
		break;
		
		case "BM_GabePlan_GabeWin_3":
			dialog.text = "...sanki burada mağdur olan oymuş gibi. Beklenirdi zaten. Unutma Charles, bir canavar da acı hissedebilir. Ama bu, onun canavar olduğu gerçeğini değiştirmez. Birçok suçlu, çoğu zaman gerçekten haklı ve masum olduğuna inanır.";
			link.l1 = "Bunu aklımda tutmaya çalışacağım. Sanırım burada işimiz bitti, ne dersiniz, Kaptan?";
			link.l1.go = "BM_GabePlan_GabeWin_4";
		break;
		
		case "BM_GabePlan_GabeWin_4":
			dialog.text = "Genel olarak evet, ama bu güzel günü tamamlamak için hâlâ yapmamız gereken bir şey daha var.";
			link.l1 = "Ha? Ne oldu?";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_IronsJamaicaJungle2":
			dialog.text = "Senin gelmen epey sürdü. O yüzden biraz keşif yapayım dedim. Her neyse, bence burada pusu kurmak, sahilde şövalyecilik oynamaktan daha akıllıca. Gabe'in evini bulup her şeyi açıkta bırakmayı başardın mı?";
			link.l1 = "Tabii ki yaptım, beni ne sanıyorsun, aptal mı? Aslında senin kaptanınım, Tommy. Eğer bir aptala hizmet ediyorsan, bu seni ne yapar?";
			link.l1.go = "BM_IronsJamaicaJungle3";
		break;
		
		case "BM_IronsJamaicaJungle3":
			dialog.text = "Ha-ha-ha-ha, hizmetteyken bu tür saçmalıklarla ne kadar sık karşılaştığımı tahmin bile edemezsin! Ama bizim durumumuzda, neyse ki, öyle bir şey yok. Peki, o zaman. Misafir bekliyoruz. Hazır mısın?";
			link.l1 = "Pekâlâ, Port Royal'ın tüm filosu ya da garnizonu buraya gelmediği sürece, ben hazırım.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CreateGabeInJungle");
		break;
		
		case "BM_GabeJungle1":
			dialog.text = "Thomas? Gerçekten sensin, demek...";
			link.l1 = "Tabii ki benim, yoksa başkasını mı bekliyordun, Gabe? Heh, yüzün bembeyaz, sanki hayalet görmüş gibisin. Ayrıca Eski İngiltere'deki halinden de şişmansın.";
			link.l1.go = "BM_GabeJungle2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabeJungle2":
			dialog.text = "Şimdi sonunda gerçekten sen olduğuna emin oldum. Her zamanki gibi kabasın. Ama sorun değil, o pis ağzını yakında sonsuza dek kapatacağım, seni alçak.";
			link.l1 = "Ha-ha-ha, şimdi konuşmaya başladık! Biliyor musun, aslında beni hayal kırıklığına uğrattın, Gabe. Yine! Sadece benimle başa çıkmak için yanında daha fazla adam getirmen gerekirdi. Hem de biz iki kişiyiz! Yoksa sana verebildikleri hepsi bu muydu, korkak?";
			link.l1.go = "BM_GabeJungle3";
		break;
		
		case "BM_GabeJungle3":
			dialog.text = "Yeter! Artık konuşmamızın bir anlamı yok.";
			link.l1 = "Bu konuda sana katılıyorum! "+pchar.name+"! Savaşa, Kaptan!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GabeJungleFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "BM_IronsJamaicaJungle4":
			dialog.text = "Heh, işte böyle! Huzur içinde yat, seni alçak.";
			link.l1 = "Peki, memnun musun Tommy? Biliyor musun, intikamını aldıktan sonra çoğu insan daha da kötüleşir.";
			link.l1.go = "BM_IronsJamaicaJungle5";
		break;
		
		case "BM_IronsJamaicaJungle5":
			dialog.text = "Ha, bunu bir yerden mi okudun? Böyle zayıfları hiç anlayamadım. Bah! Memnun muyum? O kadar mutluyum ki altıma işeyebilirim! O alçaklar en büyük felaketlerimin kaynağıydı!";
			link.l1 = "Senin adına sevindim. İntikam alman gereken başka kimse yok mu? Yoksa senden daha fazla kâğıt fişek şakası mı beklemeliyim?";
			link.l1.go = "BM_IronsJamaicaJungle6";
		break;
		
		case "BM_IronsJamaicaJungle6":
			dialog.text = "Sakin ol, Gabe sonuncusuydu. Şakalara gelince – merak etme, seninle ilgili artık olmayacak, en azından seni ilgilendiren kısmında.";
			link.l1 = "Gemiye geri dönelim mi o zaman?";
			link.l1.go = "BM_IronsJamaicaJungle7";
		break;
		
		case "BM_IronsJamaicaJungle7":
			dialog.text = "Zaten ona geri dönecektik, ister hâlâ intikam alacak birim olsun ister olmasın. Ama bir dakika...";
			link.l1 = "Ah, demek henüz bitmedi...";
			link.l1.go = "BM_IronsJamaicaJungle8";
		break;
		
		case "BM_IronsJamaicaJungle8":
			dialog.text = "Evet, öyle. Sana bir şey söylemek istiyorum. Bunu çok az kişiye söylerim. Ve bir daha da söylemem. Eğer bana gülersen, sana çok kızarım.";
			link.l1 = "Gülmeyeceğime söz veriyorum. Zaten, şakalarını komik olmaktan çok gergin buluyorum.";
			link.l1.go = "BM_IronsJamaicaJungle9";
		break;
		
		case "BM_IronsJamaicaJungle9":
			dialog.text = "Güzel. Yani... Bana yardım etmeye karar verdiğin için gerçekten minnettarım, Jack'in yaptığını yapmadığın için. Sen gerçek bir dostsun, Kaptan. Teşekkür ederim. Ayrıca... istersen, güvenilir kılıcımı ve zırhımı ödünç alabilirsin... Geriye ne kaldıysa, ha-ha!";
			link.l1 = "Sağ ol, bunu söylediğin için. Her gün subaylarından böyle bir şey duymuyorsun. Hadi bakalım, dostum.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_FinalInJungleWithTommy");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Irons_officer":
			dialog.text = "Emredersiniz, Kaptan?";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				Link.l1 = "Tommy, görünüşe göre buradan sonra yollarımız ayrılıyor.";
				Link.l1.go = "SharlieEpilog_Irons_1";
				break;
			}
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Peki, Rumba, bu gece kimin kemikleri üstünde dans edeceğiz?";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Evet, Ellie?";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Sizi dinliyorum, kaptan.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = ""+pchar.name+"?";
			}
			//////
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal") && !CheckAttribute(pchar, "questTemp.BM_TommiTieyasalOtkaz"))
			{
				Link.l4 = "Tommy, sana çok ciddi bir şey sormak istiyorum. Şey var... Kızılderililere ait bir taş put. Ve yardıma ihtiyacım olacak. Bunu ancak en yakın dostlarımdan, senin gibi olanlardan isteyebilirim. Yeni gelenler ya da henüz pek güvenmediğim kişiler olmaz.";
				Link.l4.go = "tieyasal_1";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tommy, martıları saymayı bırak. Tüm yükleri saydın mı? Bana tam bir rapor ve bir tahmin ver.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Tommy, bugünden itibaren limanlardan belirli malları satın almanı istiyorum.";
				Link.l12.go = "QMASTER_2";
				
				if (startHeroType == 4)
				{
					Link.l11 = "Tommy, gemiyle ilgili her şeyi rapor edebilir misin lütfen?";
					Link.l12 = "Tommy, artık oldukça yorulmaya başladım. Her limanda bazı malları tedarik edebilir misin?";
				}
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l11 = "Gemi ve içindekilerin durumu hakkında bir rapor hazırla, Tommy.";
					Link.l12 = "Limanlara uğradığımızda bazı malları temin edebilir misin?";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l11 = "Gemide ne varsa hepsini say ve genel durumu hakkında rapor ver.";
					Link.l12 = "Her limanda durduğumuzda bu malları almanı istiyorum.";
				}
			}
			//////
			Link.l1 = "Emirlerimi dikkatlice dinle!";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Birisi kesinlikle öyle. Ama şimdilik, emirlerimi dinle.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Emirlerimi dinle... Tommy. ";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "İyi, çünkü senin için yeni bir görevim var, Tommy.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Emirlerimi dinle, Tom.";
			}
			Link.l1.go = "stay_follow";
			//////
			link.l2 = "Bir şey yok, Tommy. Rahat ol.";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Bakalım nasıl olacak, Tommy.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Hayır, Tom, hiçbir şey.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Hayır, hiçbir şey.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Hiçbir şey, her şey yolunda.";
			}
			link.l2.go = "exit";
			NextDiag.TempNode = "Irons_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Envantere daha başlamadım bile. Kârımızı ve zararımızı saydığıma bile şükretmelisin, o açgözlü tüccarlarla pazarlık etmeyi geçtim. Envanter benim işim değil, ordudayken de hiç yapmadım, şimdi de yapacak değilim.";
			Link.l1 = "Bu ordu değil, Tommy. Ama peki, anladım, seni zorlamayacağım.";
			if (startHeroType == 4)
			{
				dialog.Text = "Ben katip değilim, Ellie. Bir zamanlar tanıdığım biri vardı, Daniel Crimson, kendini hep katip olarak tanıtırdı ama savaş alanını neredeyse hiç görmemişti. Yine de dövüşte tam bir canavardı. Ama ben öyle değilim ve bu konuda yalan söylemeyeceğim. Envanter işi bana göre değil. Zaten senin hatırın için hesaplarımızı tutuyorum. Daha fazlasını bekleme.";
				Link.l1 = "Pekala, Tommy, yapmayacağım.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Bak, ben bir katip değilim. Şimdiye kadar orduda bile, benim gibi sıradan askerlerden böyle bir şey istenmedi. Bu kuralı değiştirmeyelim.";
				Link.l1 = "Pekâlâ, yapmayalım.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Sayabildiğim tek şey, kaç düşmanımızı vurduğum. Ha-ha-ha. Onu bile bazen unutuyorum. Ben basit bir askerden fazlası değilim, anlıyor musun? Gemiyle ilgili kim ne bilsin ki – hayatımın çoğunu karada geçirdim.";
				Link.l1 = "Görünüşe bakılırsa bunu kendim yapmak zorunda kalacağım.";
			}
			Link.l1.go = "exit";
		break;

		case "QMASTER_2":
			dialog.text = "Beni ne sandın, arka sokaklarda çalışan bir ambarcı mı? Memlekette o yüreksiz korkaklara sadece küçümsemeyle bakardık. Soylu olmayabilirim ama hâlâ gururum var.";
			link.l1 = "Peki, peki, istemiyorsan istemiyorsun.";
			link.l1.go = "exit";
			if (startHeroType == 4)
			{
				dialog.Text = "Bak, ben basit, dürüst bir askerdim, ikmal subayı değilim kızım. Bu işlerden pek anlamam, öğrenmek de istemem. Bu, sana tüfeği zamana karşı söküp takmanı istemek gibi bir şey.";
				Link.l1 = "Bu gemideki sabit ve hareketli donanımın her bir parçasını ezbere sayabilirim. Ama madem öyle istiyorsun, Tom. Konu kapandı.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Hayır, yapamadım. Belki unuttun ya da bunu hiç bilmiyorsun, o yüzden açıklayayım. Senin için bu sıradan bir iş olurdu, ama bizim orduda ikmal ve destek hizmetlerine pek iyi davranılmaz. Lütfen beni onlarla bir tutma.";
				Link.l1 = "Ha-ha, iyi, iyi.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Bak, sana saygı duyuyorum elbette, ama kendime karşı gelip yapamayacağım ya da katlanamayacağım bir şeyi yapmam. O zamanlar zar zor saymayı öğrenmiştim, şimdi ise benden düzgün bir tedarikçi olmamı istiyorsun. Bu arada, onlardan hoşlanmadık – mühimmatı, suyu, yiyeceği ve tazeliğini hep kısmaya çalışıyorlar.";
				Link.l1 = "Hm, peki, bunu unutalım.";
			}
		break;
		
		case "stay_follow":
            dialog.Text = ""+GetSexPhrase("Ha, emir mi veriyorsun? Askeri disiplin ve o tarz şeyler hoşuna gidiyor galiba. Bana ne yapılması gerektiğini doğrudan söylesen daha iyi olurdu.","Sen bir çavuş falan gibisin. Ama bu sana hiç yakışmıyor – bunun için fazlasıyla güzelsin. Orduda bir gün bile dayanamazdın. Ama seni dinliyorum.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Anlaşılan, gerçekten de üniformaları, talimleri ve bütün o işleri pek seviyorsun. Peki, devam et.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Hangisi?";
			}
			
            Link.l1 = ""+GetSexPhrase("Hiçbir yere gitme ve hiçbir şey yapma - sadece gözlemle, anladın mı? Seni biliyorum.","Olduğun yerde kal, beni anladın mı?")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Burada dur, hiçbir yere gitme ve hiçbir şeye dokunma.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Burada kal ve kimsenin geçmesine izin verme.";
			}
			Link.l1.go = "Boal_Stay";
            Link.l2 = ""+GetSexPhrase("Beni takip et ve hiçbir şeye dalıp gitme – yoldan çıkan eşler ya da aniden ortaya çıkan eski savaş arkadaşları da dahil.","Yakında dur, olur mu? Sırtımı kollamanı isterim.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Beni takip et. Düşüncelere dalmışsın, görüyorum.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Beni takip et, yoksa bir nedenle durmadıysan.";
			}
			Link.l2.go = "Boal_Follow";
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Bu sefer senden farklı bir şey vurmanı istiyorum.";
					Link.l3.go = "SetGunBullets";
					if (pchar.sex == "man" && pchar.rank >= 15)
					{
						Link.l3 = "Yaklaşan çatışmada farklı mühimmat kullanmanı istiyorum.";
					}
					if (pchar.sex == "man" && pchar.rank >= 25)
					{
						Link.l3 = "Bir sonraki savaşta farklı mühimmat kullanacaksın.";
					}
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Tüfeğiniz için cephane türünü değiştirin.";
					Link.l4.go = "SetMusketBullets";
				}
				Link.l5 = "Yakın dövüş için ana silahını değiştir.";
				Link.l5.go = "SetPriorityMode";
				Link.l6 = "Düşmanlarınla aranda belli bir mesafe bırakmanı isterim.";
				Link.l6.go = "TargetDistance";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l6 = "Düşmandan belli bir mesafede durmanı istiyorum, Tommy.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l6 = "Düşmanla aranda belli bir mesafe bırak, Tommy.";
				}
			}
		break;
		
		case "SetGunBullets":
			Dialog.Text = ""+GetSexPhrase("Ne tür mühimmatlar? Umarım her birini özenle hazırladın, çünkü nereye düşecekleri hiç belli olmaz, hehe.","Senin için her şeyi vururum. Ne olursa olsun, ama asla boş mermiyle değil, hehe. ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "İlginç bir şeylerin döndüğünü hissediyorum! Peki, neymiş bakalım?";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Yine kavga mı... Peki, ne tür bir kavga?";
			}
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;

		case "SetMusketBullets":
			Dialog.Text = "Kullanılacak mühimmat türünü seç:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Savaşın başında şunları kullanacaksın:";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Musket";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = ""+GetSexPhrase("Orada dayak yesen bile, hehe? Anladım, sadece izleyeceğim.","Beni koruma yapmaya mı çalışıyorsun? Ya başına bir şey gelirse, ya da dayak yersen?")+"";
            Link.l1 = ""+GetSexPhrase("Hey, dikkat et! O noktaya gelirsek bir çaresini buluruz.","Pekala, öylece durup izlemeyeceksin herhalde, değil mi? Kaptanının anlattığın kadar harika olduğunu düşünüyorsan, bir şeyler yaparsın.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Başına nişan almak bile mi? Tamam, tamam, bana öyle bakma, anladım.";
				Link.l1 = "Umarım öyle.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Korkma, kimse buradan geçemeyecek.";
				Link.l1 = "Eğer kimseyi özlemiyorsan, tabii. Ama iyi.";
			}
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = ""+GetSexPhrase("Çok komik. Ama ne demek istediğini anladım.","Ah, merak etme, her zaman arkandayım, hehe.")+"";
            Link.l1 = ""+GetSexPhrase("İyi.","Tanrım, çekilmezsin Tom.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Şey, çok önemli bir şeyi hatırlamaya çalışıyorum. Sonra fark ediyorum ki aslında ne olduğunu bile bilmiyorum, çünkü o zaman hafızamı kaybetmiştim, yani bundan bir şey çıkmaz. Tamam, hadi gidelim.";
				Link.l1 = "Zekiymiş, doğrusu.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Şey, burada duruyorum çünkü az önce bunu bana bizzat sen emrettin. Geliyorum, geliyorum.";
				Link.l1 = "Hmm, peki, peki.";
			}
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = ""+GetSexPhrase("Ne kadar bir mesafe? Yirmi yardı geçerse, isabetli nişan alamam, bunu unutma. Tabii ki, illa birine isabet ettirmemi istemiyorsan, hehe.","Senden sonra pis kokan adamlara yaklaşmak isteyeceğimi mi sanıyorsun? Peki, mesafe ne kadar? Ama unutma, ateşimi yirmi yarddan uzağa düzgünce yöneltemem. Kimse yapamaz.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Peki, ne kadar mesafe? Ama hatırlatayım, savaşın ortasında yirmi metreden fazla uzakta hem yavaş hem de isabetli ateş edemem.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Peki. Ne? Şunu unutma ki... artık küçük değiliz, sen de ben de bunu biliyoruz.";
			}
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = ""+GetSexPhrase("Espri yapmaya kalkışmamalısın.","Espri konusunda benden öğreneceğin çok şey var, kızım. Ama ilerleme kaydediyorsun!")+"";
				link.l1 = ""+GetSexPhrase("That's odd; I've always been told the opposite.","Very funny, Tommy.")+"";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Fena bir şaka değildi. Belki bir gün şu asık suratlı halinden de kurtulursun, heh-heh.";
					Link.l1 = "Pekala.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Ha-ha-ha, iyi şaka.";
					Link.l1 = "Aslında, ben sadece... tamam.";
				}
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Peki, o zaman ben olduğum yerde durup kendimi savunacağım. Eğer onlarla çok uzaktan savaşırsan, tehlikede olan sensin, hehe.";
				link.l1 = "Don't be sarcastic; holding your ground is exactly what I want you to do from now.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Heh, bana sadece beklememi söyleyebilirdin, mesafelerden ve sayılardan bahsetmek yerine.";
					Link.l1 = "Asıl önemli olan, beni anladın ya.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Anladım, burada mevzileniyorum. Sonra onları biraz daha yaklaştır ki ateş edebileyim.";
					Link.l1 = "Elbette.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Bak, her attığım atışın deniz fenerindekine benzemesini isterdin biliyorum, ama bu her zaman olmayacak. Orada iyi bir pozisyondaydım. Sakin ve sakindim. Savaşın ortasında bunu tekrar edemezsin.";
				link.l1 = "Hmm. O zaman yirmi adım uzakta dur.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Bunu isteyeceğini biliyorum, herkes isterdi, ama o deniz fenerindeki sefer gibi olmayacak, artık işe yaramaz. İyi bir yer bulmam lazım ve kimsenin yanıma yaklaşmaması gerek, yoksa sinirlerim dayanmaz.";
					Link.l1 = "Hmm, tamam.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "O zamandan beri kesinlikle yeteneklerimi geliştirdim, ama imkansız olan yine de imkansız kalacak - savaşın ortasında, deniz fenerinden attığım o atışı asla tekrarlayamam. Tekerlekli tüfekle bile.";
					Link.l1 = "Ve imkansız da mümkündür, Tommy. Ama peki, hayır demek hayırdır.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = RandPhraseSimple("Çok iyi. O mesafeyi tam olarak koruyacağım, ama bir meyhanede ya da mağarada dövüşüyorsak, korumak için dışarı çıkacağım, hehe.","Deneyeceğim. Ama güverteler ve dar alanlar kendi kurallarını koyabilir.");
			link.l1 = ""+GetSexPhrase("Komik değil, Tommy. Uygun davran, şaka yapma ve o aptalca numaralarından da uzak dur.","Bunu biliyorum, Thomas, aptal değilim.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Hatırlamaya çalışacağım.";
				Link.l1 = "Pekala, sana güveniyorum.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Evet, kaptan.";
				Link.l1 = "Rahat ol, Tommy.";
			}
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal_1":
			dialog.text = "Ne için yardım edeyim, çalmak için mi? Ama neden? Tabii ki iltifat sayarım, ama her şeyi çoktan söyleyebilirdin. Hadi, söyle bakalım.";
			link.l1 = "Ağzını topla, ha? Neyse, lanet olsun – kendini nasıl ifade ettiğin umurumda değil, yeter ki benim tarafımda ol. Şu put meselesi... Onunla, sihirli bir şekilde başka bir yere gidebiliyorsun. Bana öyle bakma – kulağa nasıl geldiğini biliyorum. Ama ben bunu daha önce yaşadım, her şeyi kendi gözlerimle gördüm. Eğer bir iksir içersen... güvenli.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Bakıyorum biraz içmişsin. Gerçi, hayır, ayık görünüyorsun. Sonra da hep benim saçmaladığımı söylerler...";
			link.l1 = "Benimle geliyor musun, yoksa gelmiyor musun? Bu put bizi eski bir Maya şehrine götürecek diyorlar, orada bizi ne bekliyor, kim bilir? Zor zamanlarda güvenebileceğim sayılı insanlardan birisin. Ve işte şimdi öyle bir zaman geldi.";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Tüm bu olanlar hakkında kötü bir his var içimde. Eğer sen kaptanım olmasaydın, seni akıl hastanesine yatırmak gerekirdi derdim. Şimdi de Tanrı'nın var olduğuna inanmamı mı söyleyeceksin?";
			link.l1 = "O öyle, Tommy. Ve şaşırtıcı bir şekilde, bu takımadalarda sadece bizimkini değil, başkalarını da etkiliyor. Burada olup biten tüm şeytanlıkları kendin görebilirdin. Muhtemelen kutsanmış ya da lanetlenmiş tılsımların etkisini de fark etmişsindir.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Şeytanlıklar memlekette de var. Ve her zaman mantıklı bir açıklaması olmuştur. Üzgünüm kaptan, ama seninle taş putların etrafında dans edecek değilim. Düşmanları vurmak - ona varım. Hafızamı kaybetmiş olabilirim ama aklımı kaybetmedim. En azından, öyle sanıyorum.";
			link.l1 = "Pekâlâ, seni zorlayamam. O halde... nasıl istersen, Tommy.";
			link.l1.go = "tieyasal_5";
			link.l2 = "Put gibi cesursun ama putun yanına gitmeye korkuyorsan, onları vuracak cesaretin olduğunu sanmıyorum.";
			link.l2.go = "tieyasal_6";
		break;
		
		case "tieyasal_5":
			dialog.text = "Oh, peki, peki, surat asma. Tamam, o putun etrafında dansını bitirip geri gelirsen, bir dahaki sefere düşünürüm.";
			link.l1 = "Bir dahaki sefere olmayabilir. Gemiye dön, Tom.";
			link.l1.go = "exit";
			pchar.questTemp.BM_TommiTieyasalOtkaz = true;
		break;
		
		case "tieyasal_6":
			dialog.text = "Korkmuyorum, yanlış anlama. Ama içgüdülerime güvenmeye alışkınım, yıllar boyunca beni hiç yanıltmadılar. Şimdi de bana bunun sonunun iyi olmayacağını söylüyorlar. Hem de... Neyse, alınacaksın işte.";
			link.l1 = "Devam et, anlat bakalım.";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Pekala, madem öyle! Seninle omuz omuza savaşmayı kabul ettim. Ama ya, diyelim ki, bu şey gerçekten işe yararsa? Ya lanetliyse? Kimse için ölmeyeceğim, üzgünüm.";
			link.l1 = "Artık kendini kanıtladın, Tommy. En sadık insanlara ihtiyacım vardı. Ve şimdi görüyorum ki, sen onlardan biri değilsin. Ben oraya gidiyorum. Ve sen... ne istersen yap.";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Şuna bak. Sonunda alınmış işte.";
			link.l1 = "Kapa çeneni. Bizi bu kadar iğrenç buluyorsan, gemiye geri dönmek zorunda değilsin.";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Vay canına! Ciddi misin? Belki de böylesi daha iyi. Şaka bile anlamayan soğuk insanlarla olmak istemem. O halde... elveda, Ekselansları.";
			link.l1 = "Elveda, Tommy. Ve cehenneme git.";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			DialogExit();
			AddDialogExitQuestFunction("BM_Irons_tieyasal_otkaz");
		break;
		
		// Эпилог
		case "SharlieEpilog_Irons_1":
			dialog.text = "Ha. Şuna bak, şaka yapmayı öğrenmişsin. Neredeyse benim gibisin. Ama ben o yemi yutmam, hiç umutlanma.";
			link.l1 = "Yanlış anladın – bu bir şaka değil. Avrupa’ya gidiyorum, babamın yanına. Tabii, burada kalıp bekleyebilirsin... ama ne kadar süreceğini bilmiyorum.";
			link.l1.go = "SharlieEpilog_Irons_2";
		break;
		
		case "SharlieEpilog_Irons_2":
			dialog.text = "Vay be, o suratla şaka yapacak kadar da iyi değilsin. Yani beni tekmeliyorsun ha? Ben senin derini kurtardıktan sonra? Tüm yaptıklarımdan sonra mı?";
			link.l1 = "Abartma Tommy. Sen işini yaptın – ve bunun için maaş aldın. Kabul ediyorum, işinde iyisin. Beklemeye karar verirsen, seni tekrar gemide görmekten memnun olurum. Ama şimdilik...";
			link.l1.go = "SharlieEpilog_Irons_3";
		break;
		
		case "SharlieEpilog_Irons_3":
			dialog.text = "Cömertlik bu ha, kahretsin. Sağ ol, hain kaptan, beyefendi. Şöyle yazalım – 'sadık bir köpek, eğer can sıkıntısından ölmezse, sahibini bekleyebilir'.";
			link.l1 = "Kişisel alma. Koşullar böyle gelişti.";
			link.l1.go = "SharlieEpilog_Irons_nothing";
			link.l2 = "Kızgın olduğunu anlıyorum. Ben de senin yerinde olsam mutlu olmazdım. Hak ettiğin maaşa ek olarak bir aylık maaş daha vereceğim. Umarım bana kin beslemezsin.";
			link.l2.go = "SharlieEpilog_Irons_salary";
			link.l3 = "Biliyorum, bu haber seni hazırlıksız yakaladı ve öfkelenmekte haklısın. Hak ettiğin maaşın üstüne üç aylık maaş daha ödemeye hazırım.";
			link.l3.go = "SharlieEpilog_Irons_salary_X3";
		break;
		
		case "SharlieEpilog_Irons_nothing":
			dialog.text = "Koşulları siktir et. Seni de. Seninle uğraştığıma pişmanım. Ve biliyor musun? Beni sen kovmuyorsun – kendi isteğimle gidiyorum.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Irons_exit";
		break;
		
		case "SharlieEpilog_Irons_salary":
			dialog.text = "O bozuk paraları dilencilere sakla. Senin sadakana ihtiyacım yok.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Irons_exit";
			//
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Irons_salary_X3":
			dialog.text = "Üç maaş mı? Bu cömertlik resmen... Gözlerim doldu. Ver şu sadakayı. Taverndeki adamlara içki ısmarlarım – Kaptan Charles de Mor şerefine: sadakatin simgesi, dostluğun timsali, örnek alınacak adam.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Irons_exit";
			//
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Irons_exit":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Irons_exit");
		break;
	}
} 