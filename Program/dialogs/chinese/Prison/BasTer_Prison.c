// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "说吧, 我在听。 ";
			link.l1 = "我搞错了。 再见。 ";
			link.l1.go = "Exit";
			// --> 蒂钦吉图
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "true")
            {
                link.l1 = "有个印第安人被逮捕了, 是被俄国人法代抓的。 我能和他谈谈吗? ";
                link.l1.go = "Tichingitu";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "commandante")
            {
                link.l1 = "告诉我, 你真的要绞死这个印第安人吗? 为了这么点小罪, 惩罚是不是太严厉了? ";
                link.l1.go = "Tichingitu_3";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "pay")
            {
                link.l1 = "又是我, 指挥官。 俄国人法代写了这份释放印第安人的请愿书, 给你。 ";
                link.l1.go = "Tichingitu_6";
            }
			// < —蒂钦吉图
			//Jason --> 不正当竞争
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "我是应当地店主的请求来找你的, 他叫" + pchar.questTemp.Shadowtrader.Tradername + "。 他让我把这封信交给你。 ";
				link.l1.go = "Shadowtrader_prison";
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.SeekTrader") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "又是我。 我有充分证据证明" + pchar.questTemp.Shadowtrader.Tradername + "是对的。 ";
				link.l1.go = "Shadowtrader_prison2";
			}
			//Jason < —不正当竞争
			//Sinistra --> 导航之星
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTurma"))
            {
                link.l1 = "我在找一个叫朗威的人。 听说你也在找他, 警官先生。 你找到他了吗, 或者有什么线索吗? ";
                link.l1.go = "PZ_IshemLongway_1";
            }
			//Sinistra < —导航之星
		break;
		
		// --> 蒂钦吉图
		case "Tichingitu":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			dialog.text = "啊哈, 法代跟你讲过他的事了? 我没理由禁止你去看他, 先生。 你不是第一个来看这个红皮肤的人。 嗯, 十天后每个市民都能看到他被挂在太阳下晒干... ";
			link.l1 = "那我能进监狱吗? ";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "我已经跟你说过‘我没理由禁止你’。 过去吧。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "Tichingitu_3":
			DelLandQuestMark(npchar);
			dialog.text = "你是新来的吧, 先生? 刚从欧洲来? 你不了解殖民地的情况。 这次处决会给那些胆敢侵犯法国殖民者财产的红皮肤混蛋一个教训。 再说, 法代本人也坚持这样做, 他在这里是个很受尊敬的人, 也是我们总督的密友。 ";
			link.l1 = "有什么办法能减轻惩罚吗? 我还是觉得太严厉了... ";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "哦, 别谈哲学了! 如果你真的那么关心这个印第安人的命运, 就去找法代, 向他请求。 如果法代写一封释放请愿书, 我们会满足的。 ";
			link.l1 = "明白了, 警官。 我会去找法代的。 ";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "fadey";
			AddLandQuestMark(characterFromId("fadey"), "questmarkmain");
			QuestPointerToLoc("BasTer_town", "reload", "houseSp1");
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			RemoveItems(pchar, "letter_1", 1);
			dialog.text = "(阅读中) 嗯... 这个法代真奇怪... 他之前要求公开处决, 现在又请求释放这个印第安人... 不管怎样, 我想总督的朋友都像他这样。 好吧, 你可以去把这个红皮肤带走了。 ";
			link.l1 = "谢谢你, 警官! ";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			AddQuestRecord("Tichingitu", "3");
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// < —蒂钦吉图
		
		//Jason --> 迷你任务 不正当竞争
		case "Shadowtrader_prison":
			dialog.text = "又是那个" + pchar.questTemp.Shadowtrader.Tradername + "在抱怨! 好吧, 看看这次又是什么... (阅读中)";
			link.l1 = "... ";
			link.l1.go = "Shadowtrader_prison_1";
			RemoveItems(PChar, "letter_1", 1);
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Fort");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison_1":
			dialog.text = "又是这样, 荒谬的猜测, 没有一点有力证据! 好吧。 告诉他, 这根本不足以让我提醒卫兵, 命令他们在镇上搜查。 ";
			link.l1 = "你想让我这么告诉他吗? ";
			link.l1.go = "Shadowtrader_prison_2";
		break;
		
		case "Shadowtrader_prison_2":
			dialog.text = "没错 —最好逐字逐句地说。 他会明白我的意思。 我不会浪费纸张给这个烦人的家伙写回信。 ";
			link.l1 = "我明白了。 那么, 再见。 ";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.Trouble = "true";
			NextDiag.TempNode = "First_officer";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "Shadowtrader_prison2":
			dialog.text = "你声称收集到的‘充分’证据是什么? ";
			link.l1 = "我和走私者达成了协议, 通过他们的非官方商店购买货物。 他们的代理人今天晚上会到港务局办公室来, 带我去他们所谓的‘商店’。 ";
			link.l1.go = "Shadowtrader_prison2_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			pchar.quest.ShadowtraderTimeSmugglers_Over.over = "yes";
			pchar.quest.Shadowtrader_SMG.over = "yes";//取消两个中断
			sld = characterFromID("ShadowAgent_1");
			sld.lifeday = 0;
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison2_1":
			dialog.text = "嗯... 好, 干得好, 船长! 那我们就进一步行动。 我们会派我们的人去他们的会面地点, 找到他们的藏身之处, 然后逮捕所有人。 感谢你的主动性! ";
			link.l1 = "随时乐意帮忙。 我相信你的行动会成功的。 ";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.End.Fort = "true";
			AddQuestRecord("Shadowtrader", "7");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			SetTimerFunction("ShadowTrader_questmark", 0, 0, 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);//权威
			AddCharacterExpToSkill(pchar, "Fortune", 100);//运气
			AddCharacterExpToSkill(pchar, "Sneak", 100);//隐蔽
			NextDiag.TempNode = "First_officer";
		break;
		// < —迷你任务 不正当竞争
		
		// Sinistra - 任务 "导航之星" ==>
		case "PZ_IshemLongway_1":
			DelLandQuestMark(npchar);
			dialog.text = "谁? 朗... 威? 我不记得我们镇上最近有英国人。 ";
			link.l1 = "不, 朗威是... 中国人。 ";
			link.l1.go = "PZ_IshemLongway_2";
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTurma");
			DeleteQuestCondition("PZ_BasTerPeshera");
		break;
		
		case "PZ_IshemLongway_2":
			dialog.text = "好吧, 好吧。 你为什么要找你的这个朗威呢, 先生? ";
			link.l1 = "他是我的朋友。 我已经听说发生了什么事 —这是一个可悲的误会, 我向你保证。 ";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "我找他是因为他是群岛上的知名罪犯。 ";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_IshemLongway_Zashita_1":
			dialog.text = "啊, 一场误会。 如果说有什么不同的话, 我们当时并不想当场教训他。 我们只是想和他谈谈... 先从谈话开始。 然而, 你这个好斗的黄皮肤朋友不仅砍倒了几名城 guard, 还在丛林中屠杀了派去追捕他的部队。 ";
			link.l1 = "你打算再派一支部队吗? 我可以和你的人一起去, 和他谈谈, 让他冷静下来, 防止另一场灾难。 如果杀戮停止, 朗威永远离开这座城市, 这样够吗? ";
			link.l1.go = "PZ_IshemLongway_Zashita_2";
		break;
		
		case "PZ_IshemLongway_Zashita_2":
			dialog.text = "在正常情况下, 我可能会同意你。 但你看, 那些被杀的人中有一个是军官 —一个有前途的年轻中尉, 是总督阁下的宠儿。 全镇都在哀悼。 这是无法视而不见或弥补的。 你明白吗? ";
			link.l1 = "我完全理解。 我为我朋友的行为道歉。 我不会再打扰你了。 ";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
			link.l2 = "你知道, 天晓得丛林里发生了什么。 任何人都可能杀了那些人。 ";
			link.l2.go = "PZ_IshemLongway_Blef_1";
		break;
		
		case "PZ_IshemLongway_Blef_1":
			dialog.text = "你认为谁能打倒一整队由一名军官率领的巡逻兵? ";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(值得信赖) 土匪, 还能有谁? 我很惭愧地承认, 我最近才从一个大帮派手中勉强逃脱。 ";
				link.l1.go = "PZ_IshemLongway_Blef_2";
			}
			else
			{
				Notification_Perk(false, "Trustworthy");
				link.l1 = "但我怎么知道呢? 可能是任何人 —强盗。 海盗。 间谍... ";
				link.l1.go = "PZ_IshemLongway_Blef_netVD_1";
			}
		break;
		
		case "PZ_IshemLongway_Blef_2":
			dialog.text = "呵, 这不奇怪 —考虑到你的体型, 船长。 是的, 如今岛上有这样的恶棍... ";
			link.l1 = "正是! 所以, 他们可能屠杀了巡逻队和那个可怜的年轻中尉。 ";
			link.l1.go = "PZ_IshemLongway_Blef_3";
		break;
		
		case "PZ_IshemLongway_Blef_3":
			dialog.text = "不幸的是, 这完全有可能。 ";
			link.l1 = "正是如此。 所以我再次请求你让我加入下一支搜索队 —朗威会听我的, 这样我们就可以避免更多的死亡。 ";
			link.l1.go = "PZ_IshemLongway_Blef_4";
		break;
		
		case "PZ_IshemLongway_Blef_4":
			dialog.text = "好吧。 但还是有一个‘但是’, 先生。 ";
			link.l1 = "那是什么? ";
			link.l1.go = "PZ_IshemLongway_Blef_5";
		break;
		
		case "PZ_IshemLongway_Blef_5":
			dialog.text = "与丛林中发生的事情不同, 你朋友在城里的罪行是清楚且充分证明的。 这不会不受惩罚。 所以, 如果你想让他活着离开这座城市, 这些死亡必须得到赔偿。 ";
			link.l1 = "公平合理。 要花多少钱, 警官先生? ";
			link.l1.go = "PZ_IshemLongway_Blef_6";
		break;
		
		case "PZ_IshemLongway_Blef_6":
			dialog.text = "三百达布隆。 这笔钱将归入市政财政, 而不是进集市上那些投机者的腰包。 ";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "当然。 三百达布隆 —给你。 ";
				link.l1.go = "PZ_IshemLongway_Blef_7";
			}
			link.l2 = "我这次进城没带达布隆。 但如果你让我去取... ";
			link.l2.go = "PZ_IshemLongway_NetDublonov_1";
		break;
		
		case "PZ_IshemLongway_Blef_7":
			dialog.text = "很好。 你证明了自己的责任感。 我们正在为下一支小队完成简报。 我批准你加入。 ";
			link.l1 = "谢谢。 再见, 警官先生。 ";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.PZ_DrugOtryad = true;
		break;
		
		case "PZ_IshemLongway_NetDublonov_1":
			dialog.text = "我可不是昨天才出生的。 我知道你打算逃跑 —不是为了达布隆, 而是为了你亲爱的中国佬。 ";
			link.l1 = "我向你保证, 我不会和朗威一起离开镇子。 ";
			link.l1.go = "PZ_IshemLongway_NetDublonov_2";
		break;
		
		case "PZ_IshemLongway_NetDublonov_2":
			dialog.text = "承诺, 承诺... 我厌倦了你的喋喋不休, 船长。 在我们自己抓住这个该死的黄皮肤之前, 你哪儿也别想去。 ";
			link.l1 = "如果你承诺不当场杀死朗威, 我就服从你的命令, 警官先生。 ";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "但我今天个人违反城市法律了吗? ";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_1":
			dialog.text = "那你就是不知道了。 我会坚持目前的判断 —不管怎样, 必须抓住那个中国人。 ";
			link.l1 = "你目前的判断? 但你没有证据证明朗威在丛林里杀了所有人。 ";
			link.l1.go = "PZ_IshemLongway_Blef_netVD_2";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_2":
			dialog.text = "那你有他无罪的证据吗? 没有? 那就别把你的黄皮肤朋友塑造成圣人。 你明白我的意思吗? ";
			link.l1 = "我完全明白。 我为我朋友的行为道歉。 我不会再打扰你了。 ";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
		break;
		
		case "PZ_IshemLongway_Uiti_1":
			dialog.text = "恐怕我现在还不能让你走, 船长。 ";
			link.l1 = "你什么意思? ";
			link.l1.go = "PZ_IshemLongway_Uiti_2";
		break;
		
		case "PZ_IshemLongway_Uiti_2":
			dialog.text = "我的意思是, 既然这个朗威是你的朋友, 就不能保证你不会追着他跑, 并试图和他一起逃跑。 所以, 在我们自己抓住这个黄皮肤的屠夫之前, 我得把你扣下。 ";
			link.l1 = "如果你承诺不当场杀死朗威, 我就服从你的命令, 警官先生。 ";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "但我今天个人违反城市法律了吗? ";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Arest_1":
			dialog.text = "我不能做任何承诺。 谁知道你朋友在想什么, 或者他看到我们时会不会再次大开杀戒。 在此期间, 请好好享受你‘豪华’的住宿条件吧, 船长。 ";
			link.l1 = "真幽默... ";
			link.l1.go = "PZ_IshemLongway_Arest_2";
		break;
		
		case "PZ_IshemLongway_Arest_2":
			DialogExit();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto9", "PZ_SharliePlennik_BadFinal");
		break;
		
		case "PZ_IshemLongway_Pobeg_1":
			dialog.text = "明白吗, 我个人对你没有任何意见。 你说得对 —你没有犯任何罪。 但我们需要确保你的黄皮肤朋友无法逃脱法律的制裁。 ";
			link.l1 = "那你也要明白, 我不会允许自己以这种虚假的方式被拘留。 ";
			link.l1.go = "PZ_IshemLongway_Pobeg_2";
		break;
		
		case "PZ_IshemLongway_Pobeg_2":
			if (pchar.location.from_sea == "BasTer_Town")
			{
				dialog.text = "既然如此, 我们就不得不让你安静下来了, 先生。 ";
			}
			else
			{
				dialog.text = "我受够了! 中士, 带领小队去那个该死的山洞, 找到那个中国人! 我亲自处理这个家伙... ";
			}
			link.l1 = "你休想。 ";
			link.l1.go = "PZ_IshemLongway_Pobeg_3";
		break;
		
		case "PZ_IshemLongway_Pobeg_3":
			DialogExit();
			
			LAi_SetHuberType(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_MoveCharacter(NPChar, "FRANCE_CITIZENS");
			LAi_group_Attack(characterFromId("BasTer_Mayor"), Pchar);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			if (pchar.location.from_sea == "BasTer_Town")
			{
				PChar.quest.PZ_KorablPort_BadFinal.win_condition.l1 = "MapEnter";
				PChar.quest.PZ_KorablPort_BadFinal.win_condition = "PZ_KorablPort_BadFinal";
				AddQuestRecord("PZ", "10");
				LocatorReloadEnterDisable("BasTer_town", "gate_back", true);
				Island_SetReloadEnableGlobal("Guadeloupe", false);
			}
			else
			{
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition.l1 = "EnterToSea";
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition = "PZ_KorablBuhta_BadFinal";
				AddQuestRecord("PZ", "5");
				
				// 与朗威在洞穴的微对话, 如果我们在与指挥官争吵后跑到洞穴去帮助他
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1 = "location";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1.location = "Guadeloupe_CaveEntrance";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition = "PZ_IshemLongway_SorraKomendant";
				
				LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
				LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
				//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			}
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_1":
			dialog.text = "赏金猎人, 嗯? 通常我不喜欢和你们这类人打交道, 但在这种情况下, 我们的利益一致对我有好处。 显然, 这个黄皮肤是个臭名昭著的杀手。 他在镇上和丛林里杀了我很多人。 ";
			link.l1 = "我在群岛上追捕他已经有一段时间了。 ";
			link.l1.go = "PZ_IshemLongway_OhotnikOtryad_2";
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_2":
			dialog.text = "该死的无赖! 我们这么办: 我会再召集一支小队, 你和他们一起去。 这次他无处可逃, 有了你的帮助, 我们成功的机会更大。 不过别指望我给你奖励 —你是赏金猎人, 所以你的报酬会来自雇佣你的人。 你应该感激我让你和我合作。 ";
			link.l1 = "说得对。 回头见, 警官。 如果你的人在和我们这位中国朋友的另一次交锋中有幸存者, 我会告诉你进展如何。 ";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			pchar.questTemp.PZ_OhotnikOtryad = true;
		break;
		
		case "PZ_IshemLongway_BeryomOtryad":
			DialogExit();
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			DoQuestReloadToLocation("Guadeloupe_jungle_02", "goto", "goto1", "PZ_IshemLongway_Otryad");
		break;
		
		case "PZ_BasTer_ComendantDialog_1":
			dialog.text = "你说得对。 我猜你们俩是熟人吧? 你们彼此是什么关系? ";
			link.l1 = "他是我船上的导航员, 而且... ";
			link.l1.go = "PZ_BasTer_ComendantDialog_2";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "我找他是因为他是群岛上的知名罪犯。 ";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_BasTer_ComendantDialog_2":
			dialog.text = "他用枪比用地图更在行。 你知道你的宠物中国人做了什么吗? ";
			link.l1 = "说实话, 不知道, 因为我刚靠岸就开始找他了。 我相信这一切都是误会。 ";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_1":
			dialog.text = "没错。 如果你这么想要他, 你对他来说是谁? 这不重要 —重要的是你进城的目的。 ";
			link.l1 = "没有任何非法行为, 先生。 但你说‘这已经不重要了’是什么意思? 他是不是... ";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_2";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_2":
			dialog.text = "是的。 他被埋在其中一座山后面, 离墓地有一段距离。 神父们不允许为一个异教徒举行正式的基督教葬礼。 ";
			link.l1 = "如果不是秘密的话, 这是怎么发生的? ";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_3";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_3":
			dialog.text = "很简单 —他来到城里, 不停地四处窥探。 我们试图和他谈谈, 想知道他在这里做什么, 但他杀了几个人, 逃进了丛林。 我派了好几支搜索队去追他, 一支接一支, 但他把他们都消灭了! 我们不得不把他困在一个山洞里, 然后神枪手解决了剩下的事。 ";
			link.l1 = "那你不知道他在找什么吗? 你看, 他以前从未做过这种事 —他曾是我船上的导航员。 但后来他偷了我的东西跑了。 ";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_4";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_4":
			dialog.text = "哦, 我刚想起来, 是的。 这么说, 你也遭受了他的行为带来的损失? 这会给你一个教训, 船长。 你会明白, 不要雇佣你不信任的人。 永远不要相信黄皮肤的人 —记住我的话! ";
			link.l1 = "是的, 我会记住的。 你在他身上找到什么东西了吗? ";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_5";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_5":
			dialog.text = "哦, 你想追回被偷的货物? 他口袋里有一些银子, 所以如果他偷了你的东西, 他已经把钱花光了。 还有一些其他文件... 来自你船上的日志? 反正我们也看不懂 —也许是什么密码? 所有东西都沾满了血, 所以我们无法辨认未损坏的部分。 ";
			link.l1 = "呃, 是的。 谢谢你。 我一直担心如果我的日志和日记被别人捡到会发生什么... ";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_6";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_6":
			dialog.text = "为此不得不编造一个复杂的密码? 你不心疼自己的时间和精力吗? 给你。 至于银子 —别生气, 但我们把它还给市政了。 那天那个中国人让我很多手下命丧黄泉。 ";
			link.l1 = "那我就不敢坚持了。 再见。 ";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_7";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_7":
			DialogExit();
			
			LAi_SetHuberType(npchar);
			AddQuestRecord("PZ", "9");
			CloseQuestHeader("PZ");
			bDisableLandEncounters = false;
		break;
		// <== 任务 "导航之星" - Sinistra
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}