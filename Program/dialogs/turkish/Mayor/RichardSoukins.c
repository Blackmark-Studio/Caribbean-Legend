// Соукинс в Пуэрто-Принсипе
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = "Benimle bir işin mi var? Yok mu? O zaman defol!";
			link.l1 = "Ben zaten gidiyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "Benim için bir işin var mı?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "İzi buldum, ama o sıçanı deliğinden çıkarmak için biraz paraya ihtiyacım var – 30.000 peso lazım.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Bak, kaçakçının cesedinde bulduğum şu mektuba bir göz at";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "Bitti. Norman Vigo ve gemisi artık deniz şeytanına karıştı.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Hm... iş, diyorsun? Aslında, bana sorman iyi oldu. Dışarıdan birine ihtiyacım var. En yakın kasabada bir şey öğrenmek istiyorum ama adamlarım orada tanınıyor. Sana çok bir şey vaat edemem, ama bir şeyler alırsın.";
			link.l1 = "Güzel! Görev ne?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Üzgünüm, ama birkaç parça için riske girmem. Hoşça kal.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "O halde dinle, bir ay önce 'Saintblue' adlı şalopa kaptanıyla 200 köle teslim etmek için anlaşma yaptım. Onları buradaki plantasyon sahibine satacaktım. Süre geçti ve müşteri endişelenmeye başladı, ama dün bana şalopanın adadan çok uzakta görülmediği söylendi. Ama! Kaptan ortada yoktu. Bugün ise müşterim avansını geri istedi ve başka bir satıcıdan köle alması teklif edildiğini söyledi. Daha pahalıya, ama tüm köleler bir arada ve hemen.";
			link.l1 = "Peki? Birkaç gün içinde seni avans kaybından kurtarmak için 200 köle mi bulmam gerekiyor? Hem de üç beş kuruş için?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Tabii ki hayır. Aptal mı görünüyorum ben? Zaten onun avansını geri vermeyeceğim. Ama ona teklif edilen kölelerin bana ait olduğuna dair kanıta ihtiyacım var. Ona yeni bir anlaşma teklif edenleri bul, 10.000 peso senin olur. Anlaştık mı?";
			link.l1 = "Ben varım. Şüphen var mı? Bunu kim yapmış olabilir?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Hiç şansın yok. Başkasını bul. Sadece 10.000 mi? Kusura bakma, bu yetmez.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "Eğer bir fikrim olsaydı, senin hizmetlerine asla başvurmazdım. O adamlar çoktan ölmüş olurdu. Ama onların 'Saintblue'nun yükünden ve müşterimden nasıl haberdar olduklarını öğrenmek istiyorum. Görünen o ki, bu iş onlar için fazlasıyla kolay olmuş. Şimdi anlıyor musun?";
			link.l1 = "Evet, birisi sana ihanet etmiş.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "Kesinlikle! Onu arıyorum. Rakiplerimi öldürmek ya da kölelerimi geri getirmek senin önceliğin değil. O sıçanı istiyorum—daha doğrusu, dürüst olmak gerekirse, kafasını bir kazığa geçirilmiş halde görmek istiyorum. Şimdi anladın mı adamlarımın görevin hakkında hiçbir şey bilmemesi gerektiğini? Bilgiyi kimin sattığını bulana kadar herkesten şüpheleneceğim. Ve bunu gerçekten istemiyorum...";
			link.l1 = "Anladım. O zaman sessiz kalacağım. Yoldayım.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "O kadarına otuz bin mi diyorsun? Bu büyük bir meblağ... Sana en fazla 5.000 peso verebilirim, şu anda elimde olan bu kadar. Sakın parayla kaçmayı aklından bile geçirme, yoksa seni bulur, en yakın çite asarım! Anladın mı?";
			link.l1 = "Pekala, o zaman bana beş bin ver...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Al onu. Aramanın sonucunu bekliyorum.";
			link.l1 = "Her şey yoluna girecek.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ha! Harika haber! Başaracağına emindim. Elimde ilginç bilgiler var.";
			link.l1 = "İşimi yaptım ve on binimi istiyorum.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Elbette, işte ödülün. Ama hemen kaçma, sana bir görevim daha var.\nPfaifer, Norman Vigo'nun tayfasından, 'Septima' adlı lügerin adamı. Norman Vigo'nun bir hain olduğundan eminim, aramızdan biri olsa bile. Son zamanlarda adanın yakınlarındaki sularda görülmüş. Senin işin, bu sıçanı deniz şeytanına yollamak. İlk seferinde beni yarı yolda bırakmadın, bu işi de sana emanet etmek istiyorum. Sana 15.000 peso ödeyeceğim. Anlaştık mı?";
			link.l1 = "Bu iş bende! Hain Norman Vigo'yu ölü bilin.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "Biliyor musun, bunun bir parçası olmak istemiyorum... Zaten hiç vaktim yok. Kusura bakma, ama gidiyorum.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "Biliyorum, biliyorum. Adamlarım savaşı izledi ve kusursuz zaferini çoktan bana bildirdi. Tamam, işini iyi yaptın. İşte sana söz verdiğim 15.000 peso. Ve teşekkür ederim, bana gerçekten büyük bir iyilik yaptın.";
			link.l1 = "Önemli değil, yardımcı olmaktan memnun oldum! Ama artık gitmem lazım, burada fazla kaldım ve yapacak çok işim var. Hoşça kal!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;


	}
}
