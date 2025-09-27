// 帮派守卫. 士兵和火枪手的对话 LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "你到底想要什么? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//----------------------------------- —独角鲸帮守卫的对话 --------------------------------------------
		// 独角鲸帮在圣盖博入口的岗哨
		case "Narval_warning":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("伙计们, 小心, 有疯子! 拿起武器! ","敌人在这里! 拿起武器! ","啊, 你这个混蛋! 现在我们要给你一个教训! ");
				link.l1 = "该死的! ";
				link.l1.go = "check_parol_fight";
				break;
			}
			ref location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "nrv_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "停下, 伙计。 前面是独角鲸帮的领地, 禁止陌生人进入。 你只能凭邀请通过。 你知道密码吗? ";
					link.l1 = "知道。 ";
					link.l1.go = "Narval_warning_yes";
					link.l2 = "不知道。 ";
					link.l2.go = "Narval_warning_no";
				}
				else // 如果是独角鲸帮的朋友
				{
					dialog.text = "啊, "+GetFullName(pchar)+"! 你好, 朋友, 我们接到通知说你可以在这里自由通行。 欢迎! ";
					link.l1 = "谢谢, 朋友! ";
					link.l1.go = "exit";
				}
				location.nrv_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "我希望你没忘记密码... ";
					link.l1 = "别担心... ";
					link.l1.go = "exit";
				}
				else // 如果是独角鲸帮的朋友
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! 你好吗? ";
					link.l1 = "很好, 谢谢! ";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Narval_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Narval_warning_yes":
			dialog.text = "那就去那边告诉那个硬汉。 别想骗他, 我们拿着滑膛枪的兄弟知道该怎么做。 所以如果你打算耍什么花招 —你最好现在转身离开。 我警告过你。 ";
			link.l1 = "好的, 朋友。 我知道了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_no":
			dialog.text = "那你在这里就没什么事可做了, 当然, 除非你想结束自己的生命。 或者你只是在开玩笑, 嗯? 你在跟我开玩笑吗? 其实, 我不在乎。 下去吧, 我的工作是警告, 不是阻止。 如果你不知道密码, 就回不来了。 ";
			link.l1 = "好的, 伙计。 我知道了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "你还需要什么? 下到'圣盖博号'去或者滚开! ";
				link.l1 = "... ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "对不起, "+pchar.name+", 但我在值班。 别打扰我, 伙计。 往前走! ";
				link.l1 = "... ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_parol":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("伙计们, 小心, 有疯子! 拿起武器! ","敌人在这里! 拿起武器! ","啊, 你这个混蛋! 现在我们要给你一个教训! ");
				link.l1 = "该死的! ";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "对不起, "+pchar.name+", 但我在值班。 别打扰我, 伙计。 往前走! ";
				link.l1 = "... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_parol";
				break;
			}
			dialog.text = "站在原地! 你不是我们的人! ";
			link.l1 = "我站着, 站着。 ";	
			link.l1.go = "check_parol";
		break;
		
		case "check_parol":
			dialog.text = "说密码, 清楚大声地说。 ";
			if (CheckAttribute(pchar, "questTemp.LSC.NParol_bye"))
			{
				link.l1 = StringFromKey("QuestsUtilite_" + (281 + rand(11)));
				link.l1.go = "check_parol_wrong";
				link.l2 = StringFromKey("QuestsUtilite_" + (293 + rand(11)));
				link.l2.go = "check_parol_wrong";
				link.l3 = StringFromKey("QuestsUtilite_" + (305 + rand(11)));
				link.l3.go = "check_parol_wrong";
				link.l4 = StringFromKey("QuestsUtilite_" + (317 + rand(11)));
				link.l4.go = "check_parol_wrong";
				
				switch (rand(3))
				{
					case 0:
						link.l1 = sTotalTemp;
						link.l1.go = "check_parol_1";
					break;

					case 1:
						link.l2 = sTotalTemp;
						link.l2.go = "check_parol_1";
					break;

					case 2:
						link.l3 = sTotalTemp;
						link.l3.go = "check_parol_1";
					break;

					case 3:
						link.l4 = sTotalTemp;
						link.l4.go = "check_parol_1";
					break;
				}
			}
			else
			{
				link.l1 = "还要什么密码? 让我过去, 否则别怪我不客气……";
				link.l1.go = "check_parol_wrong";
			}
		break;
		
		case "check_parol_1":
			dialog.text = "好的, 你可以继续前进。 ";
			link.l1 = "谢谢, 伙计... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			pchar.questTemp.LSC.parol_nrv = "true";
		break;
		
		case "check_parol_wrong":
			dialog.text = "嗯... 伙计们! 我们有伴了! ";
			link.l1 = "该死的! ";
			link.l1.go = "check_parol_fight";
		break;
		
		case "check_parol_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Narval_parol_repeat":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("伙计们, 小心, 有疯子! 拿起武器! ","敌人在这里! 拿起武器! ","啊, 你这个混蛋! 现在我们要给你一个教训! ");
				link.l1 = "该死的! ";
				link.l1.go = "check_parol_fight";
				break;
			}
			dialog.text = "往前走! 别站在这里! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
		break;
		
		// 在驻地
		case "Narval_residence":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("伙计们, 小心, 有疯子! 拿起武器! ","敌人在这里! 拿起武器! ","啊, 你这个混蛋! 现在我们要给你一个教训! ");
				link.l1 = "该死的! ";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // 对话根据一天中的时间。 护林员
			    {
					dialog.text = TimeGreeting()+", "+pchar.name+"! 门是开着的, 如果你想见老板的话。 ";
					link.l1 = "好的... ";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else
				{
                    dialog.text = TimeGreeting()+", "+pchar.name+"! 如果你想见老板, 他现在睡着了。 早上再来。 ";
					link.l1 = "好的... ";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");	
                }					
				break;	
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "黑人的朋友在这里无事可做。 这是老板的直接命令! ";
				if (CheckAttribute(pchar, "questTemp.LSC.Donald_enter"))
				{
					link.l1 = "他必须见我。 你们有大麻烦了, 伙计们。 我是按上将的正式命令来的。 所以打开该死的门! ";
					link.l1.go = "negotiations";
				}
				else
				{
				link.l1 = "我也不想见他... ";
				link.l1.go = "exit";
				}
				NextDiag.TempNode = "Narval_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // 护林员 。 对话根据一天中的时间 .
			{
			dialog.text = "想见老板? 嗯, 那就往前走吧。 ";
			link.l1 = "谢谢你允许我... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else
			{
            dialog.text = "想见老板? 今天不再接待了。 早上再来。 ";
			link.l1 = "好吧... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Narval_soldier":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("伙计们, 小心, 有疯子! 拿起武器! ","敌人在这里! 拿起武器! ","啊, 你这个混蛋! 现在我们要给你一个教训! ");
				link.l1 = "该死的! ";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! 你好吗? ";
				link.l1 = "我很好, 谢谢... ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "听着, 伙计, 我没心情说话。 往前走... ";
				link.l1 = "好的。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_soldier";
		break;
		
		case "negotiations":
			dialog.text = "好了好了... 冷静点。 你一开始就应该说你是上将的人。 看, 有各种各样的人在这里游荡... ";
			link.l1 = "你终于要让我过去了吗? 谢谢! ";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			DialogExit();
			NextDiag.CurrentNode = "negotiations_2";
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false); // 打开通往唐纳德.格林斯皮的入口
		break;
		
		case "negotiations_2":
			dialog.text = "往前走, 你被允许... ";
			link.l1 = "哦, 真的吗? 难以置信。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_2";
		break;
		
//----------------------------------- —里瓦多斯守卫的对话 --------------------------------------------
		// 里瓦多斯在愤怒号和贝拉斯科号入口的岗哨
		case "Rivados_warning":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("伙计们, 小心, 有好斗的疯子! 拿起武器! ","敌人在这里! 拿起武器! ","啊, 你这个病态的混蛋! 现在我们要给你一个教训! ");
				link.l1 = "该死的! ";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "rvd_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "停下! 我身后的领地属于里瓦多斯帮派, 没有邀请的陌生人不准通过。 你知道密码吗? ";
					link.l1 = "知道。 ";
					link.l1.go = "Rivados_warning_yes";
					link.l2 = "不知道。 ";
					link.l2.go = "Rivados_warning_no";
				}
				else // 如果是里瓦多斯的朋友
				{
					dialog.text = "啊, "+GetFullName(pchar)+"! 很高兴见到你! 我们接到通知说你可以在这里自由通行。 欢迎! ";
					link.l1 = "谢谢, 朋友! ";
					link.l1.go = "exit";
				}
				location.rvd_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "我希望你没忘记密码... ";
					link.l1 = "别担心... ";
					link.l1.go = "exit";
				}
				else // 如果是里瓦多斯的朋友
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! 你好吗? ";
					link.l1 = "我很好, 谢谢... ";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_warning_yes":
			dialog.text = "那你可以走了。 这个小伙子会向你要密码。 如果你有任何欺骗我们的想法, 最好现在就离开。 我警告过你。 ";
			link.l1 = "好的, 伙计。 我知道了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_no":
			dialog.text = "嗬嗬! 如果你打算不带密码来拜访我们, 那你要么非常勇敢, 要么非常愚蠢。 或者你只是在开玩笑? 那你就去吧。 我是来警告的, 不是来阻止的。 如果你真的不知道密码, 小心点! ";
			link.l1 = "好的, 伙计。 我知道了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "那么, 你想要什么? 往前走或者滚开! ";
				link.l1 = "... ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "对不起, "+pchar.name+", 但我在值班。 埃迪不想让我多说。 ";
				link.l1 = "... ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_parol":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("伙计们, 小心, 有好斗的疯子! 拿起武器! ","敌人在这里! 拿起武器! ","啊, 你这个病态的混蛋! 现在我们要给你一个教训! ");
				link.l1 = "该死的! ";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "对不起, "+pchar.name+", 但我在值班。 埃迪不想让我多说。 ";
				link.l1 = "... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_parol";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			dialog.text = "站在原地! 你不是里瓦多斯人! ";
			link.l1 = "我想通过。 ";	
			link.l1.go = "Rcheck_parol";
		break;
		
		case "Rcheck_parol":
			dialog.text = "那就说密码, 大声清楚地说。 ";
			if (CheckAttribute(pchar, "questTemp.LSC.RParol_bye"))
			{
				link.l1 = StringFromKey("QuestsUtilite_" + (281 + rand(11)));
				link.l1.go = "Rcheck_parol_wrong";
				link.l2 = StringFromKey("QuestsUtilite_" + (293 + rand(11)));
				link.l2.go = "Rcheck_parol_wrong";
				link.l3 = StringFromKey("QuestsUtilite_" + (305 + rand(11)));
				link.l3.go = "Rcheck_parol_wrong";
				link.l4 = StringFromKey("QuestsUtilite_" + (317 + rand(11)));
				link.l4.go = "Rcheck_parol_wrong";
				
				switch (rand(3))
				{
					case 0:
						link.l1 = sTotalTemp;
						link.l1.go = "Rcheck_parol_1";
					break;

					case 1:
						link.l2 = sTotalTemp;
						link.l2.go = "Rcheck_parol_1";
					break;

					case 2:
						link.l3 = sTotalTemp;
						link.l3.go = "Rcheck_parol_1";
					break;

					case 3:
						link.l4 = sTotalTemp;
						link.l4.go = "Rcheck_parol_1";
					break;
				}
			}
			else
			{
				link.l1 = "还要什么密码? 让我过去, 否则别怪我不客气……";
				link.l1.go = "Rcheck_parol_wrong";
			}
		break;
		
		case "Rcheck_parol_1":
			dialog.text = "正确。 往前走。 ";
			link.l1 = "谢谢, 伙计... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			pchar.questTemp.LSC.parol_rvd = "true";
		break;
		
		case "Rcheck_parol_wrong":
			dialog.text = "哈哈! 我们有客人了! 让我们让他看看我们是谁! ";
			link.l1 = "该死的! ";
			link.l1.go = "Rcheck_parol_fight";
		break;
		
		case "Rcheck_parol_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Rivados_parol_repeat":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("伙计们, 小心, 有好斗的疯子! 拿起武器! ","敌人在这里! 拿起武器! ","啊, 你这个病态的混蛋! 现在我们要给你一个教训! ");
				link.l1 = "该死的! ";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			dialog.text = "别站在这里, 往前走! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
		break;
		
		// 在驻地
		case "Rivados_residence":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("伙计们, 小心, 有好斗的疯子! 拿起武器! ","敌人在这里! 拿起武器! ","啊, 你这个病态的混蛋! 现在我们要教训你! ");
				link.l1 = "该死的! ";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // 护林员 。 对话根据一天中的时间 .
				{
				dialog.text = TimeGreeting()+", "+pchar.name+"! 门是开着的, 如果你想见埃迪和奇米塞特的话。 他们会很高兴见到你。 ";
				link.l1 = "好的... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else // 护林员 - 通行模式 
				{	
				dialog.text = TimeGreeting()+", "+pchar.name+"! 如果你想见埃迪和奇米塞特, 他们已经休息了。 早上再来, 他们会很高兴见到你。 ";
				link.l1 = "好的... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "独角鲸帮的朋友在埃迪的船舱里无事可做! 这是他的直接命令。 滚开! ";
				link.l1 = "我也不想见他... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (GetCharacterIndex("Chimiset") == -1) // 奇米塞特被杀
			{
				dialog.text = "你在埃迪的船舱里无事可做! 这是他的直接命令。 滚开! ";
				link.l1 = "我也不想见他... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // 护林员 。 对话根据一天中的时间 .
			{
			dialog.text = "你想见埃迪吗? 好的, 往前走, 我想他会为你抽出一分钟时间。 ";
			link.l1 = "谢谢你允许我... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else // 护林员 通行模式.
			{
            dialog.text = "你想见埃迪吗? 今天不再接待了, 早上再来, 他会为你抽出一分钟时间。 ";
			link.l1 = "好吧... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Rivados_soldier":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("伙计们, 小心, 有好斗的疯子! 拿起武器! ","敌人在这里! 拿起武器! ","啊, 你这个病态的混蛋! 现在我们要给你一个教训! ");
				link.l1 = "该死的! ";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! 你好吗? ";
				link.l1 = "我很好, 谢谢... ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "听着, 伙计, 我没心情说话。 往前走... ";
				link.l1 = "好的。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_soldier";
		break;
//----------------------------------- —海盗守卫的对话 --------------------------------------------	
		// 在仓库
		case "Shark_storage":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("伙计们, 小心, 有武装疯子! 拿起武器! ","敌人在这里! 拿起武器! ","啊, 你这个混蛋! 现在我们要踢你的屁股! ");
				link.l1 = "该死的! ";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "停下! 这是限制区域! ";
			link.l1 = "好的, 如你所说... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_storage";
		break;
		
		// 在驻地
		case "Shark_residence":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("伙计们, 小心, 有武装疯子! 拿起武器! ","敌人在这里! 拿起武器! ","啊, 你这个混蛋! 现在我们要踢你的屁股! ");
				link.l1 = "该死的! ";
				link.l1.go = "shark_guard_fight";
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00)
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // 刚刚到达
				{
					dialog.text = "停下! 你不是我们的人... 鲨鱼在等你, 还是你只是毫无目的地四处走动? ";
					link.l1 = "鲨鱼? 史蒂夫.多德森? ";
					link.l1.go = "first_talk_day";
				}
				else
				{
				dialog.text = "舰队司令会接待你。 往前走。 ";
				link.l1 = "谢谢! ";
				link.l1.go = "exit";
			}
			}
			else
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // 刚刚到达
				{
					dialog.text = "你急着去哪里? 现在是晚上, 你没看见吗! 或者你真的认为上将会醒来亲自迎接你? 早上再来。 ";
					link.l1 = "如你所说。 我在哪里可以休息? ";
					link.l1.go = "first_talk_night";
				}
			else
			{
				dialog.text = "已经很晚了,舰队司令现在不接待。 明天再来。 ";
				link.l1 = "好的... ";
				link.l1.go = "exit";
			}
			}
			NextDiag.TempNode = "Shark_residence";
		break;
		
		case "Shark_soldier":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("伙计们, 小心, 有武装疯子! 拿起武器! ","敌人在这里! 拿起武器! ","啊, 你这个混蛋! 现在我们要踢你的屁股! ");
				link.l1 = "该死的! ";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "如果上将看到我说话会不高兴的。 往前走。 ";
			link.l1 = "好的... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_soldier";
		break;
		
		case "first_talk_night":
			dialog.text = NPCStringReactionRepeat("你喝醉了吗? 转身走过桥, 经过两艘船, 然后你会找到另一座桥, 它会带你到酒馆。 在那里睡觉。 ", 
				"你想惹我生气吗? 我刚刚告诉你该怎么做。 滚开! ", 
				"去睡觉吧, 醉鬼... ",
				"走开!! ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("谢谢, 先生。 实际上你可以更礼貌一点... ", 
				"对不起, 我忘了... ",
				"我没醉! ", 
				"什么? ! ", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "first_talk_day":
			dialog.text = "别瞪大眼睛, 小伙子。 每个人都知道史蒂夫.鲨鱼是我们的舰队司令。 你找他有什么事吗? ";
			link.l1 = "是的, 该死的! 我找他有事, 而且很紧急。 ";
			link.l1.go = "first_talk_day_1";
		break;
		
		case "first_talk_day_1":
			dialog.text = "什么样的事? ";
			link.l1 = "我只会私下跟鲨鱼说。 我为扬.斯文森工作, 你认识他吗? ";
			link.l1.go = "first_talk_day_2";
		break;
		
		case "first_talk_day_2":
			dialog.text = "森林魔鬼? 哈! 大陆一半的人都认识那个人。 听着, 小伙子, 别固执。 要么解释清楚, 要么在我生气之前滚开。 鲨鱼说要把他从无用的人身边隔开, 我只是按他的命令行事。 ";
			link.l1 = "好的。 给, 看看这封信, 是森林魔鬼写给鲨鱼的。 ";
			link.l1.go = "first_talk_day_3";
		break;
		
		case "first_talk_day_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(看着信)... 好的。 我想史蒂夫会觉得有趣。 往前走。 ";
			link.l1 = "哦, 真的吗? 如果不太麻烦的话, 请把信还给我。 ";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "first_talk_day_5";
			else link.l1.go = "first_talk_day_4";
		break;
		
		case "first_talk_day_4":
			PlaySound("interface\important_item.wav");
			npchar.dialog.currentnode = "First time";
			DialogExit();
			LSC_OpenSanAvgustinDoors(); // 打开圣奥古斯丁
			LocatorReloadEnterDisable("LostShipsCity_town", "reload2", true); // 从海边关闭仓库
			pchar.quest.LSC_entry_pantry.over = "yes"; // 移除逮捕中断
			pchar.quest.LSC_findMary.over = "yes"; // 移除玛丽中断
			pchar.questTemp.LSC = "entrance"; // 更改标志
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance";
			// 关闭玛丽的入口
			LocatorReloadEnterDisable("LostShipsCity_town", "reload60", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload61", true);
		break;
		
		case "first_talk_day_5":
			PlaySound("interface\important_item.wav");
			npchar.dialog.currentnode = "First time";
			DialogExit();
			LSC_OpenSanAvgustinDoors(); // 打开圣奥古斯丁
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance";
		break;
		
		case "shark_guard_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_SHARK");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}